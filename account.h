typedef struct Node{
    char account[16];
    char password[16];
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
void Account_Login();
void Close_Account_System();

Node* Creat_Node(char *account,char *password,int win,int lose);
int Traverse_All_Account_Info(Head);

static Head all_account_head = {.length = 0,.next = NULL};

Player player_one = {.account = "No player now",.lose = 0,.win = 0};
Player player_two = {.account = "No player now",.lose = 0,.win = 0};