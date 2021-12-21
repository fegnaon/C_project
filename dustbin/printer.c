#include <stdio.h>
#include <string.h>
#include "client.h"

extern Status player;

void PrintLoginInterface(){
   printf("\
��ӭ����������С��Ϸ\n\
1.��¼\n\
2.ע��\n\
3.������Ϸ\n\
4.�˳���Ϸ\n\
��ѡ����Ҫ���еĲ���:"); 
}

void PrintMainMenu(){
    printf("\
���˵�\n\
���:%s ʤ:%d ��:%d\n\
1.������Ϸ\n\
2.������Ϸ\n\
3.�޸�����\n\
4.�˳���Ϸ\n\
��ѡ����Ҫ���еĲ���:",player.account,player.win,player.lose);
}

void PrintBoard(char (*board)[15])
{
    int i,j;
    printf("   1 2 3 4 5 6 7 8 9 101112131415\n");
    for (i = 0;i < 15;i ++)
    {
        printf("%2d ",i+1);
        for (j = 0;j < 15; j ++)
        {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

void PrintTable(Table table)
{
    int i,j;
    printf("   1 2 3 4 5 6 7 8 9 101112131415\n");
    for (i = 0;i < 15;i ++)
    {
        printf("%2d ",i+1);
        for (j = 0;j < 15; j ++)
        {
            printf("%c ",table.board[i][j]);
        }
        printf("\n");
    }

    printf("��ǰ���\n���1:%s\n���2:%s\n",table.player0,table.player1);
    
    if (!strcmp(table.player1,"NO PLAYER")){
        printf("���δ������ȴ�");
    }
}