#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

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

int rand_number();
int GenerateNumber();
void hide_cursor();
void welcome();
int initialize();
void clear_screen();
void making_road();
void gotoxy(int x, int y);
void game();

int dim_x;
int dim_y;
int v_count;
int x_c1;
int y_c1;
int x_c2;
int y_c2;
char kingdom[2][2];
int numb_king = 1;
int map[17][17];
int detail[17][6];
int x_houses[287][2];
int cost[287];
int farmanrava[1][3];
int x_count;




struct kingdom{
    int jx;
    int iy;
    double Gold;
    double Food;
    int employees;
    int Soldier;
    char name[20];
}king;

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

struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
};

int main(){

    srand(time(NULL));
    //hide_cursor();
    welcome();
    int er = initialize();
    if(er==0) making_road();
    return 0;
}

int rand_number(){

    int random_num_1_to_6 = rand() % 5 + 1;

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


    gotoxy(3,90);
    printf("Count of kingdom: ");
    scanf("%d", &numb_king);

    if(numb_king>2 || numb_king<0) return 1;


    i = 0;
    while(i<numb_king){
        gotoxy(3*i+4,90);
        printf(GREEN"X position of C: "RESET);
        scanf("%d", &king.jx);
        if(king.jx>=dim_x)  {
        system("cls");
        gotoxy(4,90);
        printf("X is too large.");
        gotoxy(5,90);
        printf("Press any key to exit");
        getch();
        system("cls");
        return 1;
        }
        gotoxy(3*i+5,90);
        printf(GREEN"Y position of C: "RESET);
        scanf("%d", &king.iy);
        if(king.iy>=dim_y) {
        system("cls");
        gotoxy(4,90);
        printf("Y is too large.");
        gotoxy(5,90);
        printf("Press any key to exit");
        getch();
        system("cls");
        return 1;
        }
        gotoxy(5*i+6,90);
        printf(GREEN"Count of workers: "RESET);
        scanf("%d", &king.employees);
        gotoxy(5*i+7,90);
        printf(GREEN"Range of food: "RESET);
        scanf("%lf", &king.Food);
        gotoxy(5*i+8,90);
        printf(GREEN"Range of gold: "RESET);
        scanf("%lf", &king.Gold);
        gotoxy(5*i+9,90);
        printf(GREEN"Count of solider: "RESET);
        scanf("%d", &king.Soldier);
        gotoxy(5 * i + 10,90);
        printf(GREEN"King name: "RESET);
        scanf("%s", king.name);
        //gets(king.name);
        i++;
        }
        i--;
    gotoxy(5 * i + 11,90);
    printf(BOLD_RED"Count of X house: "RESET);
    scanf("%d", &x_count);
    for(i=0;i<x_count;i++){
        gotoxy(2*i+12,90);
        printf(BOLD_RED"X of block house %d: "RESET, i+1);
        scanf("%d", &block[i].jx);
        if(block[i].jx>=dim_x) return 1;
        gotoxy(2*i+13,90);
        printf(BOLD_RED"Y of block house %d: "RESET, i+1);
        scanf("%d", &block[i].iy);
        if(block[i].iy>=dim_y) return 1;
        if(block[i].jx==king.jx && block[i].iy==king.iy) return 1;
    }
    i--;
    gotoxy(2*i+14,90);
    printf(BOLD_MAGENTA"Count of villages: "RESET);
    scanf("%d", &v_count);
    if(v_count<1){
        system("cls");
        printf("The count of village can not be 0");
        return 1;
    }
    int offset_v = 2 * i + 14;
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

    village[villa_count].x_dis = abs(king.jx - village[villa_count].jx);
    village[villa_count].y_dis = abs(king.iy - village[villa_count].iy);
    villa_count++;
    }

    clear_screen();


    i = 0;
    j = 0;
    int v = 0;
    gotoxy(1,70);
    printf(BOLD_GREEN"Your Dimension"RESET);
    clear_screen();
    y_c1 = king.iy;
    x_c1 = king.jx;
    for(iy=0;iy<dim_y;iy++){
        for(jx=0;jx<dim_x;jx++){
            map[iy][jx] = rand_number();
            if(iy==y_c1 && jx==x_c1) map[iy][jx] = 0;
            for(i=0;i<x_count;i++){
                for(j=0;j<x_count;j++){
                    if(iy==block[i].iy && jx==block[i].jx) map[iy][jx] = 9;
                }
            }

            for(i=0;i<v_count;i++){
                for(j=0;j<2;j++){
                    if(iy==village[i].iy && jx==village[i].jx) map[iy][jx] = 0;
                }
            }
        }
    }
    for(iy=0;iy<dim_y;iy++){
        for(jx=0;jx<dim_x;jx++){
            gotoxy(2*iy+1,4*jx+1+70);
            if(jx==king.jx && iy==king.iy) printf(BOLD_GREEN"C%d"RESET,1);
            else printf(BOLD_WHITE"%d"RESET, map[iy][jx]);
            }
        }

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

    gotoxy(35,0);
    for(i=0;i<210;i++) printf("-");
    i = 0;
    gotoxy(2*y_c1+1,4*x_c1+1+70);

    return 0;
}

