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

int Initialize_All_Account_Info();
void Login(Request request,char *buf);
void Register(Request request,char *buf);
void Modify(Request request,char *buf);
void Close_Account_System();

void Trans(char *buf,void *res,int len);

Node* Creat_Node(char *account,char *password,int win,int lose);
int Traverse_All_Account_Info(Head);

static Head all_account_head = {.length = 0,.next = NULL};