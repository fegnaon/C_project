#include <stdio.h>
#include <string.h>
#include "client.h"

extern Status player;

void PrintLoginInterface(){
   printf("\
��ӭ����������С��Ϸ\n\
1.��¼\n\
2.ע��\n\
3.�˳���Ϸ\n\
��ѡ����Ҫ���еĲ���:"); 
}

void PrintMainMenu(){
    printf("\
���˵�\n\
���:%s ʤ:%d ��:%d\n\
1.��ʼ��Ϸ\n\
2.�޸�����\n\
3.�˳���Ϸ\n\
��ѡ����Ҫ���еĲ���:",player.account,player.win,player.lose);
}

void PrintTable(Table table)
{
    int i,j;
    printf("   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
    for (i = 0;i < 15;i ++)
    {
        printf("%2d ",i+1);
        for (j = 0;j < 15; j ++)
        {
            printf("%c  ",table.board[i][j]);
        }
        printf("\n");
    }

    printf("��ǰ���\n���1:%s\n���2:%s\n",table.player0,table.player1);
    
    if (!strcmp(table.player1,"NO PLAYER")){
        printf("���δ������ȴ�");
    }
}