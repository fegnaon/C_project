#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "account.h"

    
// int main()232323
// {
//     printf("Player one :%s\n",player_one.account);
//     printf("Player two %s\n",player_two.account);

//     Initialize_All_Account_Info();
//     Traverse_All_Account_Info(all_account_head);
//     Account_Change_Password();
//     Traverse_All_Account_Info(all_account_head);

//     Account_Login();

//     printf("Player one :%s\n",player_one.account);
//     printf("Player two %s\n",player_two.account);

//     Close_Account_System();
// }

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

void Account_Count(int win)
{
    if (win == 1)
    {
        player_one.win ++;
        player_two.lose ++;

        Node *player = all_account_head.next;

        while(strcmp(player->account,player_one.account))
        {
            player = player->next;
        }
        player->win ++;

        player = all_account_head.next;

        while(strcmp(player->account,player_two.account))
        {
            player = player->next;
        }
        player->lose ++;
    }
    else
    {
        player_two.win ++;
        player_one.lose ++;

        Node *player = all_account_head.next;

        while(strcmp(player->account,player_two.account))
        {
            player = player->next;
        }
        player->win ++;

        player = all_account_head.next;

        while(strcmp(player->account,player_one.account))
        {
            player = player->next;
        }
        player->lose ++;
    }
}

int Traverse_All_Account_Info(Head head)
{
    Node *current = head.next;

    printf("starting print list...\n");
    printf("list have %d node\n",head.length);

    for (int i = 0;i < head.length;i ++)
    {
        printf("Node%d: %s %s %d %d",i+1,current->account,current->password,current->win,current->lose);
        current = current->next;
        printf("\n");
    }
}

void Account_Register()  //先将账号信息写入账号文件，然后再把新的账号添加到链表中
{
    FILE *fp;
    char ac[16];
    char psw[16];

    // system("cls");

    printf("Please enter your account:");
    scanf("%s",ac);
    printf("Please enter your password:");
    scanf("%s",psw);

    fp = fopen("account","r+");
    fseek(fp,-1,SEEK_CUR);
    
    fprintf(fp,"#%s %s 0 0\n@",ac,psw);

    Node *last = all_account_head.next;

    if (last)
    {
        while(last->next)
        {
            last = last->next;
        }
        last->next = Creat_Node(ac,psw,0,0);
        all_account_head.length ++;
    }
    else
    {
        all_account_head.next = Creat_Node(ac,psw,0,0);
        all_account_head.length ++;
    }

    fclose(fp);    
}

 //先根据账户名在链表中找到账户，然后输入当前密码，如果正确就可以修改密码，比如不正确就不行
void Account_Change_Password()
{
    char ac[16];
    char psw[16];

    // system("cls");

    printf("Please enter your account:");
    scanf("%s",ac);

    Node *change = all_account_head.next;

    while(strcmp(change->account,ac))
    {
        if (!change)
        {
            printf("System dosen't find this account\n");
            system("pause");
            return;
        }
        change = change->next;
    }

    printf("Please enter your current password:");
    scanf("%s",psw);

    if(strcmp(change->password,psw))
    {
        printf("Password Wrong!\n");
        system("pause");
        return;
    }

    printf("Please enter your new password:");
    scanf("%s",psw);

    strcpy(change->password,psw);

    printf("Success!\n");
    system("pause");
}

void Account_Login()
{
    char ac[16];
    char psw[16];
    int choice;

//  system("cls");

    printf("Which player do you want to be?(1 or 2):");
    scanf("%d",&choice);

    printf("Please enter your account:");
    scanf("%s",ac);

    Node *player = all_account_head.next;

    while(strcmp(player->account,ac))
    {
        if (!player)
        {
            printf("System dosen't find this account\n");
            system("pause");
            return;
        }
        player = player->next;
    }

    printf("Please enter your password:");
    scanf("%s",psw);

    if(strcmp(player->password,psw))
    {
        printf("Password Wrong!\n");
        system("pause");
        return;
    }

    if (choice == 1)
    {
        strcpy(player_one.account,player->account);
        player_one.lose = player->lose;
        player_one.win = player->win;
    }
    else if (choice == 2)
    {
        strcpy(player_two.account,player->account);
        player_two.lose = player->lose;
        player_two.win = player->win;        
    }

    printf("Login success!\n");
    system("pause");
}

void Close_Account_System()
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