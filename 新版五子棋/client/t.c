#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "ai.h"

#define TYPENUM 42

Root root;
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

int AllType[TYPENUM] = {212,2112,21112,211112,2111112,
213,312,
313,
2113,3112,31312,21313,313312,213313,3133313,
3113,31313,31331,
31112,21113,313112,211313,311312,213113,3113313,3133113,3131313,2311132,
31113,313113,311313,313313,
311112,211113,3113112,2113113,3131112,2111313,
311113,
3111113,3111112,2111113};

int TypeVal(int type);
int CalculateGrade(char (*board)[15],char mpiece);

int CalculateLineGrade(char *line,char piece,int len,int ifstart);
int CheckIfEnd(char (*board)[15],int row,int column);

int PRINT(char *line,char piece,int len,int ifstart){
    for (int i = 0;i < len;i ++){
        printf("%c",line[i]);
    }
    printf("\n");
}

int CalculateLineGrade(char *line,char piece,int len,int ifstart)
{     
    if (len == 1){
        if (line[0] != piece){
        return 0;
        }else{
            return TypeVal(213);
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
        if (TypeVal(type)!=0){
        printf("type = %d,last = %d\n",type,last);
        }
        for (j = 0;j < 43;j ++){
            if (AllSonType[j] == type){
                ifinson = 1;
            }
        }
        for (j = 0;j < TYPENUM;j ++){
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
            ifinson = 0;
            ifintype = 0;
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
    if (TypeVal(type)!=0){
    printf("%d %d\n",type,TypeVal(type));
    }
    return TypeVal(type) + CalculateLineGrade(line+1,piece,len-1,0);
}

int CalculateGrade(char (*board)[15],char mpiece)
{   
    int grade = 0;
    int i,j;
    char line[15];
    for (i = 0;i < 15;i ++)
    {   
        // PRINT(board[i],mpiece,15,1);
        grade += CalculateLineGrade(board[i],mpiece,15,1);
    }
    for (j = 0;j < 15;j ++)
    {
        for (i = 0;i < 15;i ++){
            line[i] = board[i][j];
        }
        // PRINT(line,mpiece,15,1);
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
        // PRINT(line,mpiece,15-start,1);
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
        // PRINT(line,mpiece,15-start,1);
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
        // PRINT(line,mpiece,15-start,1);
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
        // PRINT(line,mpiece,start+1,1);
        grade += CalculateLineGrade(line,mpiece,start+1,1);
        cnt = 0;
        start ++;
    }
    
    return grade;
}

void Print_Board(char (*board)[15])
{   
    int row;
    int line;

    for (line = 0;line < 15;line ++)
    {
        for (row = 0;row < 15;row ++)
        {
            printf("%c ",board[line][row]);
        }
        printf("\n");
    }
}

// void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece){
//     int bound = (1<<31)-1;
//     int step1,step2,step3,step4;
//     int grade;
//     int ifini = 0,ifskip = 0;
//     int choice[225],cnt = 0;;

//     for (step1 = 0;step1 < 225;step1 ++)
//     {
//         if (board[step1/15][step1%15] != '.'){
//             continue;
//         }
//         board[step1/15][step1%15] = mpiece;

//         for (step2 = 0;step2 < 225;step2 ++)
//         {
//             if (board[step2/15][step2%15] != '.'){
//                 continue;
//             }
//             board[step2/15][step2%15] = epiece;
//             // if (CheckIfEnd,step2/15,step2%15){
//             //     board[step2/15][step2%15] = '.';
//             //     break;
//             // }

//             for (step3 = 0;step3 < 225;step3 ++)
//             {   
//                 if (board[step3/15][step3%15] != '.'){
//                     continue;
//                 }
//                 board[step3/15][step3%15] = mpiece;

//                 for (step4 = 0;step4 < 225;step4 ++)
//                 {
//                     if (board[step4/15][step4%15] != '.'){
//                         continue;
//                     }
//                     board[step4/15][step4%15] = epiece;
//                     // if (CheckIfEnd,step2/15,step2%15){
//                     //     board[step2/15][step2%15] = '.';
//                     //     ifskip = 1;
//                     //     break;
//                     // }
                    
//                     if (ifini == 0){
//                         grade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
//                         if (grade < bound){
//                             Print_Board(board);
//                             printf("分数:%d\n",grade);  
//                             bound = grade;
//                         }
//                         else if (grade == bound)
//                         {
//                             choice[cnt] = step1;
//                             cnt ++;
//                         }
//                     }
//                     else
//                     {
//                         grade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
//                         if (grade < bound){
//                             Print_Board(board);
//                             printf("skip分数:%d\n",grade);  
//                             ifskip = 1;
//                         }
//                         else if (grade > bound){
//                             Print_Board(board);
//                             printf("分数:%d\n",grade);  
//                             bound = grade;
//                             cnt = 0;
//                             choice[cnt] = step1;
//                             cnt ++;
//                         }
//                         else{
//                             if (cnt < 225){
//                                 choice[cnt] = step1;
//                                 cnt ++;
//                             }
//                         }
                        
//                     }

//                     board[step4/15][step4%15] = '.';
//                     if (ifskip == 1){
//                         ifskip = 0;
//                         break;
//                     }
//                 }
//                 if (ifini == 0){
//                     ifini = 1;
//                 }

//                 board[step3/15][step3%15] = '.';
//                 if (ifskip == 1){
//                     ifskip = 0;
//                     break;
//                 }
//             }

//             board[step2/15][step2%15] = '.';
//             // if (ifskip == 1){
//             //     ifskip = 0;
//             //     break;
//             // }
//         }

//         board[step1/15][step1%15] = '.';
//     }

//     int result = rand()%cnt;
//     *maxi = choice[result]/15;
//     *maxj = choice[result]%15;
//     board[*maxi][*maxj] = mpiece;
// }

void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece)
{
    int lowerbound;
    int step1,step2,step3,skip = 0;
    int max = 1<<31,min = (1<<31)-1;
    int leafgrade,branchgrade;
    int init = 0;
    int choice;

    for (step1 = 0;step1 < 225;step1 ++)
    {
        if (board[step1/15][step1%15] != '.'){
            continue;
        }
        board[step1/15][step1%15] = mpiece;
        init = 0;
        for (step2 = 0;step2 < 225;step2 ++)
        {
            if (board[step2/15][step2%15] != '.'){
                continue;
            }
            board[step2/15][step2%15] = epiece;
            for (step3 = 0;step3 < 225;step3 ++)
            {
                if (board[step3/15][step3%15] != '.'){
                    continue;
                }

                board[step3/15][step3%15] = mpiece;
                leafgrade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
                Print_Board(board);
                printf("分数:%d\n",leafgrade);
                board[step3/15][step3%15] = '.';
                if (init == 1){
                    if (leafgrade <= lowerbound){
                        printf("剪!!");
                        skip = 1;
                        break;
                    }
                    else{
                        if (leafgrade < min){
                            min = leafgrade;
                        }
                    }
                }
                else{
                    if (leafgrade <= branchgrade){
                        branchgrade = leafgrade;
                    }
                }
            }
            board[step2/15][step2%15] = '.';
            if (init == 0){
                min = branchgrade;
                lowerbound = branchgrade;
                branchgrade = (1<<31)-1;
                init = 1;
            }
            else{
                if (skip == 1){
                    skip = 0;
                    continue;
                }
                else{
                    lowerbound = branchgrade;
                }
            }
        }
        board[step1/15][step1%15] = '.';
        if (lowerbound >= max){
            max = lowerbound;
            choice = step1;
        }
        printf("\nstep%d finished!\n",step1);
    }

    *maxi = choice/15;
    *maxj = choice%15;
    board[*maxi][*maxj] = mpiece;
}

void oldGame(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece)
{
    int i,j,k,l;
    int mi[255] = {},mj[255] = {},cnt = 0;
    int cur1,cur2;
    int maxgrade = 1<<31;

    for (i = 0;i < 15;i ++)
    {   
        cur1 = i * 15;
        for (j = 0;j < 15;j ++)
        {   
            cur1 += j;
            if (board[i][j] == '.')
            {   
                root.branches[cur1]->val = 1;
                board[i][j] = mpiece;
                if (CalculateGrade(board,mpiece) - CalculateGrade(board,epiece) < maxgrade){
                    cur1 -= j;
                    board[i][j] = '.';
                    continue;
                }
                // root.branches[cur1]->grade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
                for (k = 0;k < 15;k ++)
                {   
                    cur2 = k * 15;
                    for (l = 0;l < 15;l ++)
                    {
                        cur2 += l;
                        if (board[k][l] == '.')
                        {   
                            root.branches[cur1]->leaves[cur2]->val = 1;
                            board[k][l] = epiece;
                            root.branches[cur1]->leaves[cur2]->grade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
                            // Print_Board(board);
                            // printf("分数:%d\n",root.branches[cur1]->leaves[cur2]->grade);  
                            
                            board[k][l] = '.';
                            
                            if (root.branches[cur1]->leaves[cur2]->grade == maxgrade){
                                if (cnt < 254){
                                    mi[cnt] = i;
                                    mj[cnt] = j;
                                    cnt ++;
                                }
                            }
                            else if (root.branches[cur1]->leaves[cur2]->grade > maxgrade){
                                cnt = 0;
                                mi[cnt] = i;
                                mj[cnt] = j;
                                cnt ++;
                                maxgrade = root.branches[cur1]->leaves[cur2]->grade;
                            }
                        }
                        else
                        {   
                            root.branches[cur1]->leaves[cur2]->val = 0;
                        }
                        cur2 -= l;
                    }
                }
                board[i][j] = '.';
            }
            else
            {   
                root.branches[cur1]->val = 1;
            }
            cur1 -= j;
        }
    }

    int re = rand();
    *maxi = mi[re%cnt];
    *maxj = mj[re%cnt];
    board[*maxi][*maxj] = mpiece;    
}

void AIDecide(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece){
    int row,column;
    char tboard[15][15];
    for (row = 0;row < 15;row ++){
        for (column = 0;column < 15;column ++){
            tboard[row][column] = board[row][column];
        }
    }

    int i,j;
    int mi[225],mj[225];
    int grade = 0;
    int maxgrade = -1000000;
    int cnt = 0;
    for (i = 0;i < 15;i ++){
        for (j = 0;j < 15;j ++){
            if (tboard[i][j] == '.')
            {
                tboard[i][j] = mpiece;
                grade = CalculateGrade(tboard,mpiece) - CalculateGrade(tboard,epiece);
                Print_Board(tboard);
                printf("分数:%d\n",grade);
                if (grade > maxgrade){
                    maxgrade = grade;
                    mi[0] = i;
                    mj[0] = j;
                    cnt = 1;
                }
                else if (grade == maxgrade){
                    mi[cnt] = i;
                    mj[cnt] = j;
                    cnt += 1;
                }
                tboard[i][j] = '.';
                grade = 0;
            }
        }
    }
    *maxi = mi[rand()%cnt];
    *maxj = mj[rand()%cnt];
}

void InitializeTree()
{
    int i,j;
    for (i = 0;i < 255;i ++)
    {
        root.branches[i] = (Branch*)malloc(sizeof(Branch));
        for (j = 0;j < 255;j ++)
        {
            root.branches[i]->leaves[j] = (Leaf*)malloc(sizeof(Leaf));
            root.branches[i]->leaves[j]->grade = 0;
            root.branches[i]->leaves[j]->val = 0;
            root.branches[i]->grade = 0;
            root.branches[i]->val = 0;
        }
    }
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

int main()
{   
    // InitializeTree();
    time_t a;
    srand(time(&a));
    int row,column;
    char board[15][15];
    for (row = 0;row < 15;row ++){
        for (column = 0;column < 15;column ++){
            board[row][column] = '.';
        }
    }

    
    // printf("AI1下棋!\n");
    // Game(&row,&column,board,'1','2');
    // // board[row][column] = '1';
    // if (CheckIfEnd(board,row,column)){printf("AI1胜利!!");}
    // // system("cls");
    // Print_Board(board);

    board[0][0] = '1';
    board[0][1] = '1';
    board[5][7] = '2';
    board[8][7] = '2';
    board[8][8] = '1';
    Print_Board(board);
    printf("grade = %d\n",CalculateGrade(board,'2'));

    // for (int i = 0;i < 15;i ++)
    // {
    //     for (int j = 0;j < 15;j ++)
    //     {   
    //         board[i][j] = '1';
    //         Print_Board(board);
    //         printf("grade = %d\n",CalculateGrade(board,'1'));
    //         board[i][j] = '.';
    //     }
    // }

    // int turn = 1;
    // while (1)
    // {   
    //     board[8][8] = '1';
    //     if (turn == 1){
    //         while(1)
    //         {
    //             printf("玩家下棋!:\n");
    //             scanf("%d %d",&row,&column);
    //             if (board[row-1][column-1] != '.'){
    //                 printf("已经有一个棋子了\n");
    //             }else{break;}
    //         }
    //         board[row-1][column-1] = '2';
    //         if (CheckIfEnd(board,row-1,column-1)){printf("玩家胜利!!");break;}
    //         // system("cls");
    //         Print_Board(board);
    //         // printf("AI2下棋!\n");
    //         // Game(&row,&column,board,'2','1');
    //         // // board[row][column] = '1';
    //         // if (CheckIfEnd(board,row,column)){printf("AI2胜利!!");break;}
    //         // // system("cls");
    //         // Print_Board(board);
    //     }
    //     else{
    //         printf("AI1下棋!\n");
    //         Game(&row,&column,board,'1','2');
    //         // board[row][column] = '1';
    //         if (CheckIfEnd(board,row,column)){printf("AI1胜利!!");break;}
    //         // system("cls");
    //         Print_Board(board);
    //     }
    //     turn = (turn + 1)%2;
    // }

}

int TypeVal(int type){
    switch (type){
    case 3111113:return 10000;
    case 3111112:return 10000;
    case 2111113:return 10000;
    case 311113:return 8000;
    case 311112:return 60;
    case 211113:return 60;
    case 3113112:return 60;
    case 2113113:return 60;
    case 3131112:return 60;
    case 2111313:return 60;
    case 31113:return 80;
    case 313313:return 5;
    case 313113:return 30;
    case 311313:return 30;
    case 31112:return 15;
    case 21113:return 15;
    case 313112:return 15;
    case 211313:return 15;
    case 311312:return 15;
    case 213110:return 15;
    case 3113313:return 15;
    case 3133113:return 15;
    case 3131313:return 15;
    case 2311132:return 15;
    case 3113:return 10;
    case 31313:return 10;
    case 3112:return 5;
    case 2113:return 5;
    case 31312:return 5;
    case 21313:return 5;
    case 313312:return 0;
    case 213313:return 0;
    case 3133313:return 5;
    case 313:return 4;
    case 312:return 1;
    case 213:return 1;
    default:return 0;
}
}