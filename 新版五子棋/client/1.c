    int all_grade = 0;
    int type = 0;
    int tag = 0;//tag为0是没开始，是1是结束，是2是开始
    int zerocnt;
    int i,j;

//检查横着的
    for (i = 0;i < 15;i ++){
        zerocnt = 0;
        tag = 0;
        type = 0;
        for (j = 0;j < 15;j ++){
            // printf("%d\n",type);
            if (j == 14){
                type = type * 10 + (board[i][j] == mpiece)?1:(board[i][j] == epiece)?2:0;
                tag = 1;
            }
            if (type == 11111){
                all_grade += 10000;
                type = 0;
                zerocnt = 0;
                tag = 0;
            }
            if (tag == 1){//如果记录停止了，就保存结果，并设置tag为未开始
                all_grade += TypeVal(type);
                // printf("%dhengtype = %d\n",j,type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//在未开始记录并且读到1或者2时开始记录
                if (board[i][j] == mpiece){
                    type += 1;
                }
                else{
                    type += 2;
                }
                tag = 2;
                continue;
            }
            if (tag == 2){
                if (board[i][j] == mpiece){//在开始记录并读到1时，就直接记录
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//在开始记录时如果读到2了，先检查是否需要保存2，然后停止记录
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
                    if (zerocnt != 1){
                        if (zerocnt == 2){//如果0的个数为2，就检查是否应该停止
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//如果符合几种特殊情况，就继续读取下一个棋子
                        else{//如果不符合，就把记录的多的0去掉停止记录
                            for (zerocnt;zerocnt != 1;zerocnt --){
                                type /= 10; 
                            }
                            tag = 1;
                        }
                    }
                    else{
                        if (type == 11110 || type == 211110 || type == 2110110 || type == 2111010 || type == 1110 || type == 10110 || type == 11010 || type == 110010 || type == 101010 || type == 211010 || type == 210110 || type == 100110 || type == 100010 || type == 21010 || type == 210010){
                            tag = 1;
                            j -= 2;
                        }
                    }
                }
            }
        }
    }
    
//检查竖着的
    for (j = 0;j < 15;j ++){
        tag = 0;
        type = 0;
        zerocnt = 0;
        for (i = 0;i < 15;i ++){
            // printf("%d\n",type);
            if (i == 14){
                type = type * 10 + (board[i][j] == mpiece)?1:(board[i][j] == epiece)?2:0;
                tag = 1;
            }
            if (type == 11111){
                all_grade += 10000;
                type = 0;
                zerocnt = 0;
                tag = 0;
            }
            if (tag == 1){//如果记录停止了，就保存结果，并设置tag为未开始
                all_grade += TypeVal(type);
                // printf("%d shutype = %d\n",i,type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//在未开始记录并且读到1或者2时开始记录
                if (board[i][j] == mpiece){
                    type += 1;
                }
                else{
                    type += 2;
                }
                tag = 2;
                continue;
            }
            if (tag == 2){
                if (board[i][j] == mpiece){//在开始记录并读到1时，就直接记录
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//在开始记录时如果读到2了，先检查是否需要保存2，然后停止记录
                    if (!(type % 10 == 0 && type != 201110)){//当最后一位是0且不为201110这一特殊情况时，就不保存2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    continue;
                }
                if (board[i][j] == '.'){//如果在开始记录数时读到0了，先记录，再检查是否继续记录
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//如果0的个数为2，就检查是否应该停止
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//如果符合几种特殊情况，就继续读取下一个棋子
                        else{//如果不符合，就把记录的多的0去掉停止记录
                            for (zerocnt;zerocnt != 1;zerocnt --){
                                type /= 10; 
                            }
                            tag = 1;
                        }
                    }
                    else{
                        if (type == 11110 || type == 211110 || type == 2110110 || type == 2111010 || type == 1110 || type == 10110 || type == 11010 || type == 110010 || type == 101010 || type == 211010 || type == 210110 || type == 100110 || type == 100010 || type == 21010 || type == 210010){
                            tag = 1;
                            i -= 2;
                        }
                    }
                }
            }
        }
    }

//检查斜着的
    int is = 14;
    while (is != -1)
    {   
        tag = 0;
        type = 0;
        zerocnt = 0;
        for (i = is,j = 0;i < 15;i ++,j ++){
            // printf("%d\n",type);
            if (i == 14){
                type = type * 10 + (board[i][j] == mpiece)?1:(board[i][j] == epiece)?2:0;
                tag = 1;
            }
            if (type == 11111){
                all_grade += 10000;
                type = 0;
                zerocnt = 0;
                tag = 0;
            }
            if (tag == 1){//如果记录停止了，就保存结果，并设置tag为未开始
                all_grade += TypeVal(type);
                // printf("xietype = %d\n",type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//在未开始记录并且读到1或者2时开始记录
                if (board[i][j] == mpiece){
                    type += 1;
                }
                else{
                    type += 2;
                }
                tag = 2;
                continue;
            }
            if (tag == 2){
                if (board[i][j] == mpiece){//在开始记录并读到1时，就直接记录
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//在开始记录时如果读到2了，先检查是否需要保存2，然后停止记录
                    if (!(type % 10 == 0 && type != 201110)){//当最后一位是0且不为201110这一特殊情况时，就不保存2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//如果在开始记录数时读到0了，先记录，再检查是否继续记录
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//如果0的个数为2，就检查是否应该停止
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//如果符合几种特殊情况，就继续读取下一个棋子
                        else{//如果不符合，就把记录的多的0去掉停止记录
                            for (zerocnt;zerocnt != 1;zerocnt --){
                                type /= 10; 
                            }
                            tag = 1;
                        }
                    }
                    else{
                        if (type == 11110 || type == 211110 || type == 2110110 || type == 2111010 || type == 1110 || type == 10110 || type == 11010 || type == 110010 || type == 101010 || type == 211010 || type == 210110 || type == 100110 || type == 100010 || type == 21010 || type == 210010){
                            tag = 1;
                            i -= 2;
                            j -= 2;
                        }
                    }
                }
            }
        }
    is --;
    }

    int js = 14;
    while (js != 0)
    {
        tag = 0;
        type = 0;
        zerocnt = 0;
        for (i = 0,j = js;j < 15;i ++,j ++){
            // printf("%d\n",type);
            if (j == 14){
                type = type * 10 + (board[i][j] == mpiece)?1:(board[i][j] == epiece)?2:0;
                tag = 1;
            }
            if (type == 11111){
                all_grade += 10000;
                type = 0;
                zerocnt = 0;
                tag = 0;
            }
            if (tag == 1){//如果记录停止了，就保存结果，并设置tag为未开始
                all_grade += TypeVal(type);
                // printf("xietype = %d\n",type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//在未开始记录并且读到1或者2时开始记录
                if (board[i][j] == mpiece){
                    type += 1;
                }
                else{
                    type += 2;
                }
                tag = 2;
                continue;
            }
            if (tag == 2){
                if (board[i][j] == mpiece){//在开始记录并读到1时，就直接记录
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//在开始记录时如果读到2了，先检查是否需要保存2，然后停止记录
                    if (!(type % 10 == 0 && type != 201110)){//当最后一位是0且不为201110这一特殊情况时，就不保存2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//如果在开始记录数时读到0了，先记录，再检查是否继续记录
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//如果0的个数为2，就检查是否应该停止
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//如果符合几种特殊情况，就继续读取下一个棋子
                        else{//如果不符合，就把记录的多的0去掉停止记录
                            for (zerocnt;zerocnt != 1;zerocnt --){
                                type /= 10; 
                            }
                            tag = 1;
                        }
                    }
                    else{
                        if (type == 11110 || type == 211110 || type == 2110110 || type == 2111010 || type == 1110 || type == 10110 || type == 11010 || type == 110010 || type == 101010 || type == 211010 || type == 210110 || type == 100110 || type == 100010 || type == 21010 || type == 210010){
                            tag = 1;
                            i -= 2;
                            j -= 2;
                        }
                    }
                }
            }
        }
    js --;
    }
    return all_grade;