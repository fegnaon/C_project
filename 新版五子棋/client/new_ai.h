typedef struct Branch{

    struct Branch* branches;
}Branch;

typedef struct Root{
    int lowerbound1;
    int upperbound2;
    int lowerbound3;
    
}Root;

Root root;

int CalculateGrade(char (*board)[15],char mpiece);

void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece){
    int bound;
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

            for (step3 = 0;step2 < 225;step2 ++)
            {   
                if (board[step3/15][step3%15] != '.'){
                    continue;
                }
                board[step3/15][step3%15] = mpiece;

                for (step4 = 0;step2 < 225;step2 ++)
                {
                    if (board[step4/15][step4%15] != '.'){
                        continue;
                    }
                    board[step4/15][step4%15] = epiece;
                    
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
                        }
                        else{
                            cnt ++;
                            choice[cnt] = step1;
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
}