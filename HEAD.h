#include<stdio.h>
#include<stdlib.h>
#include <conio.h>       
#include<time.h>
#include <windows.h>
#define HEIGHT 14
#define WIDTH 18
#define block_h 4
#define block_w 4

enum block_type{                         //�`�@���o7�ؤ��
    O,J,L,I,Z,S,T
};
 
int block_type_num = 7;                  //�n�]�üƪ��`��
int cur_x=0,cur_y=0;  
int color_to_change_pattern;             //�O���C�� --> ���ܧΪ�
int over=0;                              //�P�_�C���O�_����

int Block0[block_h][block_w] = {         //�����
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockJ[block_h][block_w] = {         //J��
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockL[block_h][block_w] = {         //L��
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockI[block_h][block_w] = {         //I��
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
};

int BlockZ[block_h][block_w] = {         //Z��
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockS[block_h][block_w] = {         //S��
    {0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}
};

int BlockT[block_h][block_w] = {         //T��
    {0,0,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};

int current_block[block_h][block_w]; 
int surface[HEIGHT][WIDTH] = {0} ;

void print_block(int block[][block_w],int x,int y);
void copy_block(int block_s[][block_w],int block_d[][block_w]);
void make_new_block();
void rotate_block();
void land_block();
int get_block_x_fill(int col);
int get_block_y_fill(int row);
void get_block_top_bottom_margin(int *top_margin, int *bottom_margin);
void get_block_left_right_margin(int *left_margin, int *right_margin);
int isCollision(int x,int y);
void print_surface();
void setCursorVisable(int v);
void gotoxy(int x,int y);
void printxy(char*str , int x, int y );
void erase_block(int block[][block_w],int x,int y);
void setColor(int color);
void clear_one_line(int h);
int is_line_fill(int h);
void check_line();
static void set_timer(int t);
static void close_timer();
void move_block_down();
void key_control();

int tm = 800;
UINT_PTR timerId;
MSG msg;
int score=0;
int level=0;

void print_block(int block[][block_w],int x,int y){     //�L�X����Ϊ�
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(block[h][w]==1 && over==0){              //�p�G�S���� && =1
                if(color_to_change_pattern==2){         //�p�G�C��O���
                    printxy("+",x+w,y+h);               //�L�X'+'
                }
                else if(color_to_change_pattern==14){   //�p�G�C��O�H����
                    printxy("X",x+w,y+h);               //�L�X'X'
                }
                else if(color_to_change_pattern==8){    //�p�G�C��O�Ǧ�
                    printxy("#",x+w,y+h);               //�L�X'#'
                }
                else if(color_to_change_pattern==12){   //�p�G�C��O�����
                    printxy("$",x+w,y+h);               //�L�X'$'
                }
                else if(color_to_change_pattern==6){    //�p�G�C��O����
                    printxy("&",x+w,y+h);               //�L�X'&'
                }
                else if(color_to_change_pattern==9){    //�p�G�C��O�Ŧ�
                    printxy("~",x+w,y+h);               //�L�X'~'
                }
                else if(color_to_change_pattern==11){   //�p�G�C��O�ź��
                    printxy("@",x+w,y+h);               //�L�X'@'
                }
            }
        }
    }
}

void copy_block(int block_s[][block_w],int block_d[][block_w]){    //�ƻs���
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            block_d[h][w] = block_s[h][w];
        }
    }
}

void make_new_block(){ 
    enum block_type type = (int)(rand()%block_type_num);   //�H����ܤ@�ؤ��
    switch(type){                                 //�Ncurrent_block�ܦ��H�����ͪ����(���ͤ��)
        case O:
            setColor(2);                          //�]�w�C��=2
            color_to_change_pattern=2;            //�O���C��
            copy_block(Block0,current_block);
            break;
        case J:
            setColor(14);                         //�]�w�C��=14
            color_to_change_pattern=14;
            copy_block(BlockJ,current_block);
            break;
        case L:
            setColor(8);                          //�]�w�C��=8
            color_to_change_pattern=8;
            copy_block(BlockL,current_block);
            break;
        case I:
            setColor(12);                         //�]�w�C��=12
            color_to_change_pattern=12;
            copy_block(BlockI,current_block);
            break;
        case Z:
            setColor(6);                          //�]�w�C��=6
            color_to_change_pattern=6;
            copy_block(BlockZ,current_block);
            break;
        case S:
            setColor(9);                          //�]�w�C��=9
            color_to_change_pattern=9;
            copy_block(BlockS,current_block);
            break;
        case T:
            setColor(11);                         //�]�w�C��=11
            color_to_change_pattern=11;
            copy_block(BlockT,current_block);
            break;
        default:
            break;
    }
    cur_x = (WIDTH-block_w)/2;                    //���ͪ���m
    cur_y = 0;
}

void rotate_block(){                              //������
    int temp[block_h][block_w] = {0};
    copy_block(current_block,temp);
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            current_block[h][w] = temp[block_w-1-w][h];
        }
    }
}

