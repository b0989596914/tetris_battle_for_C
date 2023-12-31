#include<stdio.h>
#include<stdlib.h>
#include <conio.h>       
#include<time.h>
#include <windows.h>
#define HEIGHT 14
#define WIDTH 18
#define block_h 4
#define block_w 4

enum block_type{                         //總共有這7種方塊
    O,J,L,I,Z,S,T
};
 
int block_type_num = 7;                  //要跑亂數的總數
int cur_x=0,cur_y=0;  
int color_to_change_pattern;             //記住顏色 --> 改變形狀
int over=0;                              //判斷遊戲是否結束

int Block0[block_h][block_w] = {         //正方形
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockJ[block_h][block_w] = {         //J形
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockL[block_h][block_w] = {         //L形
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockI[block_h][block_w] = {         //I形
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}
};

int BlockZ[block_h][block_w] = {         //Z形
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};

int BlockS[block_h][block_w] = {         //S形
    {0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}
};

int BlockT[block_h][block_w] = {         //T型
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

void print_block(int block[][block_w],int x,int y){     //印出方塊形狀
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(block[h][w]==1 && over==0){              //如果沒結束 && =1
                if(color_to_change_pattern==2){         //如果顏色是綠色
                    printxy("+",x+w,y+h);               //印出'+'
                }
                else if(color_to_change_pattern==14){   //如果顏色是淡黃色
                    printxy("X",x+w,y+h);               //印出'X'
                }
                else if(color_to_change_pattern==8){    //如果顏色是灰色
                    printxy("#",x+w,y+h);               //印出'#'
                }
                else if(color_to_change_pattern==12){   //如果顏色是桃紅色
                    printxy("$",x+w,y+h);               //印出'$'
                }
                else if(color_to_change_pattern==6){    //如果顏色是黃色
                    printxy("&",x+w,y+h);               //印出'&'
                }
                else if(color_to_change_pattern==9){    //如果顏色是藍色
                    printxy("~",x+w,y+h);               //印出'~'
                }
                else if(color_to_change_pattern==11){   //如果顏色是藍綠色
                    printxy("@",x+w,y+h);               //印出'@'
                }
            }
        }
    }
}

void copy_block(int block_s[][block_w],int block_d[][block_w]){    //複製方塊
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            block_d[h][w] = block_s[h][w];
        }
    }
}

void make_new_block(){ 
    enum block_type type = (int)(rand()%block_type_num);   //隨機選擇一種方塊
    switch(type){                                 //將current_block變成隨機產生的方塊(產生方塊)
        case O:
            setColor(2);                          //設定顏色=2
            color_to_change_pattern=2;            //記住顏色
            copy_block(Block0,current_block);
            break;
        case J:
            setColor(14);                         //設定顏色=14
            color_to_change_pattern=14;
            copy_block(BlockJ,current_block);
            break;
        case L:
            setColor(8);                          //設定顏色=8
            color_to_change_pattern=8;
            copy_block(BlockL,current_block);
            break;
        case I:
            setColor(12);                         //設定顏色=12
            color_to_change_pattern=12;
            copy_block(BlockI,current_block);
            break;
        case Z:
            setColor(6);                          //設定顏色=6
            color_to_change_pattern=6;
            copy_block(BlockZ,current_block);
            break;
        case S:
            setColor(9);                          //設定顏色=9
            color_to_change_pattern=9;
            copy_block(BlockS,current_block);
            break;
        case T:
            setColor(11);                         //設定顏色=11
            color_to_change_pattern=11;
            copy_block(BlockT,current_block);
            break;
        default:
            break;
    }
    cur_x = (WIDTH-block_w)/2;                    //產生的位置
    cur_y = 0;
}

void rotate_block(){                              //旋轉方塊
    int temp[block_h][block_w] = {0};
    copy_block(current_block,temp);
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            current_block[h][w] = temp[block_w-1-w][h];
        }
    }
}

void land_block(){                //方塊落定到邊界
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

int get_block_y_fill(int row){         //傳入方塊的row --> 檢查是不是真的有方塊
    int is_fill =0;
    int col;
    for(col=0;col<block_w;col++){      //檢查方塊中，該row的每個col，是不是真的有方塊(1)
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

void get_block_left_right_margin(int *left_margin, int *right_margin){    //計算上下左右邊的白邊
    int i = 0;
    for(i=0;i<block_w/2;i++){             //檢查左半邊的白邊
        if(get_block_x_fill(i)==0){
            (*left_margin)+=1;
        }
    }
    for(i=block_w-1;i>=block_w/2;i--){     //檢查右半邊的白邊
        if(get_block_x_fill(i)==0){
            (*right_margin)+=1;
        }
    }
}

int isCollision(int x,int y){              //邊界判斷
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

void print_surface(){                             //列印畫面
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

void gotoxy(int x,int y){                    //更改cursor位置並列印
    COORD loc;
    loc.X = x;
    loc.Y = y;
    SetConsoleCursorPosition(hand,loc);
}

void printxy(char*str , int x, int y ){     //更改cursor位置並列印
    gotoxy(x,y);
    printf("%s",str);
}

void erase_block(int block[][block_w],int x,int y){    //列印+暫停+擦掉方塊
    int w,h;
    for(w=0;w<block_w;w++){
        for(h=0;h<block_h;h++){
            if(block[h][w]==1){
                printxy(" ",x+w,y+h); 
            }
        }
    }
}

void clear_one_line(int h){                          //清除連線
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

int is_line_fill(int h){                            //是否連線
    int w;
    for(w=0;w<WIDTH;w++){
        if(surface[h][w]==0){
            return 0;
        }        
    }
    return 1;
}

void check_line(){                      //是否連線
    int total_line = 0;                 //把消的行數清0
    int h;
    for(h=cur_y;h<HEIGHT;h++){
        if(is_line_fill(h)==1){         //如果一行滿了就清掉
            clear_one_line(h);          //把一行清掉
            total_line++;               //消掉的行數增加
            score+=total_line*150;      //分數為行數的150倍
            print_surface();            //印表面
            tm-=30;                     //時間每次-30
            set_timer(tm);              //重新設定時間
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
            erase_block(current_block,cur_x,cur_y);  //擦掉原本的方塊 
            close_timer();                           //暫停時間
            system("cls");                           //清空頁面 
            setColor(4);                             //顏色換紅色
            erase_block(current_block,cur_x,cur_y);  //擦掉原本的方塊
            printf("\n\n\n\t遊戲結束!!!");
            over=1;                                  //遊戲結束-->不要再印出方塊了 
            printf("\n\n\t您的得分是 : %d",score);    //印出分數 
            printf("\n\n\t您的等級是 : %d",level);    //印出等級 
            Sleep(4000);                             //暫停4秒 
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
                            erase_block(current_block,cur_x,cur_y);    //擦掉原本的方塊
                            rem_ch=13;                                 //判斷是不是有一直換方塊 
                            print_surface();   
                            make_new_block();                          //再印新的方塊 
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
                    print_block(current_block,cur_x,cur_y);  //瞬降 
                    break;
                case 72:            //up
                    rem_ch=72;
                    erase_block(current_block,cur_x,cur_y);
                    rotate_block();
                    if(isCollision(cur_x,cur_y)==1){         //如果發生碰撞，就要轉回來。
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

void setColor(int color){        //換顏色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
