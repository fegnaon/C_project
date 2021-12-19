#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <stdbool.h>
#include <time.h>
#include "client.h"
#pragma comment (lib,"ws2_32.lib")

#define BUFSIZE 64

int main()
{   
    int choice;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("1.14.96.36");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    
    Request request;
    Accept accept;
    char sbuf[64];
    char lbuf[512];

    player.table_number = 0;

//初始菜单
    while(true)
    {   
        system("cls");
        PrintLoginInterface();
        scanf("%10d",&choice);

        if (choice == 1){
            request = PackLoginRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if (accept.num1 == 1){
                LoadStatus(accept);
                printf("登录成功!\n");
                system("pause");
                break;
            }
            else{
                
                printf("登录失败");
                if (accept.num1 == 0){
                    printf(",账号不存在或密码错误\n");
                }
                else if (accept.num1 == 2){
                    printf(",该账号已登录,不能重复登录\n");
                }
                system("pause");
                continue;
            }
        }
        else if(choice == 2){
            request = PackRegisterRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){
                printf("注册成功!\n");
                system("pause");
                continue;
            }
            else{
                printf("注册失败,该账号已存在\n");
                system("pause");
                continue;
            }
        }
        else if(choice == 3){
            exit(0);
        }
        else{
            printf("你输入的啥啊\n");
            system("pause");
        }
    }

//主菜单
    while(true)
    {
        system("cls");
        PrintMainMenu();
        scanf("%10d",&choice);

        if (choice == 1){
            request = PackStartRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;
            
            if(accept.num1 == 1){
                player.table_number = request.table_number;
                printf("上桌成功!\n");
                system("pause");

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
                    system("cls");
                    PrintTable(new_table);

                    if (new_table.turn == -2){
                        system("cls");
                        printf("你输了!");
                        player.lose += 1;
                        system("pause");
                        break;
                    }

                    if (strcmp(new_table.player1,"NO PLAYER")){
                        if ((new_table.turn == 0 && (!strcmp(new_table.player0,player.account)))||(new_table.turn == 1 && (!strcmp(new_table.player1,player.account)))){
                            while (true)
                            {
                                request = PackChessRequest();
                                Trans(sbuf,&request,64);

                                SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                                connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
                                send(clifd,sbuf,64,0);
                                recv(clifd,sbuf,64,0);
                                closesocket(clifd);

                                accept = *(Accept*)sbuf;

                                if (accept.num1 == 0){
                                    printf("下棋失败,这里已经有一个棋子了\n");
                                }
                                else if (accept.num1 == 2){
                                    printf("你赢了!");
                                    system("pause");
                                    break;
                                }
                                else{
                                    break;
                                }
                            }
                            if (accept.num1 == 2){
                                player.win += 1;
                                break;
                            }
                        }
                    }
                    else{
                        printf("当前桌上你有一位玩家,请等待...\n");
                    }
                    delay();
                }
                continue;
            }
            else{
                printf("上桌失败");
                printf(",这桌已经满了\n");
                system("pause");
                continue;
            }
        }
        else if(choice == 2){
            request = PackModifyRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){
                printf("修改成功!\n");
                system("pause");
                continue;
            }
            else{
                printf("修改失败");
                system("pause");
                continue;
            }
        }
        else if(choice == 3){
            request = PackExitRequest();
            Trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            closesocket(clifd);
            exit(0);
        }
        else{
            printf("你输入的啥啊\n");
            system("pause");
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

void delay()
{
    time_t last,cur;
    time(&cur);
    while(1){
        time(&last);
        if (last>cur){
            return;
        }
    }
}