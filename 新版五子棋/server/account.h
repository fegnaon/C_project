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

typedef struct{
    char account[16];
    int win;
    int lose;
}Player;

int Initialize_All_Account_Info();
void Account_Count(int win);
void Account_Register();
void Account_Change_Password();
int Account_Login(const char *ac,const char* psw);
void Close_Account_System();

Node* Creat_Node(char *account,char *password,int win,int lose);
int Traverse_All_Account_Info(Head);

static Head all_account_head = {.length = 0,.next = NULL};