#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define RESET   "\033[0m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

#define BOLD_BLACK   "\033[1;30m"
#define BOLD_RED     "\033[1;31m"
#define BOLD_GREEN   "\033[1;32m"
#define BOLD_YELLOW  "\033[1;33m"
#define BOLD_BLUE    "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN    "\033[1;36m"
#define BOLD_WHITE   "\033[1;37m"

#define INFx 100000
#define INFv 100

// جهت‌های حرکت
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int rand_number();
int GenerateNumber();
void hide_cursor();
void welcome();
int initialize();
void clear_screen();
void making_road();
void gotoxy(int x, int y);
void game();
void printmap();
void printdetail();
void print_after_rand_1();
void print_after_rand_2();
void game_over();

int dim_x;
int dim_y;
int v_count;
int x_c1;
int y_c1;
int x_c2;
int y_c2;
int numb_king;
int x_count;
int sodier_to_achive;
int sw[287];
int count;
int displayV = 0;


struct map_st{
    int init_value;
    int current_value;
    int current_value1;
    int current_value2;
    int owner;//0: free , 1: owner is king 1, 2: owner is king 2
    int type;// 1: king1 , 2: king2 , 3: village, 4: road, 5: block house 6: normal house

}gmap[17][17];

struct kingdom{
    int jx;
    int iy;
    double Gold;
    double Food;
    int employees;
    int Soldier;
    char name[20];
    int vkingdom;
}king[2];

struct x_house{
    int jx;
    int iy;
}block[287];

struct vil{
    int gold;
    int food;
    int jx;
    int iy;
    int solider;
    int x_dis;
    int y_dis;
}village[287];

typedef struct {
    int x, y;
} Point;

int manhattan(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool isValid(int x, int y) {
    return x >= 0 && x < dim_x && y >= 0 && y < dim_y;
}

int destroyx( Point start, Point goal,int turn_game) {
    int openList[dim_y][dim_x] ;
    int closedList[dim_y][dim_x] ;
    int path[dim_y][dim_x];
    Point parent[dim_y][dim_x];
    int dest_act=1;

    if(dest_act==1){
        for (int i = 0; i < dim_y; i++) {
            for (int j = 0; j < dim_x; j++) {
                parent[i][j] = (Point){-1, -1};
                path[i][j] = 0;
                openList[i][j]=0 ;
                closedList[i][j]=0 ;
            }
        }
        openList[start.y][start.x] = 1;
        closedList[start.y][start.x] = 1;

    while (1) {
        int currentX = -1, currentY = -1;
        for (int i = 0; i < dim_y; i++) {
            for (int j = 0; j < dim_x; j++) {
                if (openList[i][j]){
                    currentX = j;
                    currentY = i;
                }
            }
        }
        if (currentX == goal.x && currentY == goal.y) {
            Point current = goal;
            while (current.x != -1 && current.y != -1) {
                path[current.y][current.x] = 1;
                current = parent[current.y][current.x];
                if(current.x != -1 && current.y != -1){
                gmap[current.y][current.x].current_value= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].current_value1= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].current_value2= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].owner= 0;
                gmap[current.y][current.x].type= 6;
                gotoxy(2*current.y+1,4*current.x+1+70);
                getch();
                printf("%d", gmap[current.y][current.x].current_value);
                }
            }
            gotoxy(2*start.y+1,4*start.x+1+70);
            return 0;
        }
        // انتقال گره به Closed List
        if (currentX == -1 && currentY == -1){
            gmap[start.y][start.x].current_value= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].current_value1= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].current_value2= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].owner= 0;
            gmap[start.y][start.x].type= 6;
            gotoxy(2*start.y+1,4*start.x+1+70);
            getch();
            printf("%d", gmap[start.y][start.x].current_value);
            gotoxy(2*start.y+1,4*start.x+1+70);
            return 1;
        }

        openList[currentY][currentX] = 0;
        closedList[currentY][currentX] = 1;
        // بررسی همسایه‌ها
        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            if (isValid(nx, ny) && !closedList[ny][nx]) {
                if(gmap[ny][nx].current_value==0 && (gmap[ny][nx].owner==1 && turn_game==2)||(gmap[ny][nx].owner==2 && turn_game==1)){
                if (!openList[ny][nx]) {
                    openList[ny][nx] = 1;
                    parent[ny][nx] = (Point){currentX, currentY};
                        }
                    }
                }
            }
        }
    }

}

