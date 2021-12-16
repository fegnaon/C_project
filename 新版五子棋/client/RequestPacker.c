#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"

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
        scanf("%d",&(request.table_number));
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
            printf("超出棋盘范围!\n");
        }
        else{
            break;
        }
    }
    
    return request;
}

Request PackExitRequest()
{
    Request request = {.type = 7};
    strcpy(request.account,player.account);
    
    return request;
}