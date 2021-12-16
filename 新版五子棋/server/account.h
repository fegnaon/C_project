typedef struct Node{
    char account[32];
    char password[32];
    int win;
    int lose;
    struct Node *next;
}Node;

typedef struct Head{
    int length;
    Node *next;
}Head;

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

static Head all_account_head = {.length = 0,.next = NULL};

Node* Creat_Node(char *ac,char *psw,int w,int l);
int Initialize_All_Account_Info();
void SaveAccountData();

void Login(Request request,char *buf);
void Register(Request request,char *buf);
void Modify(Request request,char *buf);

void Count(char *player0,char *player1,int turn);

extern void Trans(char *buf,void *res,int len);