int destroy( int y1, int x1,int turn_game) {
    int openList[dim_y][dim_x] ;
    int closedList[dim_y][dim_x] ;
    int path[dim_y][dim_x];
    Point parent[dim_y][dim_x]; // for store parent
    Point start,goal;
    int dest_act=0;

    for (int i = 0; i < 4; i++) {
        int zx = x1 + dx[i];
        int zy = y1 + dy[i];

        if(turn_game==1  &&  gmap[y1][x1].current_value==0 &&  gmap[y1][x1].owner==1&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==2){
            goal.x=king[1].jx;
            goal.y=king[1].iy;
            start.x=zx;
            start.y=zy;
            dest_act=1;
        }

        if(turn_game==2  &&  gmap[y1][x1].current_value==0 &&  gmap[y1][x1].owner==2&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==1){
            goal.x=king[0].jx;
            goal.y=king[0].iy;
            start.x=zx;
            start.y=zy;
            dest_act=1;
        }

        if(turn_game==3 && gmap[y1][x1].current_value==0 &&  gmap[y1][x1].owner==1&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==2){
            goal.x=king[1].jx;
            goal.y=king[1].iy;
            start.x=zx;
            start.y=zy;
            dest_act=1;
        }
    }
    // init
    if(dest_act==1){
        for (int i = 0; i < dim_y; i++) {
            for (int j = 0; j < dim_x; j++) {
                parent[i][j] = (Point){-1, -1};
                path[i][j] = 0;
                openList[i][j]=0 ;
                closedList[i][j]=0 ;


            }
        }
        openList[start.y][start.x] = 1;
        closedList[y1][x1] = 1;

    while (1) {
        int currentX = -1, currentY = -1;
        for (int i = 0; i < dim_y; i++) {
            for (int j = 0; j < dim_x; j++) {
                if (openList[i][j]){
                    currentX = j;
                    currentY = i;
                }
            }
        }
        if (currentX == goal.x && currentY == goal.y) {
            Point current = goal;
            while (current.x != -1 && current.y != -1) {
                path[current.y][current.x] = 1;
                current = parent[current.y][current.x];
                if(current.x != -1 && current.y != -1){
                gmap[current.y][current.x].current_value= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].current_value1= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].current_value2= gmap[current.y][current.x].init_value;
                gmap[current.y][current.x].owner= 0;
                gmap[current.y][current.x].type= 6;
                gotoxy(2*current.y+1,4*current.x+1+70);
                getch();
                printf("%d", gmap[current.y][current.x].current_value);
                }
            }
            gotoxy(2*y1+1,4*x1+1+70);
            return 0;
        }
        // انتقال گره به Closed List
        if (currentX == -1 && currentY == -1){
            gmap[start.y][start.x].current_value= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].current_value1= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].current_value2= gmap[start.y][start.x].init_value;
            gmap[start.y][start.x].owner= 0;
            gmap[start.y][start.x].type= 6;
            gotoxy(2*start.y+1,4*start.x+1+70);
            getch();
            printf("%d", gmap[start.y][start.x].current_value);
            gotoxy(2*start.y+1,4*start.x+1+70);
            return 1;
        }

        openList[currentY][currentX] = 0;
        closedList[currentY][currentX] = 1;
        // بررسی همسایه‌ها
        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            if (isValid(nx, ny) && !closedList[ny][nx]) {
                if(gmap[ny][nx].current_value==0 && (gmap[ny][nx].owner==1 && turn_game==2)||(gmap[ny][nx].owner==2 && turn_game==1)){
                if (!openList[ny][nx]) {
                    openList[ny][nx] = 1;
                    parent[ny][nx] = (Point){currentX, currentY};
                        }
                    }
                }
            }
        }
    }

}

int astar( Point start, Point goal , int turn_game) {
    int openList[dim_y][dim_x] ;
    int closedList[dim_y][dim_x] ;
    int gScore[dim_y][dim_x], fScore[dim_y][dim_x];
    int path[dim_y][dim_x];

    Point parent[dim_y][dim_x];

    for (int i = 0; i < dim_y; i++) {
        for (int j = 0; j < dim_x; j++) {
            gScore[i][j] = INFx; // g(x) distance from scratch parent
            fScore[i][j] = INFx; // manhattan is the heuristic
            parent[i][j] = (Point){-1, -1};   // parrent[i][j].x,
            path[i][j] = 0;
            openList[i][j]=0 ;
            closedList[i][j]=0 ;
        }
    }
        gScore[start.y][start.x] = 0;
        fScore[start.y][start.x] = manhattan(start, goal);
        openList[start.y][start.x] = 1;

    while (1) {
        int minF = INFx, currentX = -1, currentY = -1;

        // یافتن گره با کمترین هزینه f   node
        for (int i = 0; i < dim_y; i++) {
            for (int j = 0; j < dim_x; j++) {
                if (openList[i][j] && fScore[i][j] < minF) {
                    minF = fScore[i][j];
                    currentX = j;
                    currentY = i;
                }
            }
        }
        // اگر به هدف رسیدیم
        if (currentX == goal.x && currentY == goal.y) 
        {
            // مسیر را بازسازی کن
            Point current = goal;
            while (current.x != -1 && current.y != -1) {
                path[current.y][current.x] = 1;
                current = parent[current.y][current.x];

                gotoxy(2*current.y+1,4*current.x+1+70);
                if(turn_game==1&&gmap[current.y][current.x].current_value1>0) printf(BOLD_BLUE"%d"RESET, gmap[current.y][current.x].current_value1);
                if(turn_game==1&&gmap[current.y][current.x].current_value1==0) printf(BOLD_BLUE"="RESET);

                if(turn_game==2&&gmap[current.y][current.x].current_value2>0) printf(BOLD_CYAN"%d"RESET, gmap[current.y][current.x].current_value2);
                if(turn_game==2&&gmap[current.y][current.x].current_value2==0) printf(BOLD_CYAN"="RESET);

                //}
            }

            gotoxy(44 , 100);
            int des;
            printf("gscpre= %d , ",gScore[goal.x][goal.y]);
            return gScore[goal.x][goal.y];
        }

        // انتقال گره به Closed List
        openList[currentY][currentX] = 0;
        closedList[currentY][currentX] = 1;
        // بررسی همسایه‌ها
        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            if (isValid(nx, ny) && !closedList[ny][nx]) {
                int tentativeG = gScore[currentY][currentX] + gmap[ny][nx].current_value;
                if (!openList[ny][nx]) {
                    openList[ny][nx] = 1;
                } else if (tentativeG >= gScore[ny][nx]) {
                    continue;
                }
                // به‌روزرسانی مقادیر
                gScore[ny][nx] = tentativeG;
                fScore[ny][nx] = tentativeG + manhattan((Point){nx, ny}, goal);
                parent[ny][nx] = (Point){currentX, currentY};
                }
            }
        }

}

int main() {
    int a1;
    int i, j;
    printf("You wanna start the previous game? (y/n): ");
    scanf("%c", &a1);
    clear_screen();

    if(a1 == 'n') {
        srand(time(NULL));
        welcome();
        int er = initialize();
        if(er==0) making_road();
    } else{

        int er = finitialize();
        if(er==0) making_road();

    }

    return 0;
}

void game_over(){
    system("cls");
    gotoxy(10,90);
    printf("press any key to exit");
    getch();
    system("cls");

}

int rand_number(){

    int random_num_1_to_6 = rand() % 5 + 1;

}

