#include <stdlib.h>

typedef struct Leaf{
    int val;
    int grade;
}Leaf;

typedef struct Branch{
    int val;
    int grade;
    Leaf *leaves[255];
}Branch;

typedef struct Root{
    Branch *branches[255];
}Root;

// int CalculateGrade(char (*board)[15],char mpiece);

// void InitializeTree()
// {
//     int i,j;
//     for (i = 0;i < 255;i ++)
//     {
//         root.branches[i] = (Branch*)malloc(sizeof(Branch));
//         for (j = 0;j < 255;j ++)
//         {
//             root.branches[i]->leaves[j] = (Leaf*)malloc(sizeof(Leaf));
//             root.branches[i]->leaves[j]->grade = 0;
//             root.branches[i]->leaves[j]->val = 0;
//             root.branches[i]->grade = 0;
//             root.branches[i]->val = 0;
//         }
//     }
// }

// void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece)
// {
//     int lowerbound;
//     int upperbound;
//     int step1,step2,step3,skip = 0;
//     int max = (1<<31)-1,min = 1<<31;
//     int leafgrade,branchgrade;
//     int init = 0;
//     int choice;

//     for (step1 = 0;step1 < 225;step1 ++)
//     {
//         board[step1/15][step1%15] = mpiece;
//         init = 0;
//         for (step2 = 0;step1 < 225;step2 ++)
//         {   
//             if (board[step2/15][step2%15] != '.'){
//                 continue;
//             }
//             board[step2/15][step2%15] = epiece;
//             for (step3 = 0;step3 < 225;step3 ++)
//             {   
//                 if (board[step3/15][step3%15] != '.'){
//                     continue;
//                 }

//                 board[step3/15][step3%15] = mpiece;
//                 leafgrade = CalculateGrade(board,mpiece) - CalculateGrade(board,epiece);
//                 board[step3/15][step3%15] != '.';
//                 if (init == 1){
//                     if (leafgrade <= lowerbound){
//                         board[step3/15][step3%15] != '.';
//                         skip = 1;
//                     }
//                     else{
//                         if (leafgrade <= min){
//                             min = leafgrade;
//                         }
//                     }
//                 }
//                 else{
//                     if (leafgrade <= branchgrade){
//                         branchgrade = leafgrade;
//                     }
//                 }
//             }
//             board[step3/15][step3%15] = '.';
//             if (init == 0){
//                 lowerbound = branchgrade;
//                 init == 1;
//             }
//             else{
//                 if (skip == 1){
//                     skip = 0;
//                     break;
//                 }
//                 else{
//                     lowerbound = min;
//                     min = 1<<31;
//                 }
//             }
//         }
//         if (lowerbound >= max){
//             max = lowerbound;
//             choice = step1;
//         }
//     }

//     *maxi = choice/15;
//     *maxj = choice%15;
// }