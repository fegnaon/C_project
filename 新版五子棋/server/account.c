#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "account.h"

Node* Creat_Node(char *ac,char *psw,int w,int l)
{
    Node *node = (Node*)malloc(sizeof(Node));
    strncpy(node->account,ac,15);
    strncpy(node->password,psw,15);
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
        fclose(fp);
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

int Account_Login(const char *ac,const char *psw)
{
    Node *player = all_account_head.next;
    while(strcmp(player->account,ac))
    {
        if (!player){
            return -1;
        }
        player = player->next;
    }
    if(strcmp(player->password,psw)){
        return -1;
    }
    return 0;
}