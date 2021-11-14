#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define LINE_LENGTH 15
#define ROW_LENGTH 15
#define PLAYER_ONE 1
#define PLAYER_two 2

int Game_Start();
void Print_Board(char (*board)[ROW_LENGTH]);
int Check_If_End(char (*board)[ROW_LENGTH],int line,int row);

// int main()
// {
//     int a = Game_Start();

//     // system("cls");
//     printf("a = %d",a);
// }

int Game_Start()
{   
    int row;
    int line;
    char board[LINE_LENGTH][ROW_LENGTH];

// 初始化棋盘
    for (line = 0;line < LINE_LENGTH;line ++)
    {   
        for (row = 0;row < ROW_LENGTH;row ++)
        {
            board[line][row] = '.';
        }
    }

    int turn = 1;

// 开始轮流下棋
    Print_Board(board);
    while(true)
    {   
        printf("Player %s,please select the position to drop(line row):",(turn == PLAYER_ONE)?"one":"two");
        scanf("%d %d",&line,&row);
        
        if (board[line-1][row-1] != '.')
        {
            printf("There is already a piece here\n");
            continue;
        }
        else
        {
            board[line-1][row-1] = (turn == PLAYER_ONE)?'#':'X';
        }

        if(Check_If_End(board,line-1,row-1))
        {
            return turn;
        }

        turn = (turn + 1) % 2;
        system("cls");
        Print_Board(board);
    }
}




int Check_If_End(char (*board)[ROW_LENGTH],int line,int row)
{
    char piece = board[line][row];
    int cnt = 0;

    for (line = 0;line < LINE_LENGTH;line ++)
    {
        for (row = 0;row < ROW_LENGTH;row ++)
        {
            if (board[line][row] == piece)
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

    for (row = 0;row < ROW_LENGTH;row ++)
    {
        for (line = 0;line < LINE_LENGTH;line ++)
        {
            if (board[line][row] == piece)
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

// 检查斜着的
    line = LINE_LENGTH - 1;
    while(line > 0)
    {   
        row = 0;
        int check_line = line;

        while(!(check_line == LINE_LENGTH || row == ROW_LENGTH))
        {   
            if (board[check_line][row] == piece)
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

            check_line ++;
            row ++;
        }
        
        cnt = 0;
        line --;
    }

    row = 0;
    while(row != ROW_LENGTH)
    {   
        line = 0;
        int check_row = row;

        while(!(line == LINE_LENGTH || check_row == ROW_LENGTH))
        {
            if (board[line][check_row] == piece)
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

            line ++;
            check_row ++;
        }
        
        cnt = 0;
        row ++;
    }
    
    return 0;
}

void Print_Board(char (*board)[15])
{   
    int row;
    int line;

    for (line = 0;line < LINE_LENGTH;line ++)
    {
        for (row = 0;row < ROW_LENGTH;row ++)
        {
            printf("%c ",board[line][row]);
        }
        printf("\n");
    }
}