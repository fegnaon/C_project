#include <stdio.h>
#include <stdlib.h>

int Show_Main_Menu();

typedef struct{
    char account[16];
    int win;
    int lose;
}Player;

extern Player player_one;
extern Player player_two;

// int main()
// {
//     printf("receive:%d",Show_Main_Menu());
// }

int Show_Main_Menu()
{   
    system("cls");
    
    int input;
    printf("\
Player One\t\t\t\t\tPlayer two\n\
ID:%s\t\t\t\t\tID:%s\n\
Win:%d Lose:%d\t\t\t\t\tWin:%d Lose:%d\n\
\t\t\t1 ��ʼ��Ϸ\n\
\t\t\t2 ע���˺�\n\
\t\t\t3 �޸�����\n\
\t\t\t4 ��¼/�л��˺�\n\
\t\t\t5 �˳���Ϸ\n\n\n\
Please enter your choice:",player_one.account,player_two.account,player_one.win,player_one.lose,player_two.win,player_two.lose);

    scanf("%d",&input);

    return input;
}

// player_one.account,player_two.account,player_one.win,player_one.lose,player_two.win,player_two.lose);