void printdetail(int turn_game){
    if(v_count==0){
        gotoxy(38,0);
        printf("There is no village");
    }else{
        gotoxy(38,0);
        printf("Village(%2d) X Cordinat: %d         \n",displayV+1,village[displayV].jx);
        printf("Village(%2d) Y cordinat: %d         \n",displayV+1,village[displayV].iy);
        printf("Village(%2d) Gold Range: %d         \n",displayV+1,village[displayV].gold);
        printf("Village(%2d) Food Range: %d          \n",displayV+1,village[displayV].food);
        printf("The X Distance between C and Village(%2d) is: %d  \n",displayV+1,village[displayV].x_dis);
        printf("The Y Distance between C and Village(%2d) is: %d  \n",displayV+1,village[displayV].y_dis);
        displayV++;
        if(displayV>=v_count) displayV = 0;
        Point pking1,pking2, pv;
        pking1.x=king[0].jx;
        pking1.y=king[0].iy;
        pking2.x=king[1].jx;
        pking2.y=king[1].jx;
        pv.x=village[displayV].jx;
        pv.y=village[displayV].iy;

        if(turn_game==1) astar(pking1,pv,1);
        if(turn_game==2)astar(pking2,pv,2);
    }
}

void printmap(){
    gotoxy(1,30);
    printf("%s\n", king[0].name);
    printf("----------------------------------------------------------------------");
    gotoxy(1,180);
    printf("%s", king[1].name);
    gotoxy(2,138);
    printf("---------------------------------------------------------------------");

    gotoxy(3,8);
    printf("Gold: %.2lf", king[0].Gold);
    gotoxy(3,50);
    printf("Food: %.2lf\n", king[0].Food);
    gotoxy(4,8);
    printf("Employees: %d", king[0].employees);
    gotoxy(4,50);
    printf("Soldier: %d \n\n", king[0].Soldier);
    gotoxy(6,15);
    printf("%s, please choose an action:\n\n",king[0].name);

    printf("1: Buy Food\n");
    printf("2: Hire Employees\n");
    printf("3: Hire Soldiers\n");
    printf("4: Making Road\n\n");

    printf("r: To Make Road \n");
    printf("o: To own the village\n");
    printf("v: To See Villages Details \n");
    printf("q: To exit \n\n");

    printf("You can buy up to %.2lf Food.\n", king[0].Gold);
    printf("You can hire up to %d Employees.\n",(int)(king[0].Food / 3));
    printf("You can hire up to %d Soldiers.\n",(int)(king[0].Gold / 2));

    gotoxy(3,150);
    printf("Gold: %.2lf", king[1].Gold);
    gotoxy(3,190);
    printf("Food: %.2lf\n", king[1].Food);
    gotoxy(4,150);
    printf("Employees: %d", king[1].employees);
    gotoxy(4,190);
    printf("Soldier: %d \n\n", king[1].Soldier);
    gotoxy(6,160);
    printf("%s, please choose an action:",king[1].name);
    gotoxy(8,140);
    printf("1: Buy Food\n");
    gotoxy(9,140);
    printf("2: Hire Employees");
    gotoxy(10,140);
    printf("3: Hire Soldiers");
    gotoxy(11,140);
    printf("4: Making Road");

    gotoxy(18,140);
    printf("You can buy up to %.2lf Food.\n", king[1].Gold);
    gotoxy(19,140);
    printf("You can hire up to %d Employees.\n",(int)(king[1].Food / 3));
    gotoxy(20,140);
    printf("You can hire up to %d Soldiers.\n",(int)(king[1].Gold / 2));


}

void gotoxy(int x, int y) {
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorCoord;
cursorCoord.X = y;
cursorCoord.Y = x;
SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

int initialize(){

    int i ,iy;
    int j ,jx;

    gotoxy(1,90);
    printf("X dimension: ");
    scanf("%d", &dim_x);
    if(dim_x==0) return 1;
    gotoxy(2,90);
    printf("Y dimension: ");
    scanf("%d", &dim_y);
    if(dim_y==0) return 1;

    gmap[dim_y][dim_x];


    gotoxy(3,90);
    printf("Count of kingdom: ");
    scanf("%d", &numb_king);

    if(numb_king>2 || numb_king<0) return 1;


    i = 0;
    while(i<numb_king){
        gotoxy(7*i+4,90);
        printf(GREEN"X position of C: "RESET);
        scanf("%d", &king[i].jx);

        if(king[i].jx>=dim_x) {
            system("cls");
            gotoxy(4,90);
            printf("X is too large.");
            gotoxy(5,90);
            printf("Press any key to exit");
            getch();
            system("cls");
            return 1;
        }

        gotoxy(7*i+5,90);
        printf(GREEN"Y position of C: "RESET);
        scanf("%d", &king[i].iy);
        if(king[i].iy>=dim_y) {
        system("cls");
        gotoxy(4,90);
        printf("Y is too large.");
        gotoxy(5,90);
        printf("Press any key to exit");
        getch();
        system("cls");
        return 1;
        }

        gotoxy(7*i+6,90);
        printf(GREEN"Count of workers: "RESET);
        scanf("%d", &king[i].employees);
        gotoxy(7*i+7,90);
        printf(GREEN"Range of food: "RESET);
        scanf("%lf", &king[i].Food);
        gotoxy(7*i+8,90);
        printf(GREEN"Range of gold: "RESET);
        scanf("%lf", &king[i].Gold);
        gotoxy(7*i+9,90);
        printf(GREEN"Count of solider: "RESET);
        scanf("%d", &king[i].Soldier);

        gotoxy(7 * i + 10,90);
        printf(GREEN"King name: "RESET);
        scanf("%s", king[i].name);
        king[i].vkingdom = 0;
        i++;
        }

    i--;
    int off = 7 * i + 12;
    gotoxy(7 * i + 11,90);
    printf(BOLD_RED"Count of X house: "RESET);
    scanf("%d", &x_count);
    for(i=0;i<x_count;i++){
        gotoxy(2*i + off,90);
        printf(BOLD_RED"X of block house %d: "RESET, i+1);
        scanf("%d", &block[i].jx);
        if(block[i].jx>=dim_x || block[i].jx <0) return 1;
        gotoxy(2*i+off + 1,90);
        printf(BOLD_RED"Y of block house %d: "RESET, i+1);
        scanf("%d", &block[i].iy);
        if(block[i].iy>=dim_y || block[i].iy <0) return 1;
        if(block[i].jx==king[i].jx && block[i].iy==king[i].iy) return 1;
        gmap[block[i].iy][block[i].jx].init_value = INFx;
        gmap[block[i].iy][block[i].jx].current_value = INFx;
        gmap[block[i].iy][block[i].jx].owner = 0;
        gmap[block[i].iy][block[i].jx].type = 5;
    }
    i--;
    gotoxy(2*i+off + 2,90);
    printf(BOLD_MAGENTA"Count of villages: "RESET);
    scanf("%d", &v_count);
    if(v_count<1){
        system("cls");
        printf("The count of village can not be 0");
        return 1;
    }
    int offset_v = 2 * i + off + 2;
    int villa_count = 0;
    while(villa_count<v_count){

    gotoxy(4*villa_count+offset_v+1,90);
    printf("Village(%d) X coordinate: ", villa_count+1);
    scanf("%d", &village[villa_count].jx);

    if(village[villa_count].jx>=dim_x) return 1;

    gotoxy(4*villa_count+offset_v+2,90);
    printf("Village(%d) Y coordinate: ", villa_count+1);
    scanf("%d", &village[villa_count].iy);

    if(village[villa_count].iy>=dim_y) return 1;

    gotoxy(4*villa_count+offset_v+3,90);
    printf("Village(%d) gold range: ", villa_count+1);
    scanf("%d", &village[villa_count].gold);

    gotoxy(4*villa_count+offset_v+4,90);
    printf("Village(%d) food range: ", villa_count+1);
    scanf("%d", &village[villa_count].food);

    gmap[village[villa_count].iy][village[villa_count].jx].init_value = INFv;
    gmap[village[villa_count].iy][village[villa_count].jx].current_value = INFv;
    gmap[village[villa_count].iy][village[villa_count].jx].owner = 0;
    gmap[village[villa_count].iy][village[villa_count].jx].type = 3;

    village[villa_count].x_dis = abs(king[i].jx - village[villa_count].jx);
    village[villa_count].y_dis = abs(king[i].iy - village[villa_count].iy);
    villa_count++;
    }
    villa_count--;
    gotoxy(4*villa_count+offset_v+5,90);
    printf("How many soldier you need?");
    scanf("%d", &sodier_to_achive);

    clear_screen();


    i = 0;
    j = 0;
    int v = 0;
    gotoxy(1,70);
    printf(BOLD_GREEN"Your Dimension"RESET);
    clear_screen();
    y_c1 = king[i].iy;
    x_c1 = king[i].jx;
    for(iy=0;iy<dim_y;iy++){
        for(jx=0;jx<dim_x;jx++){
            gmap[iy][jx].current_value = rand_number();
            gmap[iy][jx].current_value2 = gmap[iy][jx].current_value;
            gmap[iy][jx].current_value1 = gmap[iy][jx].current_value;
            gmap[iy][jx].init_value = gmap[iy][jx].current_value;
            for(i=0;i<x_count;i++){
                if(iy==block[i].iy && jx==block[i].jx){
                    gmap[iy][jx].current_value = INFx;
                    gmap[iy][jx].init_value = INFx;
                }
            }
            for(i=0;i<v_count;i++){
              //  for(j=0;j<2;j++){
                    if(iy==village[i].iy && jx==village[i].jx){
                    gmap[iy][jx].current_value = INFv;
                    gmap[iy][jx].init_value = INFv;
                    //gmap[iy][jx].init_value = 5;

                    }

                }
            //}
        }
    }

    gmap[king[0].iy][king[0].jx].init_value = 0;
    gmap[king[0].iy][king[0].jx].current_value = 0;
    gmap[king[0].iy][king[0].jx].owner = 1;
    gmap[king[0].iy][king[0].jx].type = 1;

    gmap[king[1].iy][king[1].jx].init_value = 0;
    gmap[king[1].iy][king[1].jx].current_value = 0;
    gmap[king[1].iy][king[1].jx].owner = 2;
    gmap[king[1].iy][king[1].jx].type = 2;

    gotoxy(35,0);
    for(i=0;i<210;i++) printf("-");
    i = 0;
    gotoxy(2*y_c1+1,4*x_c1+1+70);

    return 0;
}

int finitialize(){

    int i ,iy;
    int j ,jx;
    FILE *info;
    info = fopen("info.txt", "r");
    fscanf(info,"%d", &dim_x);
    printf("dimx=%d\n",dim_x);

    if(dim_x==0) return 1;
    fscanf(info,"%d", &dim_y);
    printf("dimy=%d",dim_y);

    if(dim_y==0) return 1;

    gmap[dim_y][dim_x];

    fscanf(info,"%d", &numb_king);

    if(numb_king>2 || numb_king<0) return 1;

    i = 0;
    while(i<numb_king){
        fscanf(info,"%d", &king[i].jx);

        if(king[i].jx>=dim_x) {
            system("cls");
            gotoxy(4,90);
            printf("X is too large.");
            gotoxy(5,90);
            printf("Press any key to exit");
            getch();
            system("cls");
            return 1;
        }

        fscanf(info,"%d", &king[i].iy);
        if(king[i].iy>=dim_y) {
        system("cls");
        gotoxy(4,90);
        printf("Y is too large.");
        gotoxy(5,90);
        printf("Press any key to exit");
        getch();
        system("cls");
        return 1;
        }

        fscanf(info,"%d", &king[i].employees);
        fscanf(info,"%lf", &king[i].Food);
        fscanf(info,"%lf", &king[i].Gold);
        fscanf(info,"%d", &king[i].Soldier);

        fscanf(info,"%s", king[i].name);
        king[i].vkingdom = 0;
        i++;
        }

    i--;
    int off = 7 * i + 12;
    fscanf(info,"%d", &x_count);
    for(i=0;i<x_count;i++){
        fscanf(info,"%d", &block[i].jx);
        if(block[i].jx>=dim_x) return 1;
        fscanf(info,"%d", &block[i].iy);
        if(block[i].iy>=dim_y) return 1;
        if(block[i].jx==king[i].jx && block[i].iy==king[i].iy) return 1;
      //  gmap[block[i].iy][block[i].jx].init_value = INFx;
      //  gmap[block[i].iy][block[i].jx].current_value = INFx;
      //  gmap[block[i].iy][block[i].jx].owner = 0;
      //  gmap[block[i].iy][block[i].jx].type = 5;
    }
    i--;
    fscanf(info,"%d", &v_count);
    if(v_count<1){
        system("cls");
        printf("The count of village can not be 0");
        return 1;
    }
    int offset_v = 2 * i + off + 2;
    int villa_count = 0;
    while(villa_count<v_count){

    fscanf(info,"%d", &village[villa_count].jx);

    if(village[villa_count].jx>=dim_x) return 1;

    fscanf(info,"%d", &village[villa_count].iy);

    if(village[villa_count].iy>=dim_y) return 1;

    fscanf(info,"%d", &village[villa_count].gold);

    fscanf(info,"%d", &village[villa_count].food);

    village[villa_count].x_dis = abs(king[i].jx - village[villa_count].jx);
    village[villa_count].y_dis = abs(king[i].iy - village[villa_count].iy);
    villa_count++;
    }
    villa_count--;
    fscanf(info,"%d", &sodier_to_achive);

    clear_screen();

    i = 0;
    j = 0;
    int v = 0;
    y_c1 = king[i].iy;
    x_c1 = king[i].jx;
    for(iy=0;iy<dim_y;iy++){
        for(jx=0;jx<dim_x;jx++){
            fscanf(info,"%d",&gmap[iy][jx].current_value);
            fscanf(info,"%d",&gmap[iy][jx].current_value2);
            fscanf(info,"%d",&gmap[iy][jx].current_value1);
            fscanf(info,"%d",&gmap[iy][jx].init_value);

        }
    }

    gmap[king[0].iy][king[0].jx].init_value = 0;
    gmap[king[0].iy][king[0].jx].current_value = 0;
    gmap[king[0].iy][king[0].jx].owner = 1;
    gmap[king[0].iy][king[0].jx].type = 1;

    gmap[king[1].iy][king[1].jx].init_value = 0;
    gmap[king[1].iy][king[1].jx].current_value = 0;
    gmap[king[1].iy][king[1].jx].owner = 2;
    gmap[king[1].iy][king[1].jx].type = 2;

    gotoxy(35,0);
    for(i=0;i<210;i++) printf("-");
    i = 0;
    gotoxy(2*y_c1+1,4*x_c1+1+70);
    fclose(info);

    return 0;
}

int fsave(){

    int i ,iy;
    int j ,jx;
    FILE *info;
    info = fopen("info.txt", "w");
    fprintf(info,"%d\n", dim_x);
    if(dim_x==0) return 1;
    fprintf(info,"%d\n", dim_y);
    if(dim_y==0) return 1;

    gmap[dim_y][dim_x];


    fprintf(info,"%d\n", numb_king);

    if(numb_king>2 || numb_king<0) return 1;

    i = 0;
    while(i<numb_king){
        fprintf(info,"%d\n", king[i].jx);

        fprintf(info,"%d\n", king[i].iy);

        fprintf(info,"%d\n", king[i].employees);
        fprintf(info,"%lf\n", king[i].Food);
        fprintf(info,"%lf\n", king[i].Gold);
        fprintf(info,"%d\n", king[i].Soldier);

        fprintf(info,"%s\n", king[i].name);
        i++;
        }

    i--;
    int off = 7 * i + 12;
    fprintf(info,"%d\n", x_count);
    for(i=0;i<x_count;i++){
        fprintf(info,"%d\n", block[i].jx);

        fprintf(info,"%d\n", block[i].iy);
      //  gmap[block[i].iy][block[i].jx].init_value = INFx;
      //  gmap[block[i].iy][block[i].jx].current_value = INFx;
      //  gmap[block[i].iy][block[i].jx].owner = 0;
      //  gmap[block[i].iy][block[i].jx].type = 5;
    }
    i--;
    fprintf(info,"%d\n", v_count);

    int offset_v = 2 * i + off + 2;
    int villa_count = 0;
    while(villa_count<v_count){

    fprintf(info,"%d\n", village[villa_count].jx);


    fprintf(info,"%d\n", village[villa_count].iy);


    fprintf(info,"%d\n", village[villa_count].gold);

    fprintf(info,"%d\n", village[villa_count].food);

    villa_count++;
    }
    villa_count--;
    fprintf(info,"%d\n", sodier_to_achive);



    i = 0;
    j = 0;
    int v = 0;
    y_c1 = king[i].iy;
    x_c1 = king[i].jx;
    for(iy=0;iy<dim_y;iy++){
        for(jx=0;jx<dim_x;jx++){
            fprintf(info,"%d\n",gmap[iy][jx].current_value);
            fprintf(info,"%d\n",gmap[iy][jx].current_value2);
            fprintf(info,"%d\n",gmap[iy][jx].current_value1);
            fprintf(info,"%d\n",gmap[iy][jx].init_value);

        }
    }


    fclose(info);

    return 0;
}

void making_road(){

    clock_t start, end;
    double round_time;
    double round_max_time = 30;

    int iy;
    int jx;

    int y;
    int x;
    int i,j;

    int check = 1;
    sw[v_count];
    int tx1;
    int ty1;
    int tx2;
    int ty2;

    for(iy = 0; iy<v_count; iy++){
        sw[iy] = 1;
    }

    x_c1 = king[0].jx;
    y_c1 = king[0].iy;
    x_c2 = king[1].jx;
    y_c2 = king[1].iy;
    gotoxy(2*y_c1 + 1,4*x_c1 + 1 + 70);
    int currentx1=x_c1;
    int currenty1=y_c1;

    tx1 = x_c1;
    ty1 = y_c1;

    tx2 = x_c2;
    ty2 = y_c2;

    int allow_up = 0;
    int allow_dn = 0;
    int allow_r = 0;
    int allow_l = 0;

    int chep = 0;
    int turn = 1;

    for(iy = 0; iy < dim_y; iy++){
        for(jx = 0; jx < dim_x; jx++){
            gotoxy(2*iy+1,4*jx+1+70);
            if(gmap[iy][jx].current_value!=INFx && gmap[iy][jx].current_value!=INFv){
                gmap[iy][jx].type = 6;
                gmap[iy][jx].owner = 0;
                printf("%d", gmap[iy][jx].current_value);
            }
        }
    }

    gotoxy(2*y_c1+1,4*x_c1+1+70);
    printf(BOLD_GREEN"C1"RESET);
    gotoxy(2*y_c2+1,4*x_c2+1+70);
    printf(BOLD_RED"C2"RESET);

    for(i=0;i<x_count;i++){
        iy = block[i].iy;
        jx = block[i].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        printf(RED"X"RESET);
    }
    for(i=0;i<v_count;i++){
        iy = village[i].iy;
        jx = village[i].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        printf(MAGENTA"V"RESET);
        }

    int cond_game_over = 1;

    gmap[king[0].iy][king[0].jx].init_value = 0;
    gmap[king[0].iy][king[0].jx].current_value = 0;
    gmap[king[0].iy][king[0].jx].current_value1 = 0;
    gmap[king[0].iy][king[0].jx].current_value2 = 0;
    gmap[king[0].iy][king[0].jx].owner = 1;
    gmap[king[0].iy][king[0].jx].type = 1;

    gmap[king[1].iy][king[1].jx].init_value = 0;
    gmap[king[1].iy][king[1].jx].current_value = 0;
    gmap[king[1].iy][king[1].jx].current_value1 = 0;
    gmap[king[1].iy][king[1].jx].current_value2 = 0;
    gmap[king[1].iy][king[1].jx].owner = 2;
    gmap[king[1].iy][king[1].jx].type = 2;

    start = clock();


    while(cond_game_over){


    //end= clock();

    //round_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printmap();
    gotoxy(36 , 90);
    printf("Current X: %d  Current Y: %d   \n",currentx1,currenty1);

    gotoxy(38 , 94);
    if(turn==1) printf(BOLD_GREEN"player 1: %s  "RESET,king[0].name);
    if(turn==2) printf(BOLD_RED"player 2: %s  "RESET,king[1].name);
    printf("Elapsed time: %.2f seconds", round_time);
    gotoxy(40 , 94);
    printf("current value: %d", gmap[currenty1][currentx1].current_value);
    gotoxy(41 , 94);
    printf(" current value1: %d", gmap[currenty1][currentx1].current_value1);
    gotoxy(42 , 94);
    printf(" current value2: %d", gmap[currenty1][currentx1].current_value2);
    gotoxy(43 , 94);
    printf("owner : %d", gmap[currenty1][currentx1].owner);
    Point stx,gox;
     for (int i = 0; i < 4; i++) {
        int zx = currentx1 + dx[i];
        int zy = currenty1 + dy[i];

      if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==1&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==2){
              if(king[0].Soldier>king[1].Soldier){
                    gox.x=king[1].jx;
                    gox.y=king[1].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,1);
              }
        }

      if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==2&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==1){
              if(king[0].Soldier<king[1].Soldier){
                    gox.x=king[0].jx;
                    gox.y=king[0].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,2);
              }
        }

      if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==2&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==1){
              if(king[0].Soldier==king[1].Soldier){
                    gox.x=king[1].jx;
                    gox.y=king[1].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,1);

                    gox.x=king[0].jx;
                    gox.y=king[0].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,2);
              }
        }

      if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==1&&  gmap[zy][zx].current_value==0 && gmap[zy][zx].owner==2){
              if(king[0].Soldier==king[1].Soldier){
                    gox.x=king[1].jx;
                    gox.y=king[1].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,1);

                    gox.x=king[0].jx;
                    gox.y=king[0].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,2);
              }
        }

      if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==1&&  zy==king[1].iy && zx==king[1].jx){
              if(king[0].Soldier<king[1].Soldier){
                    gox.x=king[0].jx;
                    gox.y=king[0].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,2);
              }
              else {
                system("cls");
                gotoxy(10,90);
                printf("%s win",king[0].name);
                getch();
                system("cls");
                cond_game_over = 0;
              }
        }

          if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==2&&  zy==king[0].iy && zx==king[0].jx){
              if(king[0].Soldier>king[1].Soldier){
                    gox.x=king[1].jx;
                    gox.y=king[1].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,1);
              }
              else {
                system("cls");
                gotoxy(10,90);
                printf("%s win",king[1].name);
                getch();
                system("cls");
                cond_game_over = 0;
              }
        }

        if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==2&&  gmap[zy][zx].type==3 && gmap[zy][zx].owner==1){
              if(king[0].Soldier<king[1].Soldier){
                    gox.x=king[0].jx;
                    gox.y=king[0].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,2);
              }
        }

        if(gmap[currenty1][currentx1].current_value==0 &&  gmap[currenty1][currentx1].owner==1&&  gmap[zy][zx].type==3 && gmap[zy][zx].owner==2){
              if(king[0].Soldier<king[1].Soldier){
                    gox.x=king[1].jx;
                    gox.y=king[1].iy;
                    stx.x=zx;
                    stx.y=zy;
                    destroyx(stx,gox,1);
              }
        }

     }


    gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
    int a1;
    a1 = getch();

    if(currenty1!=0){
    if((gmap[currenty1][currentx1].current_value==0 || gmap[currenty1-1][currentx1].current_value==0)&&(gmap[currenty1-1][currentx1].owner==turn || gmap[currenty1-1][currentx1].owner==0)) allow_up = 1;
    else allow_up = 0;
    }

    if(currenty1!=dim_y-1){
    if((gmap[currenty1][currentx1].current_value==0 || gmap[currenty1+1][currentx1].current_value==0)&&(gmap[currenty1+1][currentx1].owner==turn|| gmap[currenty1+1][currentx1].owner==0)) allow_dn = 1;
    else allow_dn = 0;
    }

    if(currentx1!=dim_x-1){
    if((gmap[currenty1][currentx1].current_value==0 || gmap[currenty1][currentx1+1].current_value==0)&&(gmap[currenty1][currentx1+1].owner==turn || gmap[currenty1][currentx1+1].owner==0)) allow_r = 1;
    else allow_r = 0;
    }

    if(currentx1!=0){
    if((gmap[currenty1][currentx1].current_value==0 || gmap[currenty1][currentx1-1].current_value==0)&&(gmap[currenty1][currentx1-1].owner==turn||gmap[currenty1][currentx1-1].owner==0)) allow_l = 1;
    else allow_l = 0;
    }

    if(a1==224){
        int a2=getch();
        if(a2==72 && currenty1>0 && allow_up==1){
            currenty1--;
            allow_up = 0;
            allow_r = 0;
            allow_l = 0;
            }
        if(a2==80 && currenty1<dim_y-1 && allow_dn==1){
            currenty1++;
            allow_dn = 0;
            allow_r = 0;
            allow_l = 0;
            }
        if(a2==77&&currentx1<dim_x-1&&allow_r==1){
            currentx1++;
            allow_r = 0;
            allow_dn = 0;
            allow_up = 0;
            }
        if(a2==75&&currentx1>0&&allow_l==1){
            currentx1--;
            allow_l = 0;
            allow_up = 0;
            allow_dn = 0;
            }
        }

    if(a1==114 && turn==1){


        if(gmap[currenty1][currentx1].current_value1!=0 && gmap[currenty1][currentx1].current_value1!=INFx){
        if(gmap[currenty1][currentx1].current_value1<=king[0].employees) gmap[currenty1][currentx1].current_value1 = 0;
        else gmap[currenty1][currentx1].current_value1-=king[0].employees;

        gotoxy(2*currenty1+1,4*currentx1+1+70);


        if(gmap[currenty1][currentx1].current_value1==0){
            gmap[currenty1][currentx1].current_value = 0;
            gmap[currenty1][currentx1].current_value2 = 0;
            gmap[currenty1][currentx1].type = 4;
            printf(BOLD_GREEN"="RESET);
            gmap[currenty1][currentx1].owner = 1;
        }else printf("%d", gmap[currenty1][currentx1].current_value2);

        gotoxy(2*currenty1+1,4*currentx1+1+70);
        start = clock();
        tx1 = currentx1;
        ty1 = currenty1;
        currentx1 = tx2;
        currenty1 = ty2;
        //gmap[currenty1][currentx1].current_value=gmap[currenty1][currentx1].current_value2;
        king[0].Gold++;
        king[0].Food++;
        turn = 2;
        a1 = 0;
        }
    }

    if(a1==114 && turn==2){
        if(gmap[currenty1][currentx1].current_value2!=0 && gmap[currenty1][currentx1].current_value2!=INFx){
        if(gmap[currenty1][currentx1].current_value2<=king[1].employees) gmap[currenty1][currentx1].current_value2 = 0;
        else {gmap[currenty1][currentx1].current_value2-=king[1].employees; }

        if(gmap[currenty1][currentx1].current_value2==0){
            gmap[currenty1][currentx1].current_value = 0;
            gmap[currenty1][currentx1].current_value1 = 0;
            gmap[currenty1][currentx1].type = 4;
            printf(BOLD_RED"="RESET);
            gmap[currenty1][currentx1].owner = 2;
        }
        else printf("%d", gmap[currenty1][currentx1].current_value1);

        tx2 = currentx1;
        ty2 = currenty1;
        currentx1 = tx1;
        currenty1 = ty1;
        //gmap[currenty1][currentx1].current_value=gmap[currenty1][currentx1].current_value1;

        gotoxy(2*currenty1+1,4*currentx1+1+70);
        start = clock();
        king[1].Gold++;
        king[1].Food++;
        turn = 1;
        a1 = 0;
        }
    }

    if(a1==49 && turn==1){
        if (king[0].Gold >= 1) {
            gotoxy(8,20);
            printf("How much would you like to buy? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(8,20);
            printf("                                  ");
            if (amount <= king[0].Gold) {
                king[0].Gold -= amount;
                king[0].Food += amount;

            }
        }
        king[1].Gold++;

        tx1 = currentx1;
        ty1 = currenty1;

        currentx1 = tx2;
        currenty1 = ty2;

        gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
        turn = 2;
        start = clock();
        a1 = 0;

    }

    if(a1==49 && turn==2){
        if (king[1].Gold >= 1) {
            gotoxy(8,160);
            printf("How much would you like to buy? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(8,160);
            printf("                                  ");
            if (amount <= king[1].Gold) {
                king[1].Gold -= amount;
                king[1].Food += amount;

            }
        }
        king[1].Gold++;

        tx2 = currentx1;
        ty2 = currenty1;

        currentx1 = tx1;
        currenty1 = ty1;
        gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
        turn = 1;
        start = clock();
        a1 = 0;
    }

    if(a1==50 && turn==1){ // hire employees
        if (king[0].Food >= 3) {
            gotoxy(9,20);
            printf("How much would you like to hire? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(9,20);
            printf("                                  ");
            if (amount * 3 <= king[0].Food) {
                king[0].employees += amount;
                king[0].Food -= amount * 3;
            }
        }
        king[0].Gold++;

        tx1 = currentx1;
        ty1 = currenty1;

        currentx1 = tx2;
        currenty1 = ty2;

        if(king[0].Soldier + king[1].Soldier == sodier_to_achive && count==v_count){
            if(king[0].Soldier>king[1].Soldier){
                system("cls");
                gotoxy(10,90);
                printf("%s win",king[0].name);
                getch();
                system("cls");
                return 1;
            }else printf("%s win",king[1].name);;
        }

        gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
        turn = 2;
        start = clock();
        a1 = 0;
    }

    if(a1==50 && turn==2){ // hire employees
        if (king[1].Food >= 3) {
            gotoxy(9,160);
            printf("How much would you like to hire? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(9,160);
            printf("                                  ");
            if (amount * 3 <= king[1].Food) {
                king[1].employees += amount;
                king[1].Food -= amount * 3;
            }
        }

        king[1].Gold++;

        tx2 = currentx1;
        ty2 = currenty1;

        currentx1 = tx1;
        currenty1 = ty1;
        gotoxy(2*y_c1 + 1,4*x_c1 + 1 + 70);
        turn = 1;
        start = clock();

        a1 = 0;
    }

    if(a1==51 && turn==1){ // hire soldier
        if (king[0].Gold >= 2) {
            gotoxy(10,20);
            printf("How much would you like to buy? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(10,20);
            printf("                                             ");
            if (amount * 2 <= king[0].Gold) {
                king[0].Soldier += amount;
                king[0].Gold -= amount * 2;
                }
            }

        if(king[0].Soldier + king[1].Soldier == sodier_to_achive && count==v_count){
            if(king[0].Soldier>king[1].Soldier){
                system("cls");
                gotoxy(10,90);
                printf("%s win",king[0].name);
                getch();
                system("cls");
                return 1;
            }else printf("%s win",king[1].name);;
        }

        king[0].Gold++;
        tx1 = currentx1;
        ty1 = currenty1;

        currentx1 = tx2;
        currenty1 = ty2;
        gotoxy(2*y_c2 + 1,4*x_c2 + 1 + 70);
        turn = 2;
        start = clock();

        a1 = 0;
    }

    if(a1==51 && turn==2){ // hire soldier
        if (king[1].Gold >= 2) {
            gotoxy(10,160);
            printf("How much would you like to buy? ");
            int amount;
            scanf("%d", &amount);
            gotoxy(10,160);
            printf("                                             ");
                if (amount * 2 <= king[1].Gold){
                    king[1].Soldier += amount;
                    king[1].Gold -= amount * 2;
            }
        }

        if(king[0].Soldier + king[1].Soldier == sodier_to_achive && count==v_count){
            if(king[0].Soldier>king[1].Soldier){
                system("cls");
                gotoxy(10,90);
                printf("%s win",king[0].name);
                getch();
                system("cls");
                cond_game_over = 0;
            }else printf("%s win",king[1].name);;
        }

        tx2 = currentx1;
        ty2 = currenty1;

        currentx1 = tx1;
        currenty1 = ty1;

        king[1].Gold++;
        gotoxy(2*y_c2 + 1,4*x_c2 + 1 + 70);
        turn = 1;
        start = clock();

        a1 = 0;
    }

    if(a1==111 && turn==1){ 
        for(iy = 0; iy<v_count; iy++){ // owing the village
            if(currentx1==village[iy].jx && currenty1==village[iy].iy && sw[iy]==1){
                king[0].Gold+=village[iy].gold;
                king[0].Food+=village[iy].food;
                y = village[iy].iy;
                x = village[iy].jx;
                count++;
                king[0].vkingdom++;
                gmap[y][x].current_value=0;
                gmap[y][x].owner=1;

                if(count==v_count){
                    system("cls");
                    gotoxy(10,90);
                    if(king[0].Soldier>king[1].Soldier++) printf("%s win",king[0].name);
                    if(king[0].Soldier<king[1].Soldier++) printf("%s win",king[1].name);
                    gotoxy(11,90);
                    printf("press any key to exit");
                    getch();
                    system("cls");
                    cond_game_over = 0;
                }
                gotoxy(2*currenty1+1,4*currentx1+1+70);
                printf(GREEN"V"RESET);
                sw[iy] = 0;

            }
        }

        tx1 = currentx1;
        ty1 = currenty1;

        currentx1 = tx2;
        currenty1 = ty2;

        gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
        turn = 2;
        start = clock();

        a1 = 0;
    }

    if(a1==111&&turn==2){
        for(iy = 0; iy<v_count; iy++){
            if(currentx1==village[iy].jx && currenty1==village[iy].iy && sw[iy]==1){
                king[1].Gold+=village[iy].gold;
                king[1].Food+=village[iy].food;
                y = village[iy].iy;
                x = village[iy].jx;
                count++;
                king[1].vkingdom++;
                gmap[y][x].current_value=0;
                gmap[y][x].owner=2;
                    if(count==v_count){
                        system("cls");
                        gotoxy(10,90);
                        if(king[0].Soldier>king[1].Soldier++) printf("%s win",king[0].name);
                        if(king[0].Soldier<king[1].Soldier++) printf("%s win",king[1].name);
                        gotoxy(11,90);
                        printf("press any key to exit");
                        getch();
                        system("cls");
                        cond_game_over = 0;
                    }
                    gotoxy(2*y+1,4*x+1+70);
                    printf(RED"V"RESET);

                    sw[iy] = 0;
                }
                turn = 1;
                start = clock();

            }
            tx2 = currentx1;
            ty2 = currenty1;

            currentx1 = tx1;
            currenty1 = ty1;

            gotoxy(2*currenty1 + 1,4*currentx1 + 1 + 70);
            a1 = 0;
        }


    if(a1==118) printdetail(turn);
    if(a1==113){
        game_over(); cond_game_over = 0;
        fsave();
    }


        iy = king[0].iy;
        jx = king[0].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        printf(BOLD_GREEN"C1"RESET);
        iy = king[1].iy;
        jx = king[1].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        printf(BOLD_RED"C2"RESET);

    for(i=0;i<x_count;i++){
        iy = block[i].iy;
        jx = block[i].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        printf(RED"X"RESET);
    }

    for(i=0;i<v_count;i++){
        iy = village[i].iy;
        jx = village[i].jx;
        gotoxy(2*iy+1,4*jx+1+70);
        if(gmap[iy][jx].owner==1) printf(BOLD_GREEN"V  "RESET);
        if(gmap[iy][jx].owner==2) printf(BOLD_RED"V  "RESET);
        if(gmap[iy][jx].owner==0) printf(BOLD_MAGENTA"V  "RESET);
        }



    }
}

void clear_screen(){
    system("cls");
}

void hide_cursor(){
    CONSOLE_CURSOR_INFO CURSORINFO;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURSORINFO);
    CURSORINFO.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURSORINFO);
}

void welcome(){

    clear_screen();

    gotoxy(1,50);
    printf(GREEN"*             *  *****  *       ****  ***        *   *      *****\n"RESET);
    gotoxy(2,50);
    printf(GREEN" *           *   *      *      *     *   *      * * * *     *    \n"RESET);
    gotoxy(3,50);
    printf(GREEN"  *    *    *    ****   *      *     *   *     *   *   *    **** \n"RESET);
    gotoxy(4,50);
    printf(GREEN"   *  *  * *     *      *      *     *   *    *         *   *    \n"RESET);
    gotoxy(5,50);
    printf(GREEN"    *     *      *****  *****   ****  ***    *           *  *****\n"RESET);

    getch();
    clear_screen();

    gotoxy(1,90);
    printf("RAHE RASTEGARI");

    gotoxy(2, 80);
    printf("Created by :Saeed Fahimi and Enayat Balaghi\n");

    gotoxy(3, 80);
    printf("Professor Abrishami\n");

    gotoxy(5,80);
    printf("please enter to countinue");
    getch();
    clear_screen();
}

