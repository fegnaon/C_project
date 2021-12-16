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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    
    Request request;
    Accept accept;
    char sbuf[64];
    char lbuf[512];

    player.table_number = 0;

//初始页面
    while(true)
    {   
        system("cls");
        PrintLoginInterface();
        scanf("%d",&choice);

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
                printf("��¼�ɹ�!\n");
                system("pause");
                break;
            }
            else{
                printf("��¼ʧ�ܣ��˺Ų����ڻ��������");
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
                printf("ע��ɹ�!\n");
                system("pause");
                continue;
            }
            else{
                printf("ע��ʧ�ܣ��˺��Ѵ���");
                system("pause");
                continue;
            }
        }
        else if(choice == 3){
            exit(0);
        }
    }

//主菜�?
    while(true)
    {
        system("cls");
        PrintMainMenu();
        scanf("%d",&choice);

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
                printf("�����ɹ�!\n");
                system("pause");

                //开始游�?
                //每秒钟拉取一次棋桌，如果到该自己下了，就下棋
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
                        printf("������!");
                        player.lose += 1;
                        system("pause");
                        break;
                    }

                    if (strcmp(new_table.player1,"NO PLAYER")){
                        if ((new_table.turn == 0 && (!strcmp(new_table.player0,player.account)))||(new_table.turn == 1 && (!strcmp(new_table.player1,player.account)))){
                            //如果到本方了，就发送一个下棋请�?
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
                                    printf("����ʧ�ܣ������Ѿ���һ��������");
                                }
                                else if (accept.num1 == 2){
                                    printf("��Ӯ��!");
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
                        printf("��ǰ����ֻ����һλ��ң���ȴ�...\n");
                    }
                    delay();
                }
                continue;
            }
            else{
                printf("����ʧ��");
                printf(",�����Ѿ�����\n");
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
                printf("�޸ĳɹ�!\n");
                system("pause");
                continue;
            }
            else{
                printf("�޸�ʧ��");
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

    printf("�����������˺�:");
    scanf("%16s",request.account);
    strncpy(player.account,request.account,16);
    printf("��������������:");
    scanf("%16s",request.password);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackRegisterRequest()
{
    Request request = {.type = 2};

    printf("�����������˺�(16���ַ�����):");
    scanf("%16s",request.account);
    printf("��������������(16���ַ�����):");
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

    printf("����������������:");
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
        printf("��������Ҫѡ�������(1-40):");
        scanf("%d",&(request.table_number));
        if (request.table_number <= 0){
            printf("���ű������0!");
        }
        else if (request.table_number > 40){
            printf("���ű���С��100!");
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
        printf("�ֵ��������ˣ����������������:");
        scanf("%d %d",&(request.row),&(request.column));
        if (request.row > 15 || request.row <= 0 || request.column > 15 || request.column <= 0){
            printf("�������̷�Χ!\n");
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