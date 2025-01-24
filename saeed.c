#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>

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
#define clrscr() system("clear")

int rand_number();
void hide_cursor();
void welcome();
int initialize();
void clear_screen();
void making_road();
void gotoxy(int x, int y);
void hide_cursor();
void Game_init(struct player* players, char **array, int village[], int villageNum);
void print_property(struct player* players);
void add_resourse(struct player *players);

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

struct kingdom {
    int jx;
    int iy;
    double Gold;
    double Food;
    int employees;
    int Soldier;
    char name[20];
} king;

struct x_house {
    int jx;
    int iy;
} block[287];

struct vil {
    int gold;
    int food;
    int jx;
    int iy;
    int solider;
    int x_dis;
    int y_dis;
} village[287];

struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
};

int main() {
    srand(time(NULL));
    //hide_cursor();
    welcome();
    int er = initialize();
    if (er == 0) {
        making_road();
    }
    return 0;
}

char my_getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int rand_number() {
    return rand() % 5 + 1;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}

int initialize() {
    int i, iy;
    int j, jx;

    gotoxy(1, 90);
    printf("X dimension: ");
    scanf("%d", &dim_x);
    if (dim_x == 0) return 1;
    gotoxy(2, 90);
    printf("Y dimension: ");
    scanf("%d", &dim_y);
    if (dim_y == 0) return 1;

    gotoxy(3, 90);
    printf("Count of kingdom: ");
    scanf("%d", &numb_king);

    if (numb_king > 2 || numb_king < 0) return 1;

    i = 0;
    while (i < numb_king) {
        gotoxy(3 * i + 4, 90);
        printf(GREEN "X position of C: " RESET);
        scanf("%d", &king.jx);
        if (king.jx >= dim_x) {
            system("cls");
            gotoxy(4, 90);
            printf("X is too large.");
            gotoxy(5, 90);
            printf("Press any key to exit");
            my_getch();
            system("cls");
            return 1;
        }
        gotoxy(3 * i + 5, 90);
        printf(GREEN "Y position of C: " RESET);
        scanf("%d", &king.iy);
        if (king.iy >= dim_y) {
            system("cls");
            gotoxy(4, 90);
            printf("Y is too large.");
            gotoxy(5, 90);
            printf("Press any key to exit");
            my_getch();
            system("cls");
            return 1;
        }
        gotoxy(5 * i + 6, 90);
        printf(GREEN "Count of workers: " RESET);
        scanf("%d", &king.employees);
        gotoxy(5 * i + 7, 90);
        printf(GREEN "Range of food: " RESET);
        scanf("%lf", &king.Food);
        gotoxy(5 * i + 8, 90);
        printf(GREEN "Range of gold: " RESET);
        scanf("%lf", &king.Gold);
        gotoxy(5 * i + 9, 90);
        printf(GREEN "Count of solider: " RESET);
        scanf("%d", &king.Soldier);
        gotoxy(5 * i + 10, 90);
        printf(GREEN "King name: " RESET);
        scanf("%s", king.name);
        i++;
    }
    i--;
    gotoxy(5 * i + 11, 90);
    printf(BOLD_RED "Count of X house: " RESET);
    scanf("%d", &x_count);
    for (i = 0; i < x_count; i++) {
        gotoxy(2 * i + 12, 90);
        printf(BOLD_RED "X of block house %d: " RESET, i + 1);
        scanf("%d", &block[i].jx);
        if (block[i].jx >= dim_x) return 1;
        gotoxy(2 * i + 13, 90);
        printf(BOLD_RED "Y of block house %d: " RESET, i + 1);
        scanf("%d", &block[i].iy);
        if (block[i].iy >= dim_y) return 1;
        if (block[i].jx == king.jx && block[i].iy == king.iy) return 1;
    }
    i--;
    gotoxy(2 * i + 14, 90);
    printf(BOLD_MAGENTA "Count of villages: " RESET);
    scanf("%d", &v_count);
    if (v_count < 1) {
        system("cls");
        printf("The count of village can not be 0");
        return 1;
    }
    int offset_v = 2 * i + 14;
    int villa_count = 0;
    while (villa_count < v_count) {
        gotoxy(4 * villa_count + offset_v + 1, 90);
        printf("Village(%d) X coordinate: ", villa_count + 1);
        scanf("%d", &village[villa_count].jx);

        if (village[villa_count].jx >= dim_x) return 1;

        gotoxy(4 * villa_count + offset_v + 2, 90);
        printf("Village(%d) Y coordinate: ", villa_count + 1);
        scanf("%d", &village[villa_count].iy);

        if (village[villa_count].iy >= dim_y) return 1;

        gotoxy(4 * villa_count + offset_v + 3, 90);
        printf("Village(%d) gold range: ", villa_count + 1);
        scanf("%d", &village[villa_count].gold);

        gotoxy(4 * villa_count + offset_v + 4, 90);
        printf("Village(%d) food range: ", villa_count + 1);
        scanf("%d", &village[villa_count].food);

        village[villa_count].x_dis = abs(king.jx - village[villa_count].jx);
        village[villa_count].y_dis = abs(king.iy - village[villa_count].iy);
        villa_count++;
    }

    clear_screen();

    i = 0;
    j = 0;
    int v = 0;
    gotoxy(1, 70);
    printf(BOLD_GREEN "Your Dimension" RESET);
    clear_screen();
    y_c1 = king.iy;
    x_c1 = king.jx;
    for (iy = 0; iy < dim_y; iy++) {
        for (jx = 0; jx < dim_x; jx++) {
            map[iy][jx] = rand_number();
            if (iy == y_c1 && jx == x_c1) map[iy][jx] = 0;
            for (i = 0; i < x_count; i++) {
                for (j = 0; j < x_count; j++) {
                    if (iy == block[i].iy && jx == block[i].jx) map[iy][jx] = 9;
                }
            }

            for (i = 0; i < v_count; i++) {
                for (j = 0; j < 2; j++) {
                    if (iy == village[i].iy && jx == village[i].jx) map[iy][jx] = 0;
                }
            }
        }
    }
    for (iy = 0; iy < dim_y; iy++) {
        for (jx = 0; jx < dim_x; jx++) {
            gotoxy(2 * iy + 1, 4 * jx + 1 + 70);
            if (jx == king.jx && iy == king.iy) printf(BOLD_GREEN "C%d" RESET, 1);
            else printf(BOLD_WHITE "%d" RESET, map[iy][jx]);
        }
    }

    for (i = 0; i < x_count; i++) {
        iy = block[i].iy;
        jx = block[i].jx;
        gotoxy(2 * iy + 1, 4 * jx + 1 + 70);
        printf(RED "X" RESET);
    }

    for (i = 0; i < v_count; i++) {
        iy = village[i].iy;
        jx = village[i].jx;
        gotoxy(2 * iy + 1, 4 * jx + 1 + 70);
        printf(MAGENTA "V" RESET);
    }

    gotoxy(35, 0);
    for (i = 0; i < 210; i++) printf("-");
    i = 0;
    gotoxy(2 * y_c1 + 1, 4 * x_c1 + 1 + 70);

    return 0;
}

