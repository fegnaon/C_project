Request PackLoginRequest();
Request PackRegisterRequest();
Request PackModifyRequest();
Request PackStartRequest();
Request PackPullTableRequest();
Request PackChessRequest();

void Trans(char *buf,void *res,int len);
void LoadStatus(Accept accept);
void delay();

extern void PrintLoginInterface();
extern void PrintMainMenu();
extern void PrintTable(Table table);

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