typedef struct table{
    char board[15][15];
    char player0[20];
    char player1[20];
    int turn;
}Table;

typedef struct status{
    char account[20];
    int table_number;
    int win;
    int lose;
}Status;

extern Status player;

int LoginInterface(char *ac,char *psw,int tip);
int MainMenuInterface(int mode);
int ModifyInterface(char* psw);
void InitializeUI();