#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct table{
    char board[15][15];
    char player0[20];
    char player1[20];
    int turn;
}Table;

int main()
{
    printf("%zd",sizeof(Table));
}