#include<stdio.h>
#include "HEAD.h"
#include <windows.h>

int main(){
    setColor(6);  //�C�⬰���� 
    printf("\n\n\t\t�C������");
    printf("\n\ttips : \n");
    printf("\t   1.����6��MAX\n");
    printf("\t   2.�C���@��|�[�t�@�I\n");
    printf("\t   3.�������ܤ�V\n");
    printf("\t   4.�����[�t�V�U\n");
    printf("\t   5.�� ������V����\n");
    printf("\t   6.space�䬰��������\n");
    printf("\t   7.enter�䬰�R�����\n");
    Sleep(8000);                           //1000==1��A����delay -->��8��
    PlaySound(TEXT("count.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //��˼�3 2 1������
    system("cls");                         //�M�ŭ��� 
    printf("\n\n\n\t\t3");
    Sleep(1000);                           //��1��
    system("cls");                         //�M�ŭ��� 
    printf("\n\n\n\t\t2");
    Sleep(1000);                           //��1��
    system("cls");                         //�M�ŭ��� 
    printf("\n\n\n\t\t1");
    Sleep(1000);                           //��1��
    system("cls");                         //�M�ŭ��� 
    printf("\n\n\n\t\tGO!");
    Sleep(1000);                           //��1��
    system("cls");                         //�M�ŭ��� 
    PlaySound(TEXT("music_tetris.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //��tetris������
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
