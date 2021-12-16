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
    servaddr.sin_addr.s_addr = inet_addr("");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    
    Request request;
    Accept accept;
    int sbuf[64];
    int lbuf[512];

    player.table_number = 0;

//初始页面
    while(true)
    {   
        system("cls");
        PrintLoginInterface();
        scanf("%d",&choice);

        if (choice == 1){
            request = PackLoginRequest();
            trans(sbuf,&request,64);

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
                printf("登录失败，账号不存在或密码错误");
                system("pause");
                continue;
            }
        }
        else if(choice == 2){
            request = PackRegisterRequest();
            trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){
                printf("注册成功!\n");
                system("pause");
                break;
            }
            else{
                printf("注册失败，账号已存在");
                system("pause");
                continue;
            }
        }
        else if(choice == 3){
            exit(0);
        }
    }

//主菜单
    while(true)
    {
        system("cls");
        PrintMainMenu();
        scanf("%d",&choice);

        if (choice == 1){
            request = PackStartRequest();
            trans(sbuf,&request,64);

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

                //开始游戏
                //每秒钟拉取一次棋桌，如果到该自己下了，就下棋
                while(true)
                {
                    request = PackPullTableRequest();
                    trans(sbuf,&request,64);
                    
                    SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                    connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
                    send(clifd,sbuf,64,0);
                    recv(clifd,lbuf,64,0);
                    closesocket(clifd);

                    Table new_table = *(Table*)lbuf;
                    PrintTable(new_table);

                    if (strcmp(new_table.player1,"NO PLAYER")){
                        if ((new_table.turn == 0 && (!strcmp(new_table.player0,player.account)))||(new_table.turn == 1 && (!strcmp(new_table.player1,player.account)))){
                            //如果到本方了，就发送一个下棋请求
                            while (true)
                            {
                                request = PackChessRequest();
                                trans(sbuf,&request,64);

                                SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
                                connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
                                send(clifd,sbuf,64,0);
                                recv(clifd,sbuf,64,0);
                                closesocket(clifd);

                                accept = *(Accept*)sbuf;

                                if (accept.num1 == 0){
                                    if (accept.num2 == 1){
                                        printf("下棋失败，这里已经有一个棋子了");
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        printf("当前桌上只有您一位玩家，请等待...\n");
                    }
                    delay();
                }


                continue;
            }
            else{
                printf("上桌失败");
                if (accept.num2 == 1){
                    printf(",这桌已经满了\n");
                }
                system("pause");
                continue;
            }
        }
        else if(choice == 2){
            request = PackModifyRequest();
            trans(sbuf,&request,64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,sbuf,64,0);
            recv(clifd,sbuf,64,0);
            closesocket(clifd);

            accept = *(Accept*)sbuf;

            if(accept.num1 == 1){
                printf("修改成功!\n");
                system("pause");
                break;
            }
            else{
                printf("修改失败");
                system("pause");
                continue;
            }
        }
        else if(choice == 3){
            exit(0);
        }
    }
}

Request PackLoginRequest()
{
    Request request = {.type = 1};

    printf("请输入您的账号:");
    scanf("%16s",request.account);
    strncpy(player.account,request.account,16);
    printf("请输入您的密码:");
    scanf("%16s",request.password);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackRegisterRequest()
{
    Request request = {.type = 2};

    printf("请输入您的账号(16个字符以内):");
    scanf("%16s",request.account);
    printf("请输入您的密码(16个字符以内):");
    scanf("%16s",request.password);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackModifyRequest()
{
    Request request = {.type = 3};
    strncpy(request.account,player.account,16);

    printf("请输入您的新密码:");
    scanf("%16s",request.password);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackStartRequest()
{
    Request request = {.type = 4};
    strncpy(request.account,player.account,16);

    while(1)
    {
        printf("请输入您要选择的桌号(1-40):");
        scanf("%d",request.table_number);
        if (request.table_number <= 0){
            printf("桌号必须大于0!");
        }
        else if (request.table_number > 40){
            printf("桌号必须小于100!");
        }
        else{
            break;
        }
    }

    return request;
}

Request PackPullTableRequest()
{
    Request request = {.type = 5};
    strncpy(request.account,player.account,16);
    request.table_number = player.table_number;

    return request;
}

Request PackChessRequest()
{
    Request request = {.type = 6};
    strncpy(request.account,player.account,16);
    request.table_number = player.table_number;
    while (1)
    {
        printf("轮到你下棋了，请输入下棋的坐标:");
        scanf("%d %d",&(request.row),&(request.column));
        if (request.row > 15 || request.row <= 0 || request.column > 15 || request.column <= 0){
            printf("超出棋盘范围!n");
        }
        else{
            break;
        }
    }
    
    return request;
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