#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <graphics.h>

int main()
{
    initgraph(800,600);

    // setbkcolor(WHITE);
    // cleardevice();

    // mouse_msg msg = {0};
    // setcolor(BLACK);

    // setfont(30,0,"����");
    // outtextxy(290,50,"������С��Ϸ");
    // outtextxy(300,125,"�޸�����");
    // setfont(24,0,"����");
    // outtextxy(200,200,"������:________________");
    // outtextxy(175,250,"ȷ������:________________");
    // outtextxy(500,200,"ȷ��");
    // outtextxy(500,250,"ȡ��");

    // int ifnpw = 0,ifcnpw = 0,npwlen = 0,cnpwlen = 0;
    // char npw[20],cnpw[20],snpw[20],scnpw[20],input;
    // for(;is_run();delay_fps(60))
    // {   
    //     while(mousemsg())
    //     {
    //         msg = getmouse();
    //     }

    //     xyprintf(0, 0, "x = %10d  y = %10d",
    //     msg.x, msg.y);

    //     if ((int)msg.is_left() == 1){
    //         ifnpw = ifcnpw = 0;
    //         if (msg.x>=280&&msg.x<=480&&msg.y>=200&&msg.y<=225){//������
    //             ifnpw = 1;
    //         }
    //         if (msg.x>=280&&msg.x<=480&&msg.y>=250&&msg.y<=275){//ȷ������
    //             ifcnpw = 1;
    //         }
    //         if (msg.x>=500&&msg.x<=550&&msg.y>=200&&msg.y<=225){//ȷ��
    //             if (!strcmp(npw,cnpw)){
    //                 setcolor(RED);
    //                 outtextxy(280,300,"�������벻һ��!");
    //             }
    //             else{
    //                 return 
    //             }
    //             outtextxy(600,250,"���� ����");
    //         }
    //         if (msg.x>=500&&msg.x<=550&&msg.y>=250&&msg.y<=275){//ȡ��
    //             outtextxy(600,350,"1");
    //             return 20;
    //         }
    //     }
    //     if (kbhit()){
    //         input = getch();
    //         if (ifnpw == 1){
    //             if ((npwlen != 16 && isgraph(input))||(input == '\b' && npwlen > 0)){
    //                 if (input == '\b'){
    //                     outtextxy(280,195,"                ");
    //                     npwlen --;
    //                     snpw[npwlen] = '\0';
    //                     npw[npwlen] = '\0';
    //                 }
    //                 else{
    //                     npw[npwlen] = input;
    //                     snpw[npwlen] = '*';
    //                     npw[npwlen+1] = '\0';
    //                     snpw[npwlen+1] = '\0';
    //                     npwlen ++;
    //                 }
    //                 xyprintf(280,195,snpw);
    //             }
    //         }
    //         if (ifcnpw == 1){
    //             if ((cnpwlen != 16 && isgraph(input))||(input == '\b' && cnpwlen > 0)){
    //                 if (input == '\b'){
    //                     outtextxy(280,245,"                ");
    //                     cnpwlen --;
    //                     scnpw[cnpwlen] = '\0';
    //                     cnpw[cnpwlen] = '\0';
    //                 }
    //                 else{
    //                     cnpw[cnpwlen] = input;
    //                     scnpw[cnpwlen] = '*';
    //                     cnpw[cnpwlen+1] = '\0';
    //                     scnpw[cnpwlen+1] = '\0';
    //                     cnpwlen ++;
    //                 }
    //                 xyprintf(280,245,scnpw);
    //             }
    //         }
    //     }
    // }

    // ���˵�
        setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);

    setfont(30,0,"����");
    outtextxy(290,50,"������С��Ϸ");
    setfont(24,0,"����");
    outtextxy(240,150,"�˺�:");
    outtextxy(300,150,"feg");
    outtextxy(500,150,"�޸�����");
    xyprintf(240,200,"ʤ:%d",123);
    xyprintf(360,200,"��:%d",123);
    outtextxy(500,200,"�л��˺�");
    outtextxy(330,250,"������Ϸ");
    outtextxy(330,300,"������Ϸ");
    outtextxy(330,350,"�˳���Ϸ");
    delay_ms(1);
    int mode = 1;

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
    for(;is_run();delay_fps(60))
    {   
        while(mousemsg())
        {
            msg = getmouse();
        }

        xyprintf(0, 0, "x = %10d  y = %10d",
        msg.x, msg.y);

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
                ifnumber = atoi(number);
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



    //��ʼ

    // setfont(30,0,"����");
    // outtextxy(290,50,"������С��Ϸ");
    // setfont(24,0,"����");
    // outtextxy(240,150,"�˺�:________________");
    // outtextxy(500,150,"��¼");
    // outtextxy(560,150,"�������");
    // outtextxy(240,200,"����:________________");
    // outtextxy(500,200,"ע��");
    // setfont(20,0,"����");
    // switch (tip)
    // {   
    //     case 0:break;
    //     case 1:setcolor(GREEN);outtextxy(300,240,"��¼�ɹ�");delay(500);return 0;
    //     case 2:setcolor(RED);outtextxy(300,240,"��¼ʧ��,�˺Ų����ڻ��������");break;
    //     case 3:setcolor(RED);outtextxy(300,240,"���˺��ѵ�¼�������ظ���¼");break;
    //     case 4:setcolor(GREEN);outtextxy(300,240,"ע��ɹ�");break;
    //     case 5:setcolor(RED);outtextxy(300,240,"ע��ʧ��,���˺��Ѵ���");break;
    // }
    // setcolor(BLACK);
    // setfont(24,0,"����");
    // outtextxy(330,300,"������Ϸ");
    // outtextxy(330,350,"�˳���Ϸ");

    // int x,y,b;
    // int ifac = 0,ifpsw = 0,ifsingle = 0,aclen = 0,pswlen = 0;
    // char ac[20],psw[20],psws[20],input;
    // for(;is_run();delay_fps(60))
    // {   
    //     while(mousemsg())
    //     {
    //         msg = getmouse();
    //     }

    //     xyprintf(0, 0, "x = %10d  y = %10d",
    //     msg.x, msg.y);

    //     if ((int)msg.is_left() == 1){
    //         ifac = ifpsw = 0;
    //         if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=320){//������Ϸ
    //             ifsingle = 1;
    //             outtextxy(460,300,"���� ����");
    //         }
    //         if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=300&&msg.y<=320){//������Ϸ����
    //             outtextxy(480,350,"1");
    //             break;
    //         }
    //         if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=300&&msg.y<=320){//������Ϸ����
    //             outtextxy(480,350,"2");
    //         }
    //         if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=370){//�˳���Ϸ
    //             // outtextxy(330,500,"�˳���Ϸ");
    //         }
    //         if (msg.x>=300&&msg.x<=500&&msg.y>=150&&msg.y<=170){//�˺�
    //             ifac = 1;
    //             outtextxy(300,500,"�˳���Ϸ");
    //         }
    //         if (msg.x>=300&&msg.x<=500&&msg.y>=200&&msg.y<=220){//����
    //             ifpsw = 1;
    //             outtextxy(300,500,"�˳���Ϸ");
    //         }
    //         if (msg.x>=560&&msg.x<=660&&msg.y>=150&&msg.y<=170){//�������
    //             ac[0] = psw[0] = aclen = pswlen = 0;
    //             outtextxy(300,145,"                ");
    //             outtextxy(300,195,"                ");
    //         }
    //     }
    //     if (kbhit()){
    //         input = getch();
    //         if (ifac == 1){
    //             if (aclen != 16){
    //                 ac[aclen] = input;
    //                 ac[aclen+1] = '\0';
    //                 aclen ++;
    //                 xyprintf(300,145,ac);
    //             }
    //         }
    //         if (ifpsw == 1){
    //             if (pswlen != 16){
    //                 psw[pswlen] = input;
    //                 psws[pswlen] = '*';
    //                 psw[pswlen+1] = '\0';
    //                 psws[pswlen+1] = '\0';
    //                 pswlen ++;
    //                 xyprintf(300,195,psws);
    //             }
    //         }
    //     }
    // }
    // memset(&msg,0,sizeof(mouse_msg));
    // delay(100);
    // flushmouse();
    // cleardevice();
    // setbkcolor(YELLOW);

    // for (x = 60,y = 60;y < 510;y += 30){
    //     line(x,y,x+420,y);
    // }
    // for (x = 60,y = 60;x < 510;x += 30){
    //     line(x,y,x,y+420);
    // }

    // char board[15][15];
    // int row,column;
    // for (row = 0;row < 15;row ++)
    // {
    //     for (column = 0;column < 15;column ++)
    //     {
    //         board[row][column] = '.';
    //     }
    // }

    // setfillcolor(BLACK);
    // for (row = 0;row < 15;row ++)
    // {
    //     for (column = 0;column < 15;column ++)
    //     {   
            
    //         if(board[row][column] == 'X'){
    //             fillellipse((column+2)*30,(row+2)*30,13,13);
    //         }
    //     }
    // }
    // setfillcolor(WHITE);
    // for (row = 0;row < 15;row ++)
    // {
    //     for (column = 0;column < 15;column ++)
    //     {
    //         if(board[row][column] == 'O'){
    //             fillellipse((column+2)*30,(row+2)*30,13,13);
    //         }
    //     }
    // }

    // setfont(25,0,"����");
    // outtextxy(500,100,"���1:");
    // outtextxy(580,100,"fegnaon");
    // outtextxy(500,150,"���2:");
    // outtextxy(580,150,"kadxdz");

    // outtextxy(500,200,"���ڸ�AI������");
    // int turn = 1;


    // while(1)
    // {   
    //     while(mousemsg())
    //     {
    //         msg = getmouse();
    //     }

    //     xyprintf(0, 0, "x = %10d  y = %10d",
    //     msg.x, msg.y);

    //     if ((int)msg.is_left() == 1){
    //         if (turn == 1){
    //             setfillcolor(BLACK);
    //             row = (msg.y-45)/30;
    //             column = (msg.x-45)/30;
    //             if (board[row][column] == '.' && row < 15 && msg.y-45 > -1 && msg.x-45 > -1 && column < 15){
    //                 fillellipse((msg.x+15)/30*30,(msg.y+15)/30*30,13,13);
    //                 board[row][column] = 'X';
    //                 turn = (turn+1)%2;
    //             }
    //         }
    //         else{
    //             setfillcolor(WHITE);
    //             row = (msg.y-45)/30;
    //             column = (msg.x-45)/30;
    //             if (board[row][column] == '.' && row < 15 && msg.y-45 > -1 && msg.x-45 > -1 && column < 15){
    //                 fillellipse((msg.x+15)/30*30,(msg.y+15)/30*30,13,13);
    //                 board[row][column] = 'O';
    //                 turn = (turn+1)%2;
    //             }
    //         }
    //     }
    // }

    getch();
}