void making_road() {
    struct player players[2];
    players[0].Gold = king.Gold;
    players[0].Food = king.Food;
    players[0].employees = king.employees;
    players[0].Soldier = king.Soldier;
    players[1] = players[0]; // Assuming two players with the same initial resources

    Game_init(players, (char **)map, (int *)village, v_count);
}

void Game_init(struct player* players, char **array, int village[], int villageNum) {
    int turn = 0;
    screen_clear;
    clrscr();
    int round = 0, SW = 1;
    while (true) {
        // the user one turn
        int player = turn;
        int choose;
        // screen_clear;
        // printFunc(array, row, col);
        if (SW) printf("\n%sPlayer %d's Turn%s\n\n", purple, player + 1, purple);
        printf("%s1 : buying food\n2 : hiring employee\n3 : hiring soldiers\n4 : making paths: \n5 for nothing: \n%s", blue, brightBlue);
        printf("%splease choose an action: %s", yellow, yellow);
        if (scanf("%d", &choose) != 1) {
            // If input is not an integer
            screen_clear;
            clrscr();
            printf("%sInvalid input. Please enter a number between 1 and 5.%s\n", red, reset);
            SW = 0;
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Check if the input is within the valid range
        if (choose < 1 || choose > 5) {
            screen_clear;
            clrscr();
            printf("%sInvalid choice. Please select a valid option.%s\n", red, reset);
            SW = 0;
            continue;
        }

        if (choose == 1) {
            screen_clear;
            clrscr();
            printf("%syou have %.lf Gold and can buy food up to %.lf, please enter the food you desire: %s", blue, players[turn].Gold, players[turn].Gold, brightBlue);
            double food;
            scanf("%lf", &food);
            if (players[turn].Gold >= 1 && players[turn].Gold >= food) {
                players[turn].Gold -= food;
                players[turn].Food += food;
            } else {
                screen_clear;
                clrscr();
                printf("%sinsufficient resourse try again!%s\n", red, reset);
                SW = 0;
                continue;
            }
        }
        screen_clear;
        clrscr();
        if (choose == 2) {
            int employee;
            screen_clear;
            clrscr();
            printf("%sYou have %.lf Food and can Hire up to %d employee, please enter your desire: %s", blue, players[turn].Food, (int)players[turn].Food / 3, brightBlue);
            scanf("%d", &employee);
            if (players[turn].Food >= employee && players[turn].Food > 3) {
                players[turn].employees += employee;
                players[turn].Food -= employee * 3;
            } else {
                screen_clear;
                clrscr();
                printf("%sYou don't have sufficient resouse please try again another attemp!%s\n", red, reset);
                SW = 0;
                continue;
            }
        }
        screen_clear;
        clrscr();
        if (choose == 3) {
            int soldier;
            screen_clear;
            clrscr();
            printf("%sYou have %.lf Gold and can hire up to %d soldiers, please enter the number of soldires you want to hire: %s", blue, players[turn].Gold, (int)players[turn].Gold / 2, brightBlue);
            scanf("%d", &soldier);
            if (players[turn].Gold >= 2 * soldier && players[turn].Gold > 2) {
                players[turn].Gold -= soldier / 2;
                players[turn].Soldier += soldier;
            } else {
                screen_clear;
                clrscr();
                printf("%sinsufficient resourses please try another one again!%s\n", red, reset);
                SW = 0;
                continue;
            }
        }
        screen_clear;
        clrscr();
        if (choose == 4) {
            char Athlete = (player == 0) ? 'F' : 'S';
            screen_clear;
            clrscr();
            FindPaths(array, village, village_num, Athlete);
            continue;
        }
        if (choose == 5) {
            screen_clear;
            clrscr();
        }
        round++, SW++;
        if (round == 2) {
            print_property(players);
            round = 0;
            add_resourse(players);
        }
        // update the turn after each action
        turn = (turn == 0) ? 1 : 0;
    }
}

void print_property(struct player* players) {
    printf("%splayer one Golds: %.2lf%s\n", Green, players[0].Gold, brightGreen);
    printf("%splayer one Foods: %.2lf%s\n", Green, players[0].Food, brightGreen);
    printf("%splayer one Employees: %d%s\n", Green, players[0].employees, brightGreen);
    printf("%splayer one Soldiers: %d%s\n", Green, players[0].Soldier, brightGreen);
    printf("%splayer two Golds: %.2lf%s\n", Green, players[1].Gold, brightGreen);
    printf("%splayer two Foods: %.2lf%s\n", Green, players[1].Food, brightGreen);
    printf("%splayer two Employees: %d%s\n", Green, players[1].employees, brightGreen);
    printf("%splayer two Soldiers: %d%s\n", Green, players[1].Soldier, brightGreen);
}

void add_resourse(struct player *players) {
    players[0].Food++;
    players[0].Gold++;
    players[1].Food++;
    players[1].Gold++;
}

void clear_screen() {
    printf("\033[2J\033[1;1H");
}

void hide_cursor() {
    initscr(); // Initialize the screen
    curs_set(0); // Hide the cursor
}

void welcome() {
    clear_screen();

    gotoxy(1, 50);
    printf(GREEN "*             *  *****  *       ****  ***        *   *      *****\n" RESET);
    gotoxy(2, 50);
    printf(GREEN " *           *   *      *      *     *   *      * * * *     *    \n" RESET);
    gotoxy(3, 50);
    printf(GREEN "  *    *    *    ****   *      *     *   *     *   *   *    **** \n" RESET);
    gotoxy(4, 50);
    printf(GREEN "   *  *  * *     *      *      *     *   *    *         *   *    \n" RESET);
    gotoxy(5, 50);
    printf(GREEN "    *     *      *****  *****   ****  ***    *           *  *****\n" RESET);

    my_getch();
    clear_screen();
}
