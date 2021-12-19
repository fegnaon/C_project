#include <stdio.h>
#include <stdlib.h>

int AllSonType[43] = {
3,2,
31,
23,21,
313,311,
231,213,211,
3133,3131,3113,3111,
2311,2133,2131,2113,2111,
31333,31331,31313,31311,31133,31131,31111,
23111,21331,21311,21131,21113,21111,
313331,313311,313131,313111,311331,311311,311111,
231113,211311,211131,211111};

int AllType[40] = {212,2112,21112,211112,2111112,
213,312,
313,
2113,3112,31312,21313,313312,213313,3133313,
3113,31313,
31112,21113,313112,211313,311312,213113,3113313,3133113,3131313,2311132,
31113,313113,311313,
311112,211113,3113112,2113113,3131112,2111313,
311113,
3111113,3111112,2111113};

int TypeVal(int type);
int CalculateGrade(char (*board)[15],char mpiece,char epiece);
int CheckIfEnd(char (*board)[15],int row,int column);

int CalculateLineGrade(char *line,char piece,int len,int ifstart)
{     
    if (len == 1){
        if (line[0] != piece){
        return 0;
        }else{
            return 20;
        }
    }

    int i,j;
    int ifinson = 0,ifintype = 0;
    int type = 0;
    int tag = 0,last = 0;
    if (ifstart == 1){
        type = 2;
    }

    for (i = 0;i < len;i ++){
        int a = (line[i] != '.')?((line[i] == piece)?1:2):3;
        type = type * 10 + a;
        // printf("type = %d,last = %d\n",type,last);

        for (j = 0;j < 43;j ++){
            if (AllSonType[j] == type){
                ifinson = 1;
            }
        }
        for (j = 0;j < 40;j ++){
            if (AllType[j] == type){
                ifintype = 1;
            }
        }

        if (ifinson == 0){
            if (ifintype == 0){
                if (tag == 1){
                    type = last;
                }
            }
            break;
        }else{
            if (ifintype == 0){
                ifinson = 0;
                ifintype = 0;
                continue;
            }else{
                tag = 1;
                ifinson = 0;
                ifintype = 0;
                last = type;
                continue;
            }
        }
    }
    // printf("%d %d\n",type,TypeVal(type));
    return TypeVal(type) + CalculateLineGrade(line+1,piece,len-1,0);
}

int PRINT(char *line,char piece,int len,int ifstart){
    for (int i = 0;i < len;i ++){
        printf("%c",line[i]);
    }
    printf("\n");
}

int CalculateGrade(char (*board)[15],char mpiece,char epiece)
{   
    int grade = 0;
    int i,j;
    char line[15];
    for (i = 0;i < 15;i ++)
    {
        grade += CalculateLineGrade(board[i],mpiece,15,1);
    }
    for (j = 0;j < 15;j ++)
    {
        for (i = 0;i < 15;i ++){
            line[i] = board[i][j];
        }
        grade += CalculateLineGrade(line,mpiece,15,1);
    }
    int len;
    int start;
    int cnt = 0;
    
    start = 14;
    while(start != -1)
    {
        for (i = start,j = 0;i < 15;i ++,j ++)
        {
            line[cnt] = board[i][j];
            cnt ++;
        }
        grade += CalculateLineGrade(line,mpiece,15-start,1);
        cnt = 0;
        start --;
    }
    start = 14;
    while(start != 0)
    {
        for (j = start,i = 0;j < 15;i ++,j ++)
        {
            line[cnt] = board[i][j];
            cnt ++;
        }
        grade += CalculateLineGrade(line,mpiece,15-start,1);
        cnt = 0;
        start --;
    }

    start = 0;
    while(start != 15)
    {
        for (i = start,j = 14;i < 15;i ++,j --)
        {
            line[cnt] = board[i][j];
            cnt ++;
        }
        grade += CalculateLineGrade(line,mpiece,15-start,1);
        cnt = 0;
        start ++;
    }
    start = 0;
    while(start != 14)
    {
        for (j = start,i = 0;j >= 0;i ++,j --)
        {
            line[cnt] = board[i][j];
            cnt ++;
        }
        grade += CalculateLineGrade(line,mpiece,start+1,1);
        cnt = 0;
        start ++;
    }
    
    return grade;
}

int TypeVal(int type){
    switch (type){
    case 3111113:return 10000;
    case 3111112:return 10000;
    case 2111113:return 10000;
    case 311113:return 8000;
    case 311112:return 500;
    case 211113:return 500;
    case 3113112:return 500;
    case 2113113:return 500;
    case 3131112:return 500;
    case 2111313:return 500;
    case 31113:return 400;
    case 313113:return 400;
    case 311313:return 400;
    case 31112:return 100;
    case 21113:return 100;
    case 313112:return 100;
    case 211313:return 100;
    case 311312:return 100;
    case 213110:return 100;
    case 3113313:return 100;
    case 3133113:return 100;
    case 3131313:return 100;
    case 2311132:return 100;
    case 3113:return 100;
    case 31313:return 100;
    case 3112:return 40;
    case 2113:return 40;
    case 31312:return 40;
    case 21313:return 40;
    case 313312:return 40;
    case 213313:return 40;
    case 3133313:return 40;
    case 313:return 20;
    case 312:return 10;
    case 213:return 10;
    default:return 0;
}
}

