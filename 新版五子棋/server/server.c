#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "server.h"

#define BUFSIZE 20

int main()
{   
    int clifd;
    struct sockaddr_in cliaddr;
    int size = sizeof(cliaddr);
    char* buf[20] = {0};

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

    //��ʼ���˺�ϵͳ
    Initialize_All_Account_Info();
    

    while(1)
    {
        clifd = accept(servfd,(struct sockaddr*)&cliaddr,&size);
        recv(clifd,buf,BUFSIZE,0);
        int req = atoi(buf);
        switch (req)
        {
            case 1:
                /*��¼*/
                break;
            case 2:
                /*ע��*/
                break;
            case 3:
                /*�޸�����*/
                break;
            case 4:
                /*�Ծ�*/
                break;
        }
    }

    close(servfd);
    return 0;
}