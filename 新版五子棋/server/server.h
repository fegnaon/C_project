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

extern void Login(Request request,char *buf);
extern void Register(Request request,char *buf);
extern void Modify(Request request,char *buf);
void Start(Request request,char *buf);
void PushTable(Request request,char *buf);
void Chess(Request request,char *buf);

void Initialize_All_Table();
void Trans(char *buf,void *res,int len);
int CheckIfEnd(char (*board)[15],int row,int column);