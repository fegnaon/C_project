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

Status player;

extern void PrintMainMenu();
extern void PrintLoginInterface();
extern void PrintTable(Table table);

extern Request PackLoginRequest();
extern Request PackRegisterRequest();
extern Request PackModifyRequest();
extern Request PackStartRequest();
extern Request PackPullTableRequest();
extern Request PackChessRequest();
extern Request PackExitRequest();

extern void Initialize();
extern void SingleGame();

void Trans(char *buf,void *res,int len);
void LoadStatus(Accept accept);
void delay();