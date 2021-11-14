#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    int input;

    Initialize_All_Account_Info();

    while(true)
    {
        input = Show_Main_Menu();
        if (input == 1)
        {
            Account_Count(Game_Start());
        }
        else if (input == 2)
        {
            Account_Register();
        }
        else if (input == 3)
        {
            Account_Change_Password();
        }
        else if (input == 4)
        {
            Account_Login();
        }
        else if (input == 5)
        {   
            Exit_Game();
        }
    }
}

void Exit_Game()
{
    Close_Account_System();

    exit(1);
}