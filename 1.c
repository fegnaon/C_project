#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct table{
    char board[15][15];
    char player0[20];
    char player1[20];
    int turn;
}Table;

int main()
{
    time_t a;
    time_t cur = time(&a);
    int i = 0;
    while(1){
        time(&a);
        if (time(&a)>cur){
            printf("%d\n",i);
            cur = a;
            i ++;
        }
    }
}