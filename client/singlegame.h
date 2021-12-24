typedef struct table{
    char board[15][15];
    char player0[20];
    char player1[20];
    int turn;
}Table;

typedef struct Stack{
    int sequence[225][2];
    int length;
}Stack;

int CheckIfEnd(char (*board)[15],int row,int column);

extern void GameInterface(Table table,int myturn,int* i,int* j);

extern void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece);