#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"

void InitializeUI()
{
    initgraph(800,600);
    setcaption("������С��Ϸ");
    setbkcolor(WHITE);
}

int LoginInterface(char *ac,char *psw,int tip)
{   
    setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);
    setfont(30,0,"����");
    outtextxy(290,50,"������С��Ϸ");
    setfont(24,0,"����");
    outtextxy(240,150,"�˺�:________________");
    outtextxy(500,150,"��¼");
    outtextxy(560,150,"�������");
    outtextxy(240,200,"����:________________");
    outtextxy(500,200,"ע��");
    setfont(20,0,"����");
    switch (tip)
    {   
        case 0:break;
        case 1:setcolor(GREEN);outtextxy(300,240,"��¼�ɹ�");break;
        case 2:setcolor(RED);outtextxy(300,240,"��¼ʧ��,�˺Ų����ڻ��������");break;
        case 3:setcolor(RED);outtextxy(300,240,"���˺��ѵ�¼�������ظ���¼");break;
        case 4:setcolor(GREEN);outtextxy(300,240,"ע��ɹ�");break;
        case 5:setcolor(RED);outtextxy(300,240,"ע��ʧ��,���˺��Ѵ���");break;
    }
    setcolor(BLACK);
    setfont(24,0,"����");
    outtextxy(330,300,"������Ϸ");
    outtextxy(330,350,"�˳���Ϸ");
    delay_ms(1);

    if (tip == 1){
        delay_ms(1000);
        printf("hhhhhh\n");
        return 0;
    }

    int x,y,b;
    int ifac = 0,ifpsw = 0,ifsingle = 0,aclen = 0,pswlen = 0;
    char spsw[20],input;
    for(;is_run();delay_fps(60))
    {
        while(mousemsg())
        {
            msg = getmouse();
        }

        // xyprintf(0, 0, "x = %10d  y = %10d",
        // msg.x, msg.y);

        if ((int)msg.is_left() == 1 && (int)msg.is_down() == 1){
            ifac = ifpsw = 0;
            if (msg.x>=500&&msg.x<=550&&msg.y>=150&&msg.y<=175){//��¼
                return 1;
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=150&&msg.y<=1750){//ע��
                return 2;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=320){//������Ϸ
                ifsingle = 1;
                outtextxy(460,300,"���� ����");
            }
            if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=300&&msg.y<=320){//������Ϸ����
                return 30;
            }
            if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=300&&msg.y<=320){//������Ϸ����
                return 31;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=370){//�˳���Ϸ
                exit(0);
            }
            if (msg.x>=300&&msg.x<=500&&msg.y>=150&&msg.y<=170){//�˺�
                ifac = 1;
            }
            if (msg.x>=300&&msg.x<=500&&msg.y>=200&&msg.y<=220){//����
                ifpsw = 1;
            }
            if (msg.x>=560&&msg.x<=660&&msg.y>=150&&msg.y<=170){//�������
                ac[0] = psw[0] = aclen = pswlen = 0;
                outtextxy(300,145,"                ");
                outtextxy(300,195,"                ");
            }
        }
        if (kbhit()){
            input = getch();
            if (ifac == 1){
                if ((aclen != 16 && isgraph(input))||(input == '\b' && aclen > 0)){
                    if (input == '\b'){
                        outtextxy(300,145,"                ");
                        aclen --;
                        ac[aclen] = '\0';
                    }
                    else{
                        ac[aclen] = input;
                        ac[aclen+1] = '\0';
                        aclen ++;
                    }
                    xyprintf(300,145,ac);
                }
            }
            if (ifpsw == 1){
                if ((pswlen != 16 && isgraph(input))||(input == '\b' && pswlen > 0)){
                    if (input == '\b'){
                        outtextxy(300,195,"                ");
                        pswlen --;
                        psw[pswlen] = '\0';
                        spsw[pswlen] = '\0';
                    }
                    else{
                        psw[pswlen] = input;
                        spsw[pswlen] = '*';
                        psw[pswlen+1] = '\0';
                        spsw[pswlen+1] = '\0';
                        pswlen ++;
                    }
                    xyprintf(300,195,spsw);
                }
            }
        }
    }
}

void GameInterface(Table table,int myturn,int* i,int* j)
{   
    setbkcolor(YELLOW);
    cleardevice();
    setcolor(BLACK);
    int x,y;
    for (x = 60,y = 60;y < 510;y += 30){
        line(x,y,x+420,y);
    }
    for (x = 60,y = 60;x < 510;x += 30){
        line(x,y,x,y+420);
    }
    int row,column;
    setfillcolor(BLACK);
    for (row = 0;row < 15;row ++)
    {
        for (column = 0;column < 15;column ++)
        {   
            if(table.board[row][column] == '0'){
                fillellipse((column+2)*30,(row+2)*30,13,13);
            }
        }
    }
    setfillcolor(WHITE);
    for (row = 0;row < 15;row ++)
    {
        for (column = 0;column < 15;column ++)
        {
            if(table.board[row][column] == '1'){
                fillellipse((column+2)*30,(row+2)*30,13,13);
            }
        }
    }

    setcolor(BLACK);
    setfont(25,0,"����");
    outtextxy(500,100,"���1:");
    outtextxy(580,100,table.player0);
    outtextxy(500,150,"���2:");
    outtextxy(580,150,table.player1);
    char turntip[100] = "���ڸ�";
    if (table.turn == -3){
        outtextxy(500,200,"��Ӯ��!");
        outtextxy(500,250,"�������������");
        getch();
        return;
    }
    if (table.turn == -4){
        outtextxy(500,200,"������!");
        outtextxy(500,250,"�������������");
        getch();
        return;
    }
    if (table.turn >= 0){
        strcat(turntip,table.turn?table.player1:table.player0);
        strcat(turntip,"������");
        outtextxy(500,200,turntip);
    }
    else{
        outtextxy(500,200,"���δ��");
        outtextxy(500,250,"��Ϸ��δ��ʼ");
        outtextxy(500,300,"��ȴ�...");
    }

    delay_ms(1);
    mouse_msg msg = {0};
    if (table.turn != myturn){
        return;
    }
    else{
        while(1)
        {
            while(mousemsg())
            {
                msg = getmouse();
            }

            if ((int)msg.is_left() == 1 && (int)msg.is_down() == 1){
                row = (msg.y-45)/30;
                column = (msg.x-45)/30;
                if (table.board[row][column] == '.' && row < 15 && msg.y-45 > -1 && msg.x-45 > -1 && column < 15){
                    *i = row;
                    *j = column;
                    return;
                }
            }
        }
    }
}

int MainMenuInterface(int mode)
{   
    setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);

    setfont(30,0,"����");
    outtextxy(290,50,"������С��Ϸ");
    setfont(24,0,"����");
    outtextxy(240,150,"�˺�:");
    outtextxy(300,150,player.account);
    outtextxy(500,150,"�޸�����");
    xyprintf(240,200,"ʤ:%d",player.win);
    xyprintf(360,200,"��:%d",player.lose);
    outtextxy(500,200,"�л��˺�");
    outtextxy(330,250,"������Ϸ");
    outtextxy(330,300,"������Ϸ");
    outtextxy(330,350,"�˳���Ϸ");

    int ifmul = 0,ifsingle = 0,ifnumber = 0,numberlen = 0;
    char number[10],input;
    if (mode == 1){
        ifmul = 1;
        outtextxy(460,300,"����:___ ȷ��");
        setcolor(RED);
        setfont(16,0,"����");
        outtextxy(620,300,"ʧ��,�Ѿ���2����");
        outtextxy(620,315,"���������������");
        setfont(24,0,"����");
        setcolor(BLACK);
    }
    delay_ms(1);

    for(;is_run();delay_fps(60))
    {   
        while(mousemsg())
        {
            msg = getmouse();
        }

        // xyprintf(0, 0, "x = %10d  y = %10d",
        // msg.x, msg.y);

        if ((int)msg.is_left() == 1 && (int)msg.is_down() == 1){
            ifnumber = 0;
            if (msg.x>=500&&msg.x<=600&&msg.y>=150&&msg.y<=175){//�޸�����
                return 3;
            }
            if (msg.x>=500&&msg.x<=600&&msg.y>=200&&msg.y<=225){//�л��˺�
                return 4;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=250&&msg.y<=275){//������Ϸ
                ifsingle = 1;
                outtextxy(460,250,"���� ����");
            }
            if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=250&&msg.y<=275){//������Ϸ����
                outtextxy(500,350,"1");
                return 20;
            }
            if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=250&&msg.y<=275){//������Ϸ����
                return 21;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=325){//������Ϸ
                ifmul = 1;
                outtextxy(460,300,"����:___ ȷ��");
            }
            if (msg.x>=520&&msg.x<=560&&msg.y>=300&&msg.y<=325){//��������
                ifnumber = 1;
            }
            if (ifmul==1&&msg.x>=570&&msg.x<=620&&msg.y>=300&&msg.y<=325){//ȷ��
                player.table_number = atoi(number);
                return 1;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=375){//�˳���Ϸ
                return 5;
            }
        }
        if (kbhit()){
            input = getch();
            if (ifnumber == 1){
                if ((numberlen != 2 && isdigit(input))||(input == 8 && numberlen > 0)){
                    if (input == 8){
                        outtextxy(520,295,"  ");
                        numberlen --;
                        number[numberlen] = '\0';
                    }
                    else{
                        number[numberlen] = input;
                        number[numberlen+1] = '\0';
                        numberlen ++;
                    }
                    xyprintf(520,295,number);
                }
            }
        }
    }
}

int ModifyInterface(char* psw)
{
    setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);

    setfont(30,0,"����");
    outtextxy(290,50,"������С��Ϸ");
    outtextxy(300,125,"�޸�����");
    setfont(24,0,"����");
    outtextxy(200,200,"������:________________");
    outtextxy(175,250,"ȷ������:________________");
    outtextxy(500,200,"ȷ��");
    outtextxy(500,250,"ȡ��");
    delay_ms(1);

    int ifnpw = 0,ifcnpw = 0,npwlen = 0,cnpwlen = 0;
    char npw[20],cnpw[20],snpw[20],scnpw[20],input;
    for(;is_run();delay_fps(60))
    {   
        while(mousemsg())
        {
            msg = getmouse();
        }

        // xyprintf(0, 0, "x = %10d  y = %10d",
        // msg.x, msg.y);

        if ((int)msg.is_left() == 1 && (int)msg.is_down() == 1){
            ifnpw = ifcnpw = 0;
            if (msg.x>=280&&msg.x<=480&&msg.y>=200&&msg.y<=225){//������
                ifnpw = 1;
            }
            if (msg.x>=280&&msg.x<=480&&msg.y>=250&&msg.y<=275){//ȷ������
                ifcnpw = 1;
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=200&&msg.y<=225){//ȷ��
                if (strcmp(npw,cnpw)){
                    setcolor(RED);
                    outtextxy(280,300,"�������벻һ��!");
                }
                else{
                    strcpy(psw,npw);
                    return 1;
                }
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=250&&msg.y<=275){//ȡ��
                return 0;
            }
        }
        if (kbhit()){
            input = getch();
            if (ifnpw == 1){
                if ((npwlen != 16 && isgraph(input))||(input == '\b' && npwlen > 0)){
                    if (input == '\b'){
                        outtextxy(280,195,"                ");
                        npwlen --;
                        snpw[npwlen] = '\0';
                        npw[npwlen] = '\0';
                    }
                    else{
                        npw[npwlen] = input;
                        snpw[npwlen] = '*';
                        npw[npwlen+1] = '\0';
                        snpw[npwlen+1] = '\0';
                        npwlen ++;
                    }
                    xyprintf(280,195,snpw);
                }
            }
            if (ifcnpw == 1){
                if ((cnpwlen != 16 && isgraph(input))||(input == '\b' && cnpwlen > 0)){
                    if (input == '\b'){
                        outtextxy(280,245,"                ");
                        cnpwlen --;
                        scnpw[cnpwlen] = '\0';
                        cnpw[cnpwlen] = '\0';
                    }
                    else{
                        cnpw[cnpwlen] = input;
                        scnpw[cnpwlen] = '*';
                        cnpw[cnpwlen+1] = '\0';
                        scnpw[cnpwlen+1] = '\0';
                        cnpwlen ++;
                    }
                    xyprintf(280,245,scnpw);
                }
            }
        }
    }
}