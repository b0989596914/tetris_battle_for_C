#include<stdio.h>
#include "HEAD.h"
#include <windows.h>

int main(){
    setColor(6);  //顏色為黃色 
    printf("\n\n\t\t遊戲說明");
    printf("\n\ttips : \n");
    printf("\t   1.等級6為MAX\n");
    printf("\t   2.每消一行會加速一點\n");
    printf("\t   3.↑為改變方向\n");
    printf("\t   4.↓為加速向下\n");
    printf("\t   5.← →為橫向移動\n");
    printf("\t   6.space鍵為瞬間降落\n");
    printf("\t   7.enter鍵為刪除方塊\n");
    Sleep(8000);                           //1000==1秒，類似delay -->停8秒
    PlaySound(TEXT("count.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //放倒數3 2 1的音樂
    system("cls");                         //清空頁面 
    printf("\n\n\n\t\t3");
    Sleep(1000);                           //停1秒
    system("cls");                         //清空頁面 
    printf("\n\n\n\t\t2");
    Sleep(1000);                           //停1秒
    system("cls");                         //清空頁面 
    printf("\n\n\n\t\t1");
    Sleep(1000);                           //停1秒
    system("cls");                         //清空頁面 
    printf("\n\n\n\t\tGO!");
    Sleep(1000);                           //停1秒
    system("cls");                         //清空頁面 
    PlaySound(TEXT("music_tetris.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //放tetris的音樂
    hand = GetStdHandle(STD_OUTPUT_HANDLE);
    setCursorVisable(0);
    print_surface();
    srand(time(NULL));
    make_new_block();
    print_block(current_block,cur_x,cur_y);
    set_timer(tm);
    key_control();
    system("pause") ;
    return 0;
}
