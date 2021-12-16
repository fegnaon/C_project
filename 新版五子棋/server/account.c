#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include "account.h"

Node* Creat_Node(char *ac,char *psw,int w,int l)
{
    Node *node = (Node*)malloc(sizeof(Node));
    strncpy(node->account,ac,16);
    strncpy(node->password,psw,16);
    node->win = w;
    node->lose = l;
    node->next = NULL;
    
    return node;
}

int Initialize_All_Account_Info()
{
    FILE *fp;
    if(!(fp = fopen("account","r")))
    {
        fp = fopen("account","w");
        fclose(fp);
        fp = fopen("account","r");
    }
    
    char ac[16];
    char psw[16];
    int w;
    int l;
    char i;

    while(true)
    {   
        i = getc(fp);
        if (i != '#')break;

        fscanf(fp,"%s %s %d %d\n",ac,psw,&w,&l);

        Node *last = all_account_head.next;

        if (last)
        {
            while(last->next)
            {
                last = last->next;
            }
            last->next = Creat_Node(ac,psw,w,l);
            all_account_head.length ++;
        }
        else
        {
            all_account_head.next = Creat_Node(ac,psw,w,l);
            all_account_head.length ++;
        }
    }
    fclose(fp);
}

void Login(Request request,char *buf)
{
    Node *player = all_account_head.next;
    Answer answer = {0};
    while(strcmp(player->account,request.account))
    {
        if (!player){
            answer.num1 = false;
            Trans(buf,&answer,64);
            return;
        }
        player = player->next;
    }
    if(strcmp(player->password,request.password)){
        answer.num1 = false;
        Trans(buf,&answer,64);
        return;
    }
    answer.num1 = true;
    answer.num2 = player->win;
    answer.num3 = player->lose;
    Trans(buf,&answer,64);
    return;
}

void Register(Request request,char *buf)
{
    Node *last = all_account_head.next;
    Answer answer = {0};

    if (last)
    {
        while(last->next)
        {   
            if (!strcmp(last->account,request.account)){
                answer.num1 = false;
                Trans(buf,&answer,64);
                return;
            }
            last = last->next;
        }
        last->next = Creat_Node(request.account,request.password,0,0);
        all_account_head.length ++;
    }
    else
    {
        all_account_head.next = Creat_Node(request.account,request.password,0,0);
        all_account_head.length ++;
    }
    answer.num1 = true;
    Trans(buf,&answer,64);
    return;
}

void Modify(Request request,char *buf)
{
    Node *change = all_account_head.next;
    Answer answer = {0};

    while(strcmp(change->account,request.account))
    {
        change = change->next;
    }
    strcpy(change->password,request.password);
    answer.num1 = true;
    Trans(buf,&answer,64);
    return;
}