void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece){
    int bound = (1<<31)-1;
    int step1,step2,step3,step4;
    int grade;
    int ifini = 0,ifskip = 0;
    int choice[225],cnt = 0;;

    for (step1 = 0;step1 < 225;step1 ++)
    {
        if (board[step1/15][step1%15] != '.'){
            continue;
        }
        board[step1/15][step1%15] = mpiece;

        for (step2 = 0;step2 < 225;step2 ++)
        {
            if (board[step2/15][step2%15] != '.'){
                continue;
            }
            board[step2/15][step2%15] = epiece;
            if (CheckIfEnd,step2/15,step2%15){
                board[step2/15][step2%15] = '.';
                break;
            }

            for (step3 = 0;step3 < 225;step3 ++)
            {   
                if (board[step3/15][step3%15] != '.'){
                    continue;
                }
                board[step3/15][step3%15] = mpiece;

                for (step4 = 0;step4 < 225;step4 ++)
                {
                    if (board[step4/15][step4%15] != '.'){
                        continue;
                    }
                    board[step4/15][step4%15] = epiece;
                    if (CheckIfEnd,step2/15,step2%15){
                        board[step2/15][step2%15] = '.';
                        ifskip = 1;
                        break;
                    }
                    
                    if (ifini == 0){
                        grade = CalculateGrade(board,mpiece);
                        if (grade < bound){
                            bound = grade;
                        }
                        else if (grade == bound)
                        {
                            choice[cnt] = step1;
                            cnt ++;
                        }
                    }
                    else
                    {
                        grade = CalculateGrade(board,mpiece);
                        if (grade < bound){
                            ifskip = 1;
                        }
                        else if (grade > bound){
                            bound = grade;
                            cnt = 0;
                            choice[cnt] = step1;
                            cnt ++;
                        }
                        else{
                            if (cnt < 225){
                                choice[cnt] = step1;
                                cnt ++;
                            }
                        }
                        
                    }

                    board[step4/15][step4%15] = '.';
                    if (ifskip == 1){
                        break;
                    }
                }
                if (ifini == 0){
                    ifini = 1;
                }

                board[step3/15][step3%15] = '.';
                if (ifskip == 1){
                        break;
                }
            }

            board[step2/15][step2%15] = '.';
            if (ifskip == 1){
                ifskip = 0;
                break;
            }
        }

        board[step1/15][step1%15] = '.';
    }

    int result = rand()%cnt;
    *maxi = choice[result]/15;
    *maxj = choice[result]%15;
    board[*maxi][*maxj] = mpiece;
}

int CheckIfEnd(char (*board)[15],int row,int column)
{
    char piece = board[row][column];
    int cnt = 0;

    for (row = 0;row < 15;row ++)
    {
        for (column = 0;column < 15;column ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    for (column = 0;column < 15;column ++)
    {
        for (row = 0;row < 15;row ++)
        {
            if (board[row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }
        }
        cnt = 0;
    }

    row = 15 - 1;
    while(row > 0)
    {   
        column = 0;
        int check_row = row;

        while(!(check_row == 15 || column == 15))
        {   
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column ++;
        }
        
        cnt = 0;
        row --;
    }

    column = 0;
    while(column != 15)
    {   
        row = 0;
        int check_column = column;

        while(!(row == 15 || check_column == 15))
        {
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column ++;
        }
        
        cnt = 0;
        column ++;
    }

    column = 0;
    while(column < 15)
    {   
        row = 0;
        int check_column = column;

        while(check_column > -1)
        {   
            if (board[row][check_column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            row ++;
            check_column --;
        }
        
        cnt = 0;
        column ++;
    }

    row = 0;
    while(row != 15)
    {   
        column = 0;
        int check_row = row;

        while(check_row < 15)
        {
            if (board[check_row][column] == piece)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }

            if (cnt == 5)
            {
                return 1;
            }

            check_row ++;
            column --;
        }
        
        cnt = 0;
        row ++;
    }
    
    return 0;
}

int main ()
{
    char a[15][15];
    for (int i = 0;i < 15;i ++){
        for (int j = 0;j < 15;j ++)
        {
            a[i][j] = '.';
        }
    }

    Game(i,j,a,'1','2');
    PRINT()

    // CalculateGrade(a,'1','2');

    // for (int i = 0;i < 15;i ++)
    // {   
    //     if (a[i] == '.'){
    //         a[i] = '2';
    //         int grade = CalculateLineGrade(a,'2',15,1) - CalculateLineGrade(a,'1',15,1);
    //         printf("%d\n",grade);
    //         a[i] = '.';
    //     }
    // }
}