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

static char PlayerOnline[100][20];

void ShowPlayerOnline(){
    printf("当前在线玩家:\n");
    for (int i = 0;i < 100;i ++){
        if (strcmp(PlayerOnline[i],"NULL")){
            printf("player %d : %s\n",i,PlayerOnline[i]);
        }
    }
}

int ShowAllAccount()
{
    Node *current = all_account_head.next;

    printf("所有玩家的账号信息:\n");
    printf("现在一共有 %d 个账号\n",all_account_head.length);

    for (int i = 0;i < all_account_head.length;i ++)
    {
        printf("账户%d: 账户�?:%s 密码:%s �?:%d �?:%d",i+1,current->account,current->password,current->win,current->lose);
        current = current->next;
        printf("\n");
    }
}

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

    for (int i = 0;i < 100;i ++)
    {
        strcpy(PlayerOnline[i],"NULL");
    }
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

    int i,j = 0,no;
    for (i = 0;i < 100;i ++)
    {
        if (!strcmp(PlayerOnline[i],request.account)){
            answer.num1 = 2;
            Trans(buf,&answer,64);
            return;
        }
        if (j == 0){
            if (!strcmp(PlayerOnline[i],"NULL")){
                no = i;
            }
        }
    }
    strcpy(PlayerOnline[no],request.account);

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
        if (!strcmp(last->account,request.account)){
            answer.num1 = false;
            Trans(buf,&answer,64);
            return;
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
    answer.num2 = 0;
    answer.num3 = 0;
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

void PlayerExit(Request request)
{
    int i;
    for (i = 0;i < 100;i ++)
    {
        if (!strcmp(PlayerOnline[i],request.account)){
            strcpy(PlayerOnline[i],"NULL");
            return;
        }
    }
}

void Count(char *player0,char *player1,int turn)
{
    Node *player = all_account_head.next;
    int i = 0;

    while(true)
    {
        if (!strcmp(player->account,player0)){
            i ++;
            if (turn == 0){
                player->win += 1;
            }
            else{
                player->lose -= 1;
            }
        }
        if (!strcmp(player->account,player1)){
            i ++;
            if (turn == 1){
                player->win += 1;
            }
            else{
                player->lose -= 1;
            }
        }
        if (i == 2){
            break;
        }
        player = player->next;
    }
    return;
}

void SaveAccountData()
{
    FILE *fp = fopen("account","w");

    Node *node = all_account_head.next;
    Node *free_node = all_account_head.next;

    while(node)
    {
        fprintf(fp,"#%s %s %d %d\n",node->account,node->password,node->win,node->lose);
        node = node->next;
        free(free_node);
        free_node = node;
    }
    fputc('@',fp);

    fclose(fp);
}