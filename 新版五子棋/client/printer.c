#include <stdio.h>
#include <string.h>
#include "client.h"

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
1.开始游戏\n\
2.修改密码\n\
3.退出游戏\n\
请选择您要进行的操作:");
}

void PrintTable(Table table)
{
    int i,j;
    for (i = 0;i < 15;i ++)
    {
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