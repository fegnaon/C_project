typedef struct status{
    char account[20];
    int table_number;
    int win;
    int lose;
}Status;

typedef struct table{
    char board[15][15];
    char player0[20];
    char player1[20];
    int turn;
}Table;

typedef struct request{
    int type;
    char account[20];
    char password[20];
    int table_number;
    int row;
    int column;
}Request;

typedef struct accept{
    int num1;
    int num2;
    int num3;
}Accept;

extern Status player;

extern int LoginInterface(char *ac,char *psw,int tip);
extern int MainMenuInterface(int mode);
extern int ModifyInterface(char* psw);
extern void GameInterface(Table table,int myturn,int* i,int* j);

extern Request PackLoginRequest(char *account,char *password);
extern Request PackRegisterRequest(char *account,char *password);
extern Request PackModifyRequest(char *psw);
extern Request PackStartRequest();
extern Request PackPullTableRequest();
extern Request PackChessRequest(int row,int column);
extern Request PackExitRequest();

extern void InitializeAI();
extern void InitializeUI();
extern void SingleGame(int turn);

void Trans(char *buf,void *res,int len);
void LoadStatus(Accept accept);