void making_road(){

    int gold = king.Gold;
    int food = king.Food;
    int employees = king.employees;
    int soldier = king.Soldier;
    int iy;
    int jx;

    int y;
    int x;

    int check = 1;

    int sw[v_count];

    for(iy = 0; iy<v_count; iy++){
        sw[iy] = 1;
    }

    x_c1 = king.jx;
    y_c1 = king.iy;
    gotoxy(2*y_c1 + 1,4*x_c1 + 1 + 70);
    int currentx=x_c1;
    int currenty=y_c1;
    int allow_up = 0;
    int allow_dn = 0;
    int allow_r = 0;
    int allow_l = 0;
    int displayV = 0;
    int chep = 0;
    int count = 0;

    gotoxy(1,30);
    printf("%s\n", king.name);
    printf("---------------------------------------------------------------------");

    while (1) {

    check = 1;

    gotoxy(3,8);
    printf("Gold: %.2lf", king.Gold);
    gotoxy(3,50);
    printf("Food: %.2lf\n", king.Food);
    gotoxy(4,8);
    printf("Employees: %d", king.employees);
    gotoxy(4,50);
    printf("Soldier: %d \n\n", king.Soldier);
    gotoxy(6,15);
    printf("%s, please choose an action:\n\n",king.name);

    printf("1: Buy Food\n");
    printf("2: Hire Employees\n");
    printf("3: Hire Soldiers\n");
    printf("4: Making Road\n\n");

    printf("r: To Make Road \n");
    printf("o: To own the village\n");
    printf("v: To See Villages Details \n");
    printf("q: To exit \n\n");


    printf("You can buy up to %.2lf Food.\n", king.Gold);
    printf("You can hire up to %d Employees.\n",(int)(king.Food / 3));
    printf("You can hire up to %d Soldiers.\n",(int)(king.Gold / 2));


    if(currenty!=0){
    if(map[currenty][currentx]==0 || map[currenty-1][currentx]==0) allow_up = 1;
    else allow_up = 0;
    }

    if(currenty!=dim_y-1){
    if(map[currenty][currentx]==0 || map[currenty+1][currentx]==0) allow_dn = 1;
    else allow_dn = 0;
    }

    if(currentx!=dim_x-1){
    if(map[currenty][currentx]==0 || map[currenty][currentx+1]==0) allow_r = 1;
    else allow_r = 0;
    }

    if(currentx!=0){
    if(map[currenty][currentx]==0 || map[currenty][currentx-1]==0) allow_l = 1;
    else allow_l = 0;
    }
    gotoxy(36 , 71);
    printf("Current X: %d  Current Y: %d   ",currentx,currenty);
    gotoxy(2*currenty + 1,4*currentx + 1 + 70);
    int a1 = getch();
    int r;
    if(a1==113) {
        system("cls");
        gotoxy(10,90);
        printf("press any key to exit");
        getch();
        system("cls");
        return 1;
    }
        if(a1==224){
            int a2=getch();
            if(a2==72 && currenty>0 && allow_up==1){
                currenty--;
                allow_up = 0;
                allow_r = 0;
                allow_l = 0;
                }
            if(a2==80 && currenty<dim_y-1 && allow_dn==1){
                currenty++;
                allow_dn = 0;
                allow_r = 0;
                allow_l = 0;
                }
            if(a2==77&&currentx<dim_x-1&&allow_r==1){
                currentx++;
                allow_r = 0;
                allow_dn = 0;
                allow_up = 0;
                }
            if(a2==75&&currentx>0&&allow_l==1){
                currentx--;
                allow_l = 0;
                allow_up = 0;
                allow_dn = 0;
                }
            }
            if(a1==114){
                if(map[currenty][currentx]!=7&&map[currenty][currentx]!=0&&map[currenty][currentx]!=9){

                    if(map[currenty][currentx]<king.employees){
                        map[currenty][currentx] = 0;
                        printf(BOLD_CYAN"="RESET);
                    } else {
                        map[currenty][currentx] = map[currenty][currentx] - king.employees;
                        if(map[currenty][currentx]==0) printf(BOLD_CYAN"="RESET);
                        else printf("%d",map[currenty][currentx]);
                    }
            gotoxy(2*currenty + 1,4*currentx + 1 + 70);
                }

                king.Gold++;
                king.Food++;
            }

            if(a1==49){ // buy food
                if (king.Gold >= 1) {
                    gotoxy(8,20);
                    printf("How much would you like to buy? ");
                    int amount;
                    scanf("%d", &amount);
                    gotoxy(8,20);
                    printf("                                  ");
                    if (amount <= king.Gold) {
                        king.Gold -= amount;
                        king.Food += amount;

                    }
                }
                king.Gold++;
            }

            if(a1==50){ // hire employees
                if (king.Food >= 3) {
                    gotoxy(9,20);
                    printf("How much would you like to hire? ");
                    int amount;
                    scanf("%d", &amount);
                    gotoxy(9,20);
                    printf("                                  ");
                    if (amount * 3 <= king.Food) {
                        king.employees += amount;
                        king.Food -= amount * 3;

                    }
                }
                king.Gold++;
            }

            if(a1==51){ // hire soldier
                if (king.Gold >= 2) {
                    gotoxy(10,20);
                    printf("How much would you like to buy? ");
                    int amount;
                    scanf("%d", &amount);
                    gotoxy(10,20);
                    printf("                                             ");
                    if (amount * 2 <= king.Gold) {
                        king.Soldier += amount;
                        king.Gold -= amount * 2;

                    }
                }
                king.Gold++;

            }
            if(a1==111){
                for(iy = 0; iy<v_count; iy++){
                    if(currentx==village[iy].jx && currenty==village[iy].iy && sw[iy]==1){
                        king.Gold+=village[iy].gold;
                        king.Food+=village[iy].food;
                        y = village[iy].iy;
                        x = village[iy].jx;
                        count++;
                        if(count==v_count){
                            system("cls");
                            gotoxy(10,90);
                            printf("The game is over");
                            gotoxy(11,90);
                            printf("press any key to exit");
                            getch();
                            system("cls");
                            return 1;
                        }
                        gotoxy(2*y+1,4*x+1+70);
                        printf(GREEN"V"RESET);
                        sw[iy] = 0;
                    }
                }
            }

            if(a1==118){
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
                }
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



void game() {

    struct player players[1];
    printf("Please enter Gold, Food, Employees, and Soldiers\n");
    scanf("%lf %lf %d %d", &players[0].Gold, &players[0].Food, &players[0].employees, &players[0].Soldier);
    int gold = players[0].Gold;
    int food = players[0].Food;
    int employees = players[0].employees;
    int soldier = players[0].Soldier;

    while (1) {
        // Player 1's turn
        int SW = 1, check = 0;
        while (SW) {
            if (check > 0)
                printf("Invalid choice or insufficient resources. Try again.\n");


            int choice;
            scanf("%d", &choice);

            if (choice == 1) { // Buy Food
                if (players[0].Gold >= 1) {
                    printf("You have %.2lf Gold and can buy up to %.2lf Food. How much would you like to buy? ", players[0].Gold, players[0].Gold);
                    int amount;
                    scanf("%d", &amount);
                    if (amount <= players[0].Gold) {
                        players[0].Gold -= amount;
                        players[0].Food += amount;
                        SW = 0;
                    }
                }
            } else if (choice == 2) { // Hire Employees
                if (players[0].Food >= 3) {
                    printf("You have %.2lf Food and can hire up to %d Employees. How many would you like to hire? ", players[0].Food, (int)(players[0].Food / 3));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 3 <= players[0].Food) {
                        players[0].employees += amount;
                        players[0].Food -= amount * 3;
                        SW = 0;
                    }
                }
            } else if (choice == 3) { // Hire Soldiers
                if (players[0].Gold >= 2) {
                    printf("You have %.2lf Gold and can hire up to %d Soldiers. How many would you like to hire? ", players[0].Gold, (int)(players[0].Gold / 2));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 2 <= players[0].Gold) {
                        players[0].Soldier += amount;
                        players[0].Gold -= amount * 2;
                        SW = 0;
                    }
                }
            }

              else if(choice==4){

                }
            check++;


        }


        printf("\n\nPlayer 1 Properties:\n");
        printf("Gold: %.2lf, Food: %.2lf, Employees: %d, Soldiers: %d\n", players[0].Gold, players[0].Food, players[0].employees, players[0].Soldier);

        players[0].Food += food;
        players[0].Gold += gold;

    }
    return 0;
}



