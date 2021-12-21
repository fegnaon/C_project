#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "singlegame.h"


void SingleGame(int turn)
{
    Table table;
    int i,j;

    for (i = 0;i < 15;i ++)
    {   
        for (j = 0;j < 15;j ++)
        {
            table.board[i][j] = '.';
        }
    }
    strcpy(table.player0,"Äã");
    strcpy(table.player1,"µçÄÔ");
    table.turn = turn;

    int row,column;
    while(true)
    {
        if (table.turn == 0){
            GameInterface(table,0,&row,&column);
            table.board[row][column] = '0';
            table.turn = (table.turn+1)%2;
            if (CheckIfEnd(table.board,row,column)){
                table.turn = -2;
                break;
            }
            GameInterface(table,&row,&column);
        }
        else{
            Game(&row,&column,0,table.board,'1','0');
            table.board[row][column] = '1';
            table.turn = (table.turn+1)%2;
            if (CheckIfEnd(table.board,row,column)){
                table.turn = -1;
                break;
            }
        }
    }

    GameInterface(table,&row,&column);

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