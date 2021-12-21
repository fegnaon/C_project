#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"

Request PackLoginRequest(char *account,char *password)
{
    Request request = {.type = 1};

    strncpy(request.account,account,16);
    strncpy(request.password,password,16);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackRegisterRequest(char *account,char *password)
{
    Request request = {.type = 2};

    strncpy(request.account,account,16);
    strncpy(request.password,password,16);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackModifyRequest(char *psw)
{
    Request request = {.type = 3};
    strncpy(request.account,player.account,16);
    strncpy(request.password,psw,16);
    request.table_number = 0;
    request.row = 0;
    request.column = 0;

    return request;
}

Request PackStartRequest()
{
    Request request = {.type = 4};
    strncpy(request.account,player.account,16);
    request.table_number = player.table_number;

    return request;
}

Request PackPullTableRequest()
{
    Request request = {.type = 5};
    strncpy(request.account,player.account,16);
    request.table_number = player.table_number;

    return request;
}

Request PackChessRequest(int row,int column)
{
    Request request = {.type = 6};
    strncpy(request.account,player.account,16);
    request.table_number = player.table_number;
    request.row = row;
    request.column = column;
    
    return request;
}

Request PackExitRequest()
{
    Request request = {.type = 7};
    strcpy(request.account,player.account);
    
    return request;
}