/*
int SW = 1, check = 0;
        while (SW) {
            //if (check > 0) printf("Invalid choice or insufficient resources. Try again.\n");
            gotoxy(5,0);
            printf("Player 1, please choose an action:\n");
            gotoxy(7,0);
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n4. Making road");

            char choice = getch();

            if (choice == '1') {
                if (king.Gold >= 1) {
                    gotoxy(10,0);
                    printf("You have %.2lf Gold and can buy up to %.2lf Food. How much would you like to buy? ", king.Gold, king.Gold);
                    int amount;
                    scanf("%d", &amount);
                    if (amount <= king.Gold) {
                        king.Gold -= amount;
                        king.Food += amount;
                        SW = 0;
                    }
                }
            } else if (choice == '2') {
                if (king.Food >= 3) {
                    gotoxy(10,0);
                    printf("You have %.2lf Food and can hire up to %d Employees. How many would you like to hire? ", king.Food, (int)(king.Food / 3));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 3 <= king.Food) {
                        king.employees += amount;
                        king.Food -= amount * 3;
                        SW = 0;
                    }
                }
            } else if (choice == '3') { // Hire Soldiers
                if (king.Gold >= 2) {
                    gotoxy(10,0);
                    printf("You have %.2lf Gold and can hire up to %d Soldiers. How many would you like to hire? ", king.Gold, (int)(king.Gold / 2));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 2 <= king.Gold) {
                        king.Soldier += amount;
                        king.Gold -= amount * 2;
                        SW = 0;
                    }
                }
            }

*/
