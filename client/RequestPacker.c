#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "client.h"

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

Request PackExitRequest()
{
    Request request = {.type = 7};
    strcpy(request.account,player.account);
    
    return request;
}