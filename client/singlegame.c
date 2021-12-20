#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "client.h"
#include "singlegame.h"


void SingleGame()
{      
    char board[15][15];
    int i,j;

    for (i = 0;i < 15;i ++)
    {   
        for (j = 0;j < 15;j ++)
        {
            board[i][j] = '.';
        }
    }

    int turn;
    printf("\
��ѡ�����ֻ��Ǻ���\n\
1.����\n\
2.����\n");
    scanf("%d",&turn);
    turn --;
    
    while (true)
    {   
        if (turn == 0){
            while(true)
            {   
                system("cls");
                printf("����������!\n");
                PrintBoard(board);
                printf("������Ҫ���������:");
                scanf("%d %d",&i,&j);
                i --;j --;
                if (board[i][j] != '.'){
                    printf("�Ѿ���һ��������\n");
                    continue;
                }
                board[i][j] = 'X';
                break;
            }
            if (CheckIfEnd(board,i,j)){
                system("cls");
                PrintBoard(board);
                printf("��Ӯ��!!\n");
                break;
            }
        }
        else{
            system("cls");
            printf("AI����!\n");
            PrintBoard(board);
            Game(&i,&j,board,'O','X');
            // board[row][column] = '1';
            // system("cls");
            if (CheckIfEnd(board,i,j)){
                system("cls");
                PrintBoard(board);
                printf("����Ӯ��!!\n");
                break;
            }
        }
        turn = (turn+1)%2;
    }
    system("pause");

    return;
}

int CheckIfEnd(char (*board)[15],int row,int column)
{
    char piece = board[row][column];
    int cnt = 0;

    for (row = 0;row < 15;row ++)
    {
        for (column = 0;column < 15;column ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    for (column = 0;column < 15;column ++)
    {
        for (row = 0;row < 15;row ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    row = 15 - 1;
    while(row > 0)
    {   
        column = 0;
        int check_row = row;

        while(!(check_row == 15 || column == 15))
        {   
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column ++;
        }
        
        cnt = 0;
        row --;
    }

    column = 0;
    while(column != 15)
    {   
        row = 0;
        int check_column = column;

        while(!(row == 15 || check_column == 15))
        {
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column ++;
        }
        
        cnt = 0;
        column ++;
    }

    column = 0;
    while(column < 15)
    {   
        row = 0;
        int check_column = column;

        while(check_column > -1)
        {   
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column --;
        }
        
        cnt = 0;
        column ++;
    }

    row = 0;
    while(row != 15)
    {   
        column = 0;
        int check_row = row;

        while(check_row < 15)
        {
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column --;
        }
        
        cnt = 0;
        row ++;
    }
    
    return 0;
}