void land_block(){                //������w�����
    int w,h; 
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(current_block[h][w]==1){
                surface[cur_y+h][cur_x+w]=1;
            }
        }
    }
}

int get_block_x_fill(int col){    
    int is_fill = 0;
    int row;
    for(row=0;row<block_w;row++){
        if(current_block[row][col]==1){
            return 1;
        }
    }
    return is_fill;
}

int get_block_y_fill(int row){         //�ǤJ�����row --> �ˬd�O���O�u�������
    int is_fill =0;
    int col;
    for(col=0;col<block_w;col++){      //�ˬd������A��row���C��col�A�O���O�u�������(1)
        if(current_block[row][col]==1){
            is_fill=1;
        }
    }
    return is_fill;
}

void get_block_top_bottom_margin(int *top_margin, int *bottom_margin){
    int i = 0;
    for(i=0;i<block_h/2;i++){
        if(get_block_y_fill(i)==0){
            (*top_margin)+=1;
        }
    }
    for(i=block_h-1;i>=block_h/2;i--){
        if(get_block_y_fill(i)==0){
            (*bottom_margin)+=1;
        }
    }
}

void get_block_left_right_margin(int *left_margin, int *right_margin){    //�p��W�U���k�䪺����
    int i = 0;
    for(i=0;i<block_w/2;i++){             //�ˬd���b�䪺����
        if(get_block_x_fill(i)==0){
            (*left_margin)+=1;
        }
    }
    for(i=block_w-1;i>=block_w/2;i--){     //�ˬd�k�b�䪺����
        if(get_block_x_fill(i)==0){
            (*right_margin)+=1;
        }
    }
}

