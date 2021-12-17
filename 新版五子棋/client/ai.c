#include <stdio.h>
#include <stdlib.h>

int CalculateGrade(char (*board)[15],char piece)
{   
    int all_grade = 0;
    int type = 0;
    int tag = 0;//tag为0是没开始，是1是结束，是2是开始
    int zerocnt;
    int i,j;
    for (i = 0;i < 15;i ++){
        zerocnt = 0;
        for (j = 0;j < 15;j ++){
            if (type == 11111){
                all_grade += 1000;break;
            }
            if (tag == 1){//如果记录停止了，就保存结果，并设置tag为未开始
                switch (type){
                    case 11110:all_grade += 800;break;
                    case 11112:all_grade += 40;break;
                    case 110112:all_grade += 40;break;
                    case 101112:all_grade += 40;break;
                    case 1110:all_grade += 30;break;
                    case 10110:all_grade += 30;break;
                    case 1112:all_grade += 20;break;
                    case 10112:all_grade += 20;break;
                    case 110010:all_grade += 20;break;
                    case 101010:all_grade += 20;break;
                    case 2011102:all_grade += 20;break;
                    case 110:all_grade += 10;break;
                    case 1010:all_grade += 10;break;
                    case 112:all_grade += 6;break;
                    case 1012:all_grade += 6;break;
                    case 10012:all_grade += 6;break;
                    case 100010:all_grade += 6;break;
                    case 10:all_grade += 4;break;
                    case 12:all_grade += 3;break;
                    case 211112:all_grade += 1;break;
                    case 21112:all_grade += 1;break;
                    case 2112:all_grade += 1;break;
                    case 212:all_grade += 1;break;

                    case 2:break;
                }
                type = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//在未开始记录并且读到1或者2时开始记录
                if (board[i][j] == '1'){
                    type += 1;
                }
                else{
                    type += 2;
                }
                tag = 2;
                zerocnt = 0;
                continue;
            }
            if (tag == 2){
                if (board[i][j] == '1'){//在开始记录并读到1时，就直接记录
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == '2'){//在开始记录时如果读到2了，先检查是否需要保存2，然后停止记录
                    if (!(type % 10 == 0 && type != 201110)){//当最后一位是0且不为201110这一特殊情况时，就不保存2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//如果在开始记录数时读到0了，先记录，再检查是否继续记录
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt == 2){//如果0的个数为2，就检查是否应该停止
                        if (type == 1100 || type == 100 || type == 2100){
                            continue;
                        }
                    }
                    else if (zerocnt == 3 && type == 1000){
                        continue;
                    }//如果符合几种特殊情况，就继续读取下一个棋子
                    else{//如果不符合，就把记录的多的0去掉停止记录
                        j -= zerocnt + 1;
                        for (;zerocnt != 1;zerocnt --){
                            type %= 10;
                        }
                        tag = 1;
                    }
                }
            }
        }
    }
    return all_grade;
}

int main()
{
    char a[15][15];
    int i,j;
    for (i = 0;i < 15;i ++)
    {
        for (j = 0;j < 15;j ++)
        {
            a[i][j] = '.';
        }
    }

    a[1][1] = '2';
    a[1][2] = '.';
    a[1][3] = '1';
    a[1][4] = '1';
    a[1][5] = '1';
    a[1][6] = '.';
    a[1][7] = '2';
    
    int grade = CalculateGrade(a,1);
    printf("%d",grade);
}