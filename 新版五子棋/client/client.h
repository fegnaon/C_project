char* PackLoginRequest();
char* PackRegisterRequest();
char* PackModifyRequest();
char* PackStartRequest();
char* PackPullTableRequest(char* account,char* password);
char* PackTableRequest(char* account,char* password);

void LoadStatus(char *receive_status);

extern void PrintLoginInterface();
extern void PrintMainMenu();

typedef struct status{
    char account[20];
    int table_number;
    int win;
    int lose;
}Status;

Status player;