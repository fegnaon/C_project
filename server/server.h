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

typedef struct answer{
    int num1;
    int num2;
    int num3;
}Answer;

Table tables[40];

extern int Initialize_All_Account_Info();
extern void SaveAccountData();
extern void ShowPlayerOnline();
extern int ShowAllAccount();

extern void Login(Request request,char *buf);
extern void Register(Request request,char *buf);
extern void Modify(Request request,char *buf);
extern void PlayerExit(Request request);
void Start(Request request,char *buf);
void PushTable(Request request,char *buf);
void Chess(Request request,char *buf);

extern void Count(char *player0,char *player1,int turn);

void Initialize_All_Table();
void Trans(char *buf,void *res,int len);
int CheckIfEnd(char (*board)[15],int row,int column);