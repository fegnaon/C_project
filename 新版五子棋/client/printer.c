#include <stdio.h>
#include <string.h>
#include "client.h"

extern Status player;

void PrintLoginInterface(){
   printf("\
欢迎来到五子棋小游戏\n\
1.登录\n\
2.注册\n\
3.退出游戏\n\
请选择您要进行的操作:"); 
}

void PrintMainMenu(){
    printf("\
主菜单\n\
玩家:%s 胜:%d 负:%d\n\
1.开始游戏\n\
2.修改密码\n\
3.退出游戏\n\
请选择您要进行的操作:",player.account,player.win,player.lose);
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
            printf("%c ",table.board[i][j]);
        }
        printf("\n");
    }

    printf("当前玩家\n玩家1:%s\n玩家2:%s\n",table.player0,table.player1);
    
    if (!strcmp(table.player1,"NO PLAYER")){
        printf("玩家未到，请等待");
    }
}