#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
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
    
    char request[64];
    char receive_bool[8];
    char receive_status[8];
    char receive_table[512];

    player.table_number = 0;

//初始页面
    while(1)
    {   
        system("cls");
        PrintLoginInterface();
        scanf("%d",&choice);

        if (choice == 1){
            strnpy(request,PackLoginRequest(),64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,request,64,0);
            recv(clifd,receive_status,sizeof(receive_status),0);
            closesocket(clifd);

            LoadStatus(receive_status);

            if (receive_status[0] == '1'){
                LoadStatus(receive_status);
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
            strnpy(request,PackLoginRequest(),64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,request,64,0);
            recv(clifd,receive_bool,sizeof(receive_bool),0);
            closesocket(clifd);

            if(!strcmp(receive_bool,"success")){
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
    while(1)
    {
        system("cls");
        PrintMainMenu();
        scanf("%d",&choice);

        if (choice == 1){
            strncpy(request,PackStartRequest(),64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,request,64,0);
            recv(clifd,receive_bool,sizeof(receive_bool),0);
            closesocket(clifd);
            
            if(!strcmp(receive_bool,"success")){
                player.table_number = *(int*)&request[1];
                printf("上桌成功!\n");
                system("pause");

                StartGame();

                continue;
            }
            else{
                printf("上桌失败");
                if (!strcmp(receive_bool,"op")){
                    printf(",这桌已经满了\n");
                }
                system("pause");
                continue;
            }
        }
        else if(choice == 2){
            strncpy(request,PackModifyRequest(),64);

            SOCKET clifd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            connect(clifd,(struct sockaddr*)&servaddr,sizeof(servaddr));
            send(clifd,request,64,0);
            recv(clifd,receive_bool,sizeof(receive_bool),0);
            closesocket(clifd);

            if(!strcmp(receive_bool,"success")){
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

char* PackLoginRequest()
{
    char account[20];
    char password[20];
    printf("请输入您的账号:");
    scanf("%16s",account);
    strncpy(player.account,account,16);
    printf("请输入您的密码:");
    scanf("%16s",password);

    char request[64] = "1";
    strcat(request,account);
    strcat(request,"\t");
    strcat(request,password);
    
    return request;
}

char* PackRegisterRequest()
{
    char account[20];
    char password[20];
    printf("请输入您的账号(16个字符以内):");
    scanf("%16s",account);
    printf("请输入您的密码(16个字符以内):");
    scanf("%16s",password);

    char request[64] = "2";
    strcat(request,account);
    strcat(request,"\t");
    strcat(request,password);
    
    return request;
}

char* PackModifyRequest()
{
    char password[20];
    printf("请输入您的新密码(16个字符以内):");
    scanf("%16s",password);

    char request[64] = "3";
    strcat(request,player.account);
    strcat(request,"\t");
    strcat(request,password);
    
    return request;
}

char* PackStartRequest()
{
    int table_number;
    while(1)
    {
        printf("请输入您要选择的桌号(1-100):");
        scanf("%d",table_number);
        if (table_number <= 0){
            printf("桌号必须大于0!");
        }
        else if (table_number > 100){
            printf("桌号必须小于100!");
        }
        else{
            break;
        }
    }

    char request[64] = "4";
    strcat(request,(char*)&table_number);
    request[sizeof(char)+sizeof(int)] = '\0';

    return request;
}

void LoadStatus(char *receive_status)
{
    player.win = receive_status[1];
    player.lose = receive_status[2];    
}