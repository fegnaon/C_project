#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <pthread.h>
#include "server.h"

void* Commands(void *a)
{   
    char command[32];
    while(true)
    {
        scanf("%31s",command);
        if (!strcmp(command,"exit")){
            SaveAccountData();
            exit(0);
        }
        if (!strcmp(command,"player")){
            ShowPlayerOnline();
        }
        if (!strcmp(command,"account")){
            ShowAllAccount();
        }
    }
}

int main()
{
    //初始�?
    //初始化socket
    int size = sizeof(struct sockaddr_in);

    int servfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    int clifd;
    struct sockaddr_in servaddr,cliaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(6666);
    bind(servfd,(struct sockaddr*)&servaddr,size);
    listen(servfd,20);
    //初始化账号系�?
    Initialize_All_Account_Info();
    //初始化所有棋�?
    Initialize_All_Table();

    Request request;
    char sbuf[64];
    char lbuf[512];
    pthread_t th;
    pthread_create(&th,NULL,Commands,NULL);

    while(1)
    {
        clifd = accept(servfd,(struct sockaddr*)&cliaddr,&size);
        recv(clifd,sbuf,64,0);
        request = *(Request*)sbuf;
        switch (request.type)
        {
        case 1: 
            printf("处理了一条登录请求\n");
            Login(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 2:
            printf("处理了一条注册请求\n");
            Register(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 3:
            printf("处理了一条修改密码请求\n");
            Modify(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 4:
            printf("处理了一条开始游戏请求\n");
            Start(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 5:
            printf("处理了一条棋盘请求\n");
            PushTable(request,lbuf);
            send(clifd,lbuf,512,0);break;
        case 6:
            printf("处理了一条下棋请求\n");
            Chess(request,sbuf);
            send(clifd,sbuf,64,0);break;
        case 7:
            printf("处理了一条离线请求\n");
            PlayerExit(request);break;
        }
        close(clifd);
    }

    close(servfd);
    return 0;
}

void Initialize_All_Table()
{
    int i,j,k;
    for (i = 0;i < 100;i ++)
    {   
        for (j = 0;j < 15;j ++)
        {   
            for (k = 0;k < 15;k ++)
            {
                tables[i].board[j][k] = '.';
            }
        }
        strcpy(tables[i].player0,"NO PLAYER");
        strcpy(tables[i].player1,"NO PLAYER");
        tables[i].turn = -2;
    }
    return;
}

void Start(Request request,char *buf)
{
//先检查是否桌上已经满�?
    Answer answer = {0};
    int table_number = request.table_number;

    if (tables[table_number].turn == -2){//玩家1
        tables[table_number].turn = -1;
        strncpy(tables[table_number].player0,request.account,16);
        answer.num2 = 0;
    }
    else if(tables[table_number].turn == -1){//玩家2
        tables[table_number].turn = 0;
        strncpy(tables[table_number].player1,request.account,16);
        answer.num2 = 1;
    }
    else{//桌上满了
        answer.num1 = false;
        Trans(buf,&answer,64);
        return;
    }
    answer.num1 = true;
    Trans(buf,&answer,64);
    return;
}

void PushTable(Request request,char *buf)
{   
    int table_number = request.table_number;
    Table table = tables[table_number];
    if (tables[table_number].turn == -4){
        tables[table_number].turn = -3;
    }
    else if (tables[table_number].turn == -3){
        tables[table_number].turn = -2;
        int i,j;
        for (i = 0;i < 15;i ++)
        {
            for (j = 0;j < 15;j ++)
            {
                tables[table_number].board[i][j] = '.';
            }
        }
        strcpy(tables[table_number].player0,"NO PLAYER");
        strcpy(tables[table_number].player1,"NO PLAYER");
    }
    Trans(buf,&table,512);
    return;
}

void Chess(Request request,char *buf)
{
    int row = request.row;
    int column = request.column;
    int table_number = request.table_number;
    Answer answer = {0};

    if (tables[table_number].turn == 0){
        tables[table_number].board[row][column] = '0';
    }
    else if(tables[table_number].turn == 1){
        tables[table_number].board[row][column] = '1';
    }
    if (CheckIfEnd(tables[table_number].board,row,column)){
        //保存战绩
        Count(tables[table_number].player0,tables[table_number].player1,tables[table_number].turn);
        tables[table_number].turn = -4;
    }
    else{
        tables[table_number].turn = (tables[table_number].turn+1)%2;
    }
    answer.num1 = 1;
    Trans(buf,&answer,64);
    return;
}

void Trans(char *buf,void *res,int len)
{
    int i;
    for (i = 0;i < len;i ++){
        buf[i] = *(((char*)res)+i);
    }
}

int CheckIfEnd(char (*board)[15],int row,int column)
{
    char piece = board[row][column];
    int cnt = 0;

    for (row = 0;row < 15;row ++)
    {
        for (column = 0;column < 15;column ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    for (column = 0;column < 15;column ++)
    {
        for (row = 0;row < 15;row ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    row = 15 - 1;
    while(row > 0)
    {   
        column = 0;
        int check_row = row;

        while(!(check_row == 15 || column == 15))
        {   
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column ++;
        }
        
        cnt = 0;
        row --;
    }

    column = 0;
    while(column != 15)
    {   
        row = 0;
        int check_column = column;

        while(!(row == 15 || check_column == 15))
        {
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column ++;
        }
        
        cnt = 0;
        column ++;
    }

    column = 0;
    while(column < 15)
    {   
        row = 0;
        int check_column = column;

        while(check_column > -1)
        {   
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column --;
        }
        
        cnt = 0;
        column ++;
    }

    row = 0;
    while(row != 15)
    {   
        column = 0;
        int check_row = row;

        while(check_row < 15)
        {
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column --;
        }
        
        cnt = 0;
        row ++;
    }
    
    return 0;
}