    int all_grade = 0;
    int type = 0;
    int tag = 0;//tagΪ0��û��ʼ����1�ǽ�������2�ǿ�ʼ
    int zerocnt;
    int i,j;

//�����ŵ�
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
            if (tag == 1){//�����¼ֹͣ�ˣ��ͱ�������������tagΪδ��ʼ
                all_grade += TypeVal(type);
                // printf("%dhengtype = %d\n",j,type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//��δ��ʼ��¼���Ҷ���1����2ʱ��ʼ��¼
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
                if (board[i][j] == mpiece){//�ڿ�ʼ��¼������1ʱ����ֱ�Ӽ�¼
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//�ڿ�ʼ��¼ʱ�������2�ˣ��ȼ���Ƿ���Ҫ����2��Ȼ��ֹͣ��¼
                    if (!(type % 10 == 0 && type != 201110)){//�����һλ��0�Ҳ�Ϊ201110��һ�������ʱ���Ͳ�����2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//����ڿ�ʼ��¼��ʱ����0�ˣ��ȼ�¼���ټ���Ƿ������¼
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//���0�ĸ���Ϊ2���ͼ���Ƿ�Ӧ��ֹͣ
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//������ϼ�������������ͼ�����ȡ��һ������
                        else{//��������ϣ��ͰѼ�¼�Ķ��0ȥ��ֹͣ��¼
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
    
//������ŵ�
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
            if (tag == 1){//�����¼ֹͣ�ˣ��ͱ�������������tagΪδ��ʼ
                all_grade += TypeVal(type);
                // printf("%d shutype = %d\n",i,type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//��δ��ʼ��¼���Ҷ���1����2ʱ��ʼ��¼
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
                if (board[i][j] == mpiece){//�ڿ�ʼ��¼������1ʱ����ֱ�Ӽ�¼
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//�ڿ�ʼ��¼ʱ�������2�ˣ��ȼ���Ƿ���Ҫ����2��Ȼ��ֹͣ��¼
                    if (!(type % 10 == 0 && type != 201110)){//�����һλ��0�Ҳ�Ϊ201110��һ�������ʱ���Ͳ�����2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    continue;
                }
                if (board[i][j] == '.'){//����ڿ�ʼ��¼��ʱ����0�ˣ��ȼ�¼���ټ���Ƿ������¼
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//���0�ĸ���Ϊ2���ͼ���Ƿ�Ӧ��ֹͣ
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//������ϼ�������������ͼ�����ȡ��һ������
                        else{//��������ϣ��ͰѼ�¼�Ķ��0ȥ��ֹͣ��¼
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

//���б�ŵ�
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
            if (tag == 1){//�����¼ֹͣ�ˣ��ͱ�������������tagΪδ��ʼ
                all_grade += TypeVal(type);
                // printf("xietype = %d\n",type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//��δ��ʼ��¼���Ҷ���1����2ʱ��ʼ��¼
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
                if (board[i][j] == mpiece){//�ڿ�ʼ��¼������1ʱ����ֱ�Ӽ�¼
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//�ڿ�ʼ��¼ʱ�������2�ˣ��ȼ���Ƿ���Ҫ����2��Ȼ��ֹͣ��¼
                    if (!(type % 10 == 0 && type != 201110)){//�����һλ��0�Ҳ�Ϊ201110��һ�������ʱ���Ͳ�����2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//����ڿ�ʼ��¼��ʱ����0�ˣ��ȼ�¼���ټ���Ƿ������¼
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//���0�ĸ���Ϊ2���ͼ���Ƿ�Ӧ��ֹͣ
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//������ϼ�������������ͼ�����ȡ��һ������
                        else{//��������ϣ��ͰѼ�¼�Ķ��0ȥ��ֹͣ��¼
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
            if (tag == 1){//�����¼ֹͣ�ˣ��ͱ�������������tagΪδ��ʼ
                all_grade += TypeVal(type);
                // printf("xietype = %d\n",type);
                tag = 0;
                type = 0;
                zerocnt = 0;
            }
            if (tag == 0 && board[i][j] != '.'){//��δ��ʼ��¼���Ҷ���1����2ʱ��ʼ��¼
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
                if (board[i][j] == mpiece){//�ڿ�ʼ��¼������1ʱ����ֱ�Ӽ�¼
                    zerocnt = 0;
                    type = type * 10 + 1;
                    continue;
                }
                if (board[i][j] == epiece){//�ڿ�ʼ��¼ʱ�������2�ˣ��ȼ���Ƿ���Ҫ����2��Ȼ��ֹͣ��¼
                    if (!(type % 10 == 0 && type != 201110)){//�����һλ��0�Ҳ�Ϊ201110��һ�������ʱ���Ͳ�����2
                        type = type * 10 + 2;
                    }
                    tag = 1;
                    i --;
                    j --;
                    continue;
                }
                if (board[i][j] == '.'){//����ڿ�ʼ��¼��ʱ����0�ˣ��ȼ�¼���ټ���Ƿ������¼
                    type *= 10;
                    zerocnt ++;
                    if (zerocnt != 1){
                        if (zerocnt == 2){//���0�ĸ���Ϊ2���ͼ���Ƿ�Ӧ��ֹͣ
                            if (type == 1100 || type == 100 || type == 2100){
                                continue;
                            }
                        }
                        else if (zerocnt == 3 && type == 1000){
                            continue;
                        }//������ϼ�������������ͼ�����ȡ��һ������
                        else{//��������ϣ��ͰѼ�¼�Ķ��0ȥ��ֹͣ��¼
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