int isCollision(int x,int y){              //��ɧP�_
    int top = 0,bottom = 0,left = 0,right = 0;
    get_block_left_right_margin(&left,&right);
    get_block_top_bottom_margin(&top,&bottom);
    if(x<0-left || x+block_w>WIDTH+right){
        return 1;
    }
    else if(y<0-top || y+block_h>HEIGHT+bottom){
        return 1;
    }
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(current_block[h][w]==1){
                if(surface[y+h][x+w]==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void print_surface(){                             //�C�L�e��
    int x,y;
    for(x=0;x<=WIDTH;x++){
        for(y=0;y<HEIGHT;y++){
            int row = y;
            int col = x;
            if(surface[row][col]==0){
                printxy(" ",x,y); 
            }
            if(score<310){                        // level 1
                level=1;
            }
            else if(score>400 && score<3100){     // level 2
                level=2;
            }
            else if(score>3100 && score<=6000){   // level 3
                level=3;
            }
            else if(score>6000 && score<=10000){  // level 4
                level=4;
            }
            else if(score>10000 && score<=20000){ // level 5
                level=5;
            }
            else if(score>20000){                 // level6
                level=6;
            }
            if(x == WIDTH && y == 0){
                setColor(7);
                printf("score : %d\n",score);
            }
            else if(x == WIDTH && y == 1){
                setColor(7);
                printf("level : %d\n",level);
            }
            else if(x == WIDTH && y == 2){
                setColor(7);
                printf("enter is delete\n");
            }
            else if(x == WIDTH && y == 3){
                setColor(7);
                printf("space is down rapidly\n");
            }
        }
    }
}

HANDLE hand;

void setCursorVisable(int v){ 
    CONSOLE_CURSOR_INFO cursor_info = {100,v};
    SetConsoleCursorInfo(hand,&cursor_info);
}

void gotoxy(int x,int y){                    //���cursor��m�æC�L
    COORD loc;
    loc.X = x;
    loc.Y = y;
    SetConsoleCursorPosition(hand,loc);
}

void printxy(char*str , int x, int y ){     //���cursor��m�æC�L
    gotoxy(x,y);
    printf("%s",str);
}

void erase_block(int block[][block_w],int x,int y){    //�C�L+�Ȱ�+�������
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(block[h][w]==1){
                printxy(" ",x+w,y+h); 
            }
        }
    }
}

void clear_one_line(int h){                          //�M���s�u
    int w,row; 
    for(row = h;row>0;row--){
        for(w=0;w<WIDTH;w++){
            surface[row][w] = surface[row-1][w];
        }
    }
    for(w=0;w<WIDTH;w++){
        surface[0][w] = 0;
    }
}

int is_line_fill(int h){                            //�O�_�s�u
    int w;
    for(w=0;w<WIDTH;w++){
        if(surface[h][w]==0){
            return 0;
        }        
    }
    return 1;
}

void check_line(){                      //�O�_�s�u
    int total_line = 0;                 //�������ƲM0
    int h;
    for(h=cur_y;h<HEIGHT;h++){
        if(is_line_fill(h)==1){         //�p�G�@�溡�F�N�M��
            clear_one_line(h);          //��@��M��
            total_line++;               //��������ƼW�[
            score+=total_line*150;      //���Ƭ���ƪ�150��
            print_surface();            //�L��
            tm-=30;                     //�ɶ��C��-30
            set_timer(tm);              //���s�]�w�ɶ�
        }
    }
}

static void set_timer(int t){ 
    KillTimer(NULL, timerId);
    timerId = SetTimer(NULL,0,t,NULL);
} 

static void close_timer(){
    KillTimer(NULL,timerId);
}

void move_block_down(){
    if(isCollision(cur_x,cur_y+1)==0){
        erase_block(current_block,cur_x,cur_y);
        cur_y++;
        print_block(current_block,cur_x,cur_y);
    }
    else{
        land_block();
        check_line();
        make_new_block();
        if(isCollision(cur_x,cur_y)==1){
            erase_block(current_block,cur_x,cur_y);  //�����쥻����� 
            close_timer();                           //�Ȱ��ɶ�
            system("cls");                           //�M�ŭ��� 
            setColor(4);                             //�C�⴫����
            erase_block(current_block,cur_x,cur_y);  //�����쥻�����
            printf("\n\n\n\t�C������!!!");
            over=1;                                  //�C������-->���n�A�L�X����F 
            printf("\n\n\t�z���o���O : %d",score);    //�L�X���� 
            printf("\n\n\t�z�����ŬO : %d",level);    //�L�X���� 
            Sleep(4000);                             //�Ȱ�4�� 
        }
        print_block(current_block,cur_x,cur_y);
    }
}

void key_control(){ 
    int ch;
    while(1){
        if(PeekMessage(&msg,NULL,WM_TIMER,WM_TIMER,PM_REMOVE)!=0){
            move_block_down();
        }
        if(kbhit()!=0){
            ch = getch();
            int rem_ch;
            switch(ch){
                case 13:            //enter
                    if(isCollision(cur_x-1,cur_y)==0){
                        if(rem_ch!=13){
                            erase_block(current_block,cur_x,cur_y);    //�����쥻�����
                            rem_ch=13;                                 //�P�_�O���O���@������� 
                            print_surface();   
                            make_new_block();                          //�A�L�s����� 
                            print_block(current_block,cur_x,cur_y);
                        }
                    }
                    break;
                case 32:            //space
                    rem_ch=32;
                    if(isCollision(cur_x,cur_y+1)==0){
                    	erase_block(current_block,cur_x,cur_y);
                        while(isCollision(cur_x,cur_y+1)==0){
                            cur_y++;
                        }
                    }
                    print_block(current_block,cur_x,cur_y);  //���� 
                    break;
                case 72:            //up
                    rem_ch=72;
                    erase_block(current_block,cur_x,cur_y);
                    rotate_block();
                    if(isCollision(cur_x,cur_y)==1){         //�p�G�o�͸I���A�N�n��^�ӡC
                        rotate_block();
                        rotate_block();
                        rotate_block();
                    }
                    print_block(current_block,cur_x,cur_y);
                    break;
                case 80:           //down
                    rem_ch=80;
                    if(isCollision(cur_x,cur_y+1)==0){
                        erase_block(current_block,cur_x,cur_y);
                        cur_y++;
                        print_block(current_block,cur_x,cur_y);
                    }
                    break;
                case 75:           //left
                    rem_ch=75;
                    if(isCollision(cur_x-1,cur_y)==0){
                        erase_block(current_block,cur_x,cur_y);
                        cur_x--;
                        print_block(current_block,cur_x,cur_y);
                    }
                    break;
                case 77:           //right
                    rem_ch=77;
                    if(isCollision(cur_x+1,cur_y)==0){
                        erase_block(current_block,cur_x,cur_y);
                        cur_x++;
                        print_block(current_block,cur_x,cur_y);
                    }
                    break;
            }
        }
    }
}

void setColor(int color){        //���C��
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
