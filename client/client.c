#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>
#include <pthread.h>
#pragma comment (lib,"ws2_32.lib")
#include "client.h"

#define BUFSIZE 64

Status player;

void* checkisrun(void* servaddr)
{
    for(;is_run();delay(100));
    logout(*(struct sockaddr_in*)servaddr);
    exit(0);
}

int main()
{   
    int choice;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("1.14.96.36");
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    
    Request request;
    Accept accept;
    char sbuf[64];
    char lbuf[512];
    int tip = 0;

    player.table_number = 0;
    InitializeAI();
    InitializeUI();
    pthread_t th;
    pthread_create(&th,NULL,checkisrun,&servaddr);

//初始菜单
    start:
    tip = 0;
    while(true)
    {   
        char ac[20],psw[20];
        choice = LoginInterface(ac,psw,tip);
        printf("%d",choice);

        if (choice == 1){
            request = PackLoginRequest(ac,psw);
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if (accept.num1 == 1){//登录成功
                strncpy(player.account,ac,16);
                LoadStatus(accept);
                tip = 1;
                LoginInterface(ac,psw,tip);
                //打印登录成功
                break;
            }
            else{//登录失败
                if (accept.num1 == 0){
                    tip = 2;
                }
                else if (accept.num1 == 2){
                    tip = 3;
                }
                continue;
            }
        }
        else if(choice == 2){
            request = PackRegisterRequest(ac,psw);
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){//注册成功
                strcpy(player.account,ac);
                LoadStatus(accept);
                tip = 4;
                continue;
            }
            else{//注册失败
                tip = 5;
                continue;
            }
        }
        else if(choice/10 == 3){
            SingleGame(choice%10);
        }
        else if(choice == 4){
            exit(0);
        }
    }
//主菜单
    while(true)
    {   
        int number;
        int mode = 0;
        choice = MainMenuInterface(mode);

        if (choice == 1){//上桌请求
            request = PackStartRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;
            
            if(accept.num1 == 1){//上桌成功
                int myturn;
                int row,column;
                if (accept.num2 == 0){
                    myturn = 0;
                }
                else if (accept.num2 == 1){
                    myturn = 1;
                }
                while(true)
                {
                    request = PackPullTableRequest();
                    Trans(sbuf,&request,64);
                    
                    SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                    connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
                    send(clifd,sbuf,64,0);
                    recv(clifd,lbuf,512,0);
                    closesocket(clifd);

                    Table new_table = *(Table*)lbuf;

                    if (new_table.turn == myturn){
                        GameInterface(new_table,myturn,&row,&column);

                        request = PackChessRequest(row,column);
                        Trans(sbuf,&request,64);

                        SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                        connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
                        send(clifd,sbuf,64,0);
                        recv(clifd,sbuf,64,0);
                        closesocket(clifd);
                    }
                    else{
                        GameInterface(new_table,myturn,&row,&column);
                    }
                    if (new_table.turn == -4){
                        player.lose += 1;
                        break;
                    }
                    if (new_table.turn == -3){
                        player.win += 1;
                        break;
                    }
                    Sleep(200);
                }
                continue;
            }
            else{//上桌失败
                mode = 1;
                continue;
            }
        }
        else if (choice/10 == 2){
            SingleGame(choice%10);
        }
        else if(choice == 3){//修改密码
            char npw[20];
            if (!ModifyInterface(npw)){
                continue;
            }
            request = PackModifyRequest(npw);

            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){
                continue;
            }
        }
        else if(choice == 4){//登出
            logout(servaddr);

            goto start;
        }
        else if(choice == 5){//退出
            logout(servaddr);
            exit(0);
        }
    }
}

void Trans(char *buf,void *res,int len)
{
    int i;
    for (i = 0;i < len;i ++){
        buf[i] = *(((char*)res)+i);
    }
}

void LoadStatus(Accept accept)
{
    player.win = accept.num2;
    player.lose = accept.num3;    
}

void logout(struct sockaddr_in servaddr)
{
    Request request = PackExitRequest();
    char sbuf[64];
    Trans(sbuf,&request,64);
    
    SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    send(clifd,sbuf,64,0);
    closesocket(clifd);
}