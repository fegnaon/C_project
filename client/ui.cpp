#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"

void InitializeUI()
{
    initgraph(800,600,INIT_NOFORCEEXIT);
    setcaption("五子棋小游戏");
    setbkcolor(WHITE);
}

int LoginInterface(char *ac,char *psw,int tip)
{   
    ac[0] = '\0';
    psw[0] = '\0';
    setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);
    setfont(30,0,"黑体");
    outtextxy(290,50,"五子棋小游戏");
    setfont(24,0,"黑体");
    outtextxy(240,150,"账号:________________");
    outtextxy(500,150,"登录");
    outtextxy(560,150,"清空输入");
    outtextxy(240,200,"密码:________________");
    outtextxy(500,200,"注册");
    setfont(20,0,"黑体");
    switch (tip)
    {   
        case 0:break;
        case 1:setcolor(GREEN);outtextxy(300,240,"登录成功");break;
        case 2:setcolor(RED);outtextxy(300,240,"登录失败,账号不存在或密码错误");break;
        case 3:setcolor(RED);outtextxy(300,240,"该账号已登录，不能重复登录");break;
        case 4:setcolor(GREEN);outtextxy(300,240,"注册成功");break;
        case 5:setcolor(RED);outtextxy(300,240,"注册失败,该账号已存在");break;
    }
    setcolor(BLACK);
    setfont(24,0,"黑体");
    outtextxy(330,300,"单人游戏");
    outtextxy(330,350,"退出游戏");
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
            if (msg.x>=500&&msg.x<=550&&msg.y>=150&&msg.y<=175){//登录
                if (strlen(psw)==0||strlen(ac)==0){
                    setcolor(RED);
                    setfont(20,0,"黑体");
                    outtextxy(300,240,"密码或账号为空");
                    setfont(24,0,"黑体");
                    setcolor(BLACK);
                }
                else{
                    return 1;
                }
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=200&&msg.y<=225){//注册
                if (strlen(psw)==0||strlen(ac)==0){
                    setcolor(RED);
                    setfont(20,0,"黑体");
                    outtextxy(300,240,"密码或账号为空");
                    setfont(24,0,"黑体");
                    setcolor(BLACK);
                }
                else{
                    return 2;
                }
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=320){//单人游戏
                ifsingle = 1;
                outtextxy(460,300,"先手 后手");
            }
            if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=300&&msg.y<=320){//单人游戏先手
                return 30;
            }
            if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=300&&msg.y<=320){//单人游戏后手
                return 31;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=370){//退出游戏
                exit(0);
            }
            if (msg.x>=300&&msg.x<=500&&msg.y>=150&&msg.y<=170){//账号
                ifac = 1;
            }
            if (msg.x>=300&&msg.x<=500&&msg.y>=200&&msg.y<=220){//密码
                ifpsw = 1;
            }
            if (msg.x>=560&&msg.x<=660&&msg.y>=150&&msg.y<=170){//清空输入
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
    setfont(25,0,"黑体");
    outtextxy(500,100,"玩家1:");
    outtextxy(580,100,table.player0);
    outtextxy(500,150,"玩家2:");
    outtextxy(580,150,table.player1);
    char turntip[100] = "现在该";
    if (table.turn == -3){
        outtextxy(500,200,"你赢了!");
        outtextxy(500,250,"按任意键键返回");
        getch();
        return;
    }
    if (table.turn == -4){
        outtextxy(500,200,"你输了!");
        outtextxy(500,250,"按任意键键返回");
        getch();
        return;
    }
    if (table.turn >= 0){
        strcat(turntip,table.turn?table.player1:table.player0);
        strcat(turntip,"下棋了");
        outtextxy(500,200,turntip);
    }
    else{
        outtextxy(500,200,"玩家未满");
        outtextxy(500,250,"游戏暂未开始");
        outtextxy(500,300,"请等待...");
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

    setfont(30,0,"黑体");
    outtextxy(290,50,"五子棋小游戏");
    setfont(24,0,"黑体");
    outtextxy(240,150,"账号:");
    outtextxy(300,150,player.account);
    outtextxy(500,150,"修改密码");
    xyprintf(240,200,"胜:%d",player.win);
    xyprintf(360,200,"负:%d",player.lose);
    outtextxy(500,200,"切换账号");
    outtextxy(330,250,"单人游戏");
    outtextxy(330,300,"多人游戏");
    outtextxy(330,350,"退出游戏");

    int ifmul = 0,ifsingle = 0,ifnumber = 0,numberlen = 0;
    char number[10] = {0},input;
    if (mode == 1){
        ifmul = 1;
        outtextxy(460,300,"暗号:___ 确认");
        setcolor(RED);
        setfont(16,0,"黑体");
        outtextxy(620,300,"失败,已经有2个人");
        outtextxy(620,315,"正在用这个暗号了");
        setfont(24,0,"黑体");
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
            if (msg.x>=500&&msg.x<=600&&msg.y>=150&&msg.y<=175){//修改密码
                return 3;
            }
            if (msg.x>=500&&msg.x<=600&&msg.y>=200&&msg.y<=225){//切换账号
                return 4;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=250&&msg.y<=275){//单人游戏
                ifsingle = 1;
                outtextxy(460,250,"先手 后手");
            }
            if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=250&&msg.y<=275){//单人游戏先手
                outtextxy(500,350,"1");
                return 20;
            }
            if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=250&&msg.y<=275){//单人游戏先手
                return 21;
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=325){//多人游戏
                ifmul = 1;
                outtextxy(460,300,"暗号:___ 确认");
            }
            if (msg.x>=520&&msg.x<=560&&msg.y>=300&&msg.y<=325){//暗号输入
                ifnumber = 1;
            }
            if (ifmul==1&&msg.x>=570&&msg.x<=620&&msg.y>=300&&msg.y<=325){//确认
                if (strlen(number)==0){
                    setcolor(RED);
                    setfont(20,0,"黑体");
                    outtextxy(460,350,"不能为空");
                    setfont(24,0,"黑体");
                    setcolor(BLACK);
                }
                else{
                    player.table_number = atoi(number);
                    return 1;
                }
            }
            if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=375){//退出游戏
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
    psw[0] = '\0';
    setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);

    setfont(30,0,"黑体");
    outtextxy(290,50,"五子棋小游戏");
    outtextxy(300,125,"修改密码");
    setfont(24,0,"黑体");
    outtextxy(200,200,"新密码:________________");
    outtextxy(175,250,"确认密码:________________");
    outtextxy(500,200,"确认");
    outtextxy(500,250,"取消");
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
            if (msg.x>=280&&msg.x<=480&&msg.y>=200&&msg.y<=225){//新密码
                ifnpw = 1;
            }
            if (msg.x>=280&&msg.x<=480&&msg.y>=250&&msg.y<=275){//确认密码
                ifcnpw = 1;
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=200&&msg.y<=225){//确认
                if (strlen(npw)==0){
                    setcolor(RED);
                    setfont(20,0,"黑体");
                    outtextxy(280,300,"密码不能为空");
                    setfont(24,0,"黑体");
                    setcolor(BLACK);
                }
                else if (strcmp(npw,cnpw)){
                    setcolor(RED);
                    setfont(20,0,"黑体");
                    outtextxy(280,300,"两次密码不一致!");
                    setfont(24,0,"黑体");
                    setcolor(BLACK);
                }
                else{
                    strcpy(psw,npw);
                    return 1;
                }
            }
            if (msg.x>=500&&msg.x<=550&&msg.y>=250&&msg.y<=275){//取消
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