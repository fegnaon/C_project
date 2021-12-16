#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include "server.h"

int main()
{
    //初始化
    //初始化socket
    int size = sizeof(struct sockaddr_in);

    int servfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    int clifd;
    struct sockaddr_in servaddr,cliaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("");
    servaddr.sin_port = htons(6666);
    bind(servfd,(struct sockaddr*)&servaddr,size);
    listen(servfd,20);
    //初始化账号系统
    Initialize_All_Account_Info();

    Request request;
    char sbuf[64];
    char lbuf[512];

    while(1)
    {
        clifd = accept(servfd,(struct sockaddr*)&cliaddr,&size);
        recv(clifd,sbuf,64,0);
        request = *(Request*)sbuf;
        switch (request.type)
        {
        case 1:
            Login(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 2:
            Register(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 3:
            Modify(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 4:
            Start(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 5:
            PushTable(request,lbuf);
            send(clifd,lbuf,64,0);break;
        case 6:
            Chess(request,sbuf);
            send(clifd,sbuf,64,0);break;
        }
        close(clifd);
    }

    close(servfd);
    return 0;
}

void Start(Request request,char *buf)
{
//先检查是否桌上已经满了
    Answer answer = {0};
    if (strcmp(tables[request.table_number-1].player1,"NO PLAYER")){
        answer.num1 = true;
        Trans(buf,&answer,64);
        return;
    }
}

void Trans(char *buf,void *res,int len)
{
    int i;
    for (i = 0;i < len;i ++){
        buf[i] = *(((char*)res)+i);
    }
}