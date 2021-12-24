#include <stdlib.h>
#include "ai.h"

void InitializeAI()
{
    int i,j;
    for (i = 0;i < 255;i ++)
    {
        root.branches[i] = (Branch*)malloc(sizeof(Branch));
        for (j = 0;j < 255;j ++)
        {
            root.branches[i]->leaves[j] = (Leaf*)malloc(sizeof(Leaf));
            root.branches[i]->leaves[j]->grade = 0;
            root.branches[i]->grade = 0;
            root.branches[i]->val = 0;
        }
    }
}

void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece)//¾ö²ßº¯Êý
{
    int i,j,k,l;
    int mi[225] = {0},mj[225] = {0},cnt = 0;
    int position1,position2;
    int maxgrade = 1<<31;

    for (i = 0;i < 15;i ++)
    {
        position1 = i * 15;
        for (j = 0;j < 15;j ++)
        {
            position1 += j;
            if (board[i][j] == '.')
            {
                board[i][j] = mpiece;
                if (CalculateGrade(board,mpiece) - CalculateGrade(board,epiece) < maxgrade){
                    position1 -= j;
                    board[i][j] = '.';
                    continue;
                }
                root.branches[position1]->val = 1;
                root.branches[position1]->grade = (1<<31)-1;
                for (k = 0;k < 15;k ++)
                {   
                    position2 = k * 15;
                    for (l = 0;l < 15;l ++)
                    {
                        position2 += l;
                        if (board[k][l] == '.')
                        {
                            board[k][l] = epiece;
                            root.branches[position1]->leaves[position2]->grade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece)*2;
                            board[k][l] = '.';
                            
                            if (root.branches[position1]->leaves[position2]->grade < root.branches[position1]->grade){
                                root.branches[position1]->grade = root.branches[position1]->leaves[position2]->grade;
                            }
                        }
                        position2 -= l;
                    }
                }
                board[i][j] = '.';
            }
            else
            {   
                root.branches[position1]->val = 0;
            }
            position1 -= j;
        }
    }

    for (i = 0;i < 225;i ++)
    {
        if (root.branches[i]->val == 1){
            if (root.branches[i]->grade > maxgrade){
                maxgrade = root.branches[i]->grade;
                cnt = 0;
                mi[cnt] = i/15;
                mj[cnt] = i%15;
                cnt ++;
            }
            if (root.branches[i]->grade == maxgrade){
                mi[cnt] = i/15;
                mj[cnt] = i%15;
                cnt ++;
            }
        }
    }

    int re = rand();
    *maxi = mi[re%cnt];
    *maxj = mj[re%cnt];
}


int CalculateGrade(char (*board)[15],char mpiece)
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
    for (i = 0,j = 0;i < len;i ++){
        if (line[i] == '.'){
            j ++;
        }
    }
    if (j == len){
        return 0;
    }

    int ifinson = 0,ifintype = 0;
    int type = 0;
    int tag = 0,last = 0;
    if (ifstart == 1){
        type = 2;
    }

    for (i = 0;i < len;i ++){
        int a = (line[i] != '.')?((line[i] == piece)?1:2):3;
        type = type * 10 + a;

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

    return TypeVal(type) + CalculateLineGrade(line+1,piece,len-1,0);
}

int TypeVal(int type){
    switch (type)
    {
        case 3111113:return 10000000;
        case 2111112:return 10000000;
        case 3111112:return 10000000;
        case 2111113:return 10000000;
        case 311113:return 800000;
        case 311112:return 4000;
        case 211113:return 4000;
        case 3113112:return 4000;
        case 2113113:return 4000;
        case 3131112:return 4000;
        case 2111313:return 4000;
        case 31113:return 4000;
        case 313313:return 80;
        case 313113:return 4000;
        case 311313:return 4000;
        case 31112:return 1500;
        case 21113:return 1500;
        case 313112:return 1500;
        case 211313:return 1500;
        case 311312:return 1500;
        case 213113:return 1500;
        case 3113313:return 1500;
        case 3133113:return 1500;
        case 3131313:return 1500;
        case 2311132:return 1500;
        case 3113:return 1000;
        case 31313:return 1000;
        case 3112:return 1000;
        case 2113:return 1000;
        case 31312:return 1000;
        case 21313:return 1000;
        case 313312:return 200;
        case 213313:return 200;
        case 3133313:return 200;
        case 313:return 40;
        case 312:return 20;
        case 213:return 20;
        default:return 0;
    }
}