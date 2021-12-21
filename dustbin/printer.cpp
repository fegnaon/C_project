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

    // setfont(30,0,"黑体");
    // outtextxy(290,50,"五子棋小游戏");
    // outtextxy(300,125,"修改密码");
    // setfont(24,0,"黑体");
    // outtextxy(200,200,"新密码:________________");
    // outtextxy(175,250,"确认密码:________________");
    // outtextxy(500,200,"确认");
    // outtextxy(500,250,"取消");

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
    //         if (msg.x>=280&&msg.x<=480&&msg.y>=200&&msg.y<=225){//新密码
    //             ifnpw = 1;
    //         }
    //         if (msg.x>=280&&msg.x<=480&&msg.y>=250&&msg.y<=275){//确认密码
    //             ifcnpw = 1;
    //         }
    //         if (msg.x>=500&&msg.x<=550&&msg.y>=200&&msg.y<=225){//确认
    //             if (!strcmp(npw,cnpw)){
    //                 setcolor(RED);
    //                 outtextxy(280,300,"两次密码不一致!");
    //             }
    //             else{
    //                 return 
    //             }
    //             outtextxy(600,250,"先手 后手");
    //         }
    //         if (msg.x>=500&&msg.x<=550&&msg.y>=250&&msg.y<=275){//取消
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

    // 主菜单
        setbkcolor(WHITE);
    cleardevice();

    mouse_msg msg = {0};
    setcolor(BLACK);

    setfont(30,0,"黑体");
    outtextxy(290,50,"五子棋小游戏");
    setfont(24,0,"黑体");
    outtextxy(240,150,"账号:");
    outtextxy(300,150,"feg");
    outtextxy(500,150,"修改密码");
    xyprintf(240,200,"胜:%d",123);
    xyprintf(360,200,"负:%d",123);
    outtextxy(500,200,"切换账号");
    outtextxy(330,250,"单人游戏");
    outtextxy(330,300,"多人游戏");
    outtextxy(330,350,"退出游戏");
    delay_ms(1);
    int mode = 1;

    int ifmul = 0,ifsingle = 0,ifnumber = 0,numberlen = 0;
    char number[10],input;
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
                ifnumber = atoi(number);
                return 1;
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



    //初始

    // setfont(30,0,"黑体");
    // outtextxy(290,50,"五子棋小游戏");
    // setfont(24,0,"黑体");
    // outtextxy(240,150,"账号:________________");
    // outtextxy(500,150,"登录");
    // outtextxy(560,150,"清空输入");
    // outtextxy(240,200,"密码:________________");
    // outtextxy(500,200,"注册");
    // setfont(20,0,"黑体");
    // switch (tip)
    // {   
    //     case 0:break;
    //     case 1:setcolor(GREEN);outtextxy(300,240,"登录成功");delay(500);return 0;
    //     case 2:setcolor(RED);outtextxy(300,240,"登录失败,账号不存在或密码错误");break;
    //     case 3:setcolor(RED);outtextxy(300,240,"该账号已登录，不能重复登录");break;
    //     case 4:setcolor(GREEN);outtextxy(300,240,"注册成功");break;
    //     case 5:setcolor(RED);outtextxy(300,240,"注册失败,该账号已存在");break;
    // }
    // setcolor(BLACK);
    // setfont(24,0,"黑体");
    // outtextxy(330,300,"单人游戏");
    // outtextxy(330,350,"退出游戏");

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
    //         if (msg.x>=330&&msg.x<=430&&msg.y>=300&&msg.y<=320){//单人游戏
    //             ifsingle = 1;
    //             outtextxy(460,300,"先手 后手");
    //         }
    //         if (ifsingle == 1&&msg.x>=460&&msg.x<=510&&msg.y>=300&&msg.y<=320){//单人游戏先手
    //             outtextxy(480,350,"1");
    //             break;
    //         }
    //         if (ifsingle == 1&&msg.x>=520&&msg.x<=570&&msg.y>=300&&msg.y<=320){//单人游戏先手
    //             outtextxy(480,350,"2");
    //         }
    //         if (msg.x>=330&&msg.x<=430&&msg.y>=350&&msg.y<=370){//退出游戏
    //             // outtextxy(330,500,"退出游戏");
    //         }
    //         if (msg.x>=300&&msg.x<=500&&msg.y>=150&&msg.y<=170){//账号
    //             ifac = 1;
    //             outtextxy(300,500,"退出游戏");
    //         }
    //         if (msg.x>=300&&msg.x<=500&&msg.y>=200&&msg.y<=220){//密码
    //             ifpsw = 1;
    //             outtextxy(300,500,"退出游戏");
    //         }
    //         if (msg.x>=560&&msg.x<=660&&msg.y>=150&&msg.y<=170){//清空输入
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

    // setfont(25,0,"黑体");
    // outtextxy(500,100,"玩家1:");
    // outtextxy(580,100,"fegnaon");
    // outtextxy(500,150,"玩家2:");
    // outtextxy(580,150,"kadxdz");

    // outtextxy(500,200,"现在该AI下棋了");
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