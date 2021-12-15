#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "server.h"

#define BUFSIZE 64

void *Login(void *agrs)
{
    int clifd = *(int*)agrs;

    char buf[64];
    strcpy(buf,(char*)(agrs+sizeof(int)));
    char account[32];
    char password[32];
    strncpy(account,buf,32);
    *strchr(account,'\t')= '\0';
    strncpy(password,strchr(buf,'\t')+1,32);

    int rslt = Account_Login(account,password);
    if (rslt){
        strcpy(buf,"fail");
        send(clifd,buf,BUFSIZE,0);
    }
    else{
        strcpy(buf,"success");
        send(clifd,buf,BUFSIZE,0);
    }

    close(clifd);
    pthread_exit(NULL);
}

int main()
{   
    struct sockaddr_in cliaddr;
    int size = sizeof(struct sockaddr_in);

    int servfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("");
    servaddr.sin_port = htons(6666);
    bind(servfd,(struct sockaddr*)&servaddr,size);
    listen(servfd,20);

    struct sockaddr_in cliaddr;
    int size = sizeof(cliaddr);

    //初始化账号系统
    Initialize_All_Account_Info();

    int clifd;
    char request[64];

    while(1)
    {
        clifd = accept(servfd,(struct sockaddr*)&cliaddr,&size);
        recv(clifd,request,BUFSIZE,0);
        int req = request[0];
    }

    close(servfd);
    return 0;
}