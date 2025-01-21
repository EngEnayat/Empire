#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

void AssigningValue(char **map) {
    int k1, k2;
    printf("Enter the coordinates of kingdom one and two: ");
    scanf("%d %d", &k1, &k2);
    map[k1][k2] = 'C';
    scanf("%d %d", &k1, &k2);
    map[k1][k2] = 'C';

    printf("How many villages are there: ");
    int VN;
    scanf("%d", &VN);
    for (int i = 0; i < VN; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        map[v1][v2] = 'V';
    }

    printf("How many banned homes are there: ");
    int XN;
    scanf("%d", &XN);
    for (int i = 0; i < XN; i++) {
        int x1, x2;
        scanf("%d %d", &x1, &x2);
        map[x1][x2] = 'X';
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] != 'X' && map[i][j] != 'V' && map[i][j] != 'C') map[i][j] = '1';
        }
    }
}

void GenerateRandom(char **array) {
    srand(time(NULL));
    hardValues = malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        hardValues[i] = malloc(col * sizeof(int));
        for (int j = 0; j < col; j++) {
            if (array[i][j] != 'X' && array[i][j] != 'V' && array[i][j] != 'F' && array[i][j] != 'S') {
                array[i][j] = '0' + (rand() % 5) +1;  // Assign random number between '0' and '9'
                hardValues[i][j] = array[i][j] - '0';  // Convert char to int
            }
        }
    }
}

void printBanner(const char* title) {
    printf("%s\n", blue);
    printf("===========================================\n");
    printf("|%s%20s%13s%s|\n", yellow, "", title, yellow);
    printf("===========================================%s\n\n", reset);
}

void printFunc(char **array) {
    printBanner("GRID DISPLAY");
    for (int i = 0; i < row; i++) {
        printf("                  %s|%s", yellow, reset);
        for (int j = 0; j < col; j++) {
            if (array[i][j] == 'X') {
                printf(Green" %c "brightGreen, array[i][j]);
            } else if (array[i][j] == 'C') {
                printf(purple" %c "yellow, array[i][j]);
            } else if (array[i][j] == 'V') {
                printf(blue" %c "reset, array[i][j]);
            } else {
                printf(red" %c "reset, array[i][j]);
            }
            printf(" %s|%s", yellow, reset);
        }
        printf("\n");
        if (i != row - 1) {
            printf("                  ");
            for (int k = 0; k < (col * 6); k++) {
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

void clrscr() {
    printf("\033[H\033[J"); // Move to the top-left corner and clear the entire screen
}

void info(struct player* func_Players){
    printf("please enter the ratio of Gold, Food , Emoloyees and Soldiers: ");
    int i=0;
    scanf("%lf %lf %d %d", &func_Players[0].Gold, &func_Players[0].Food, &func_Players[0].employees, &func_Players[0].Soldier);
    func_Players[1] = func_Players[0];
}
void Game_init(struct player* players, char **array){
    int turn =0;
    screen_clear;
    print_map;
    int round =0, SW=1;
    while(true){
        // the user one turn
        int temp = turn;
        int choose;
        // screen_clear;
        // printFunc(array, row, col);
        if(SW) printf("\n%sPlayer %d's Turn%s\n",purple, temp+1 , purple);
        printf("%splease choose an action: %s\n", yellow, yellow);
        printf("%s1 : buying food\n2 : hiring employee\n3 : hiring soldiers\n4 : making paths: %s", white, brightBlue);

        if (scanf("%d", &choose) != 1) {
            // If input is not an integer
            screen_clear;
            print_map;
            printf("%sInvalid input. Please enter a number between 1 and 4.%s\n", red, reset);
            SW =0;
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Check if the input is within the valid range
        if (choose < 1 || choose > 4) {
            screen_clear;
            print_map;
            printf("%sInvalid choice. Please select a valid option.%s\n", red, reset);
            SW =0;
            continue;
        }        

        if(choose == 1){
            screen_clear;
            print_map;
            printf ("%syou have %.lf Gold and can buy food up to %.lf, please enter the food you desire: %s",blue, players[turn].Gold, players[turn].Gold, brightBlue);
            double food;
            scanf("%lf", &food);
            if(players[turn].Gold>=1 && players[turn].Gold >=food){
                players[turn].Gold -= food;
                players[turn].Food += food;
            }else{
                screen_clear;
                print_map;
                printf("%sinsufficient resourse try again!%s\n", red, reset);
                SW =0;
                continue;
            }

        }
        screen_clear;
        print_map;
        if(choose == 2)
        {
            int employee;
            screen_clear;
            print_map;
            printf("%sYou have %.lf Food and can Hire up to %d employee, please enter your desire: %s",blue, players[turn].Food, (int)players[turn].Food /3, brightBlue);
            scanf("%d", &employee);
            if(players[turn].Food >= employee)
            {
                    players[turn].employees += employee;
                    players[turn].Food -= employee * 3;               
            }else {
                screen_clear;
                print_map;
                printf("%sYou don't have sufficient resouse please try again another attemp!%s\n", red, reset);
                SW =0;
                continue;
            }
        }
        screen_clear;
        print_map;
        if(choose == 3)
        {
            int soldier;
            screen_clear;
            print_map;
            printf("%sYou have %.lf Gold and can hire up to %d soldiers, please enter the number of soldires you want to hire: %s",blue,players[turn].Food, (int)players[turn].Gold/3, brightBlue);
            scanf("%d", &soldier);
            if(players[turn].Gold>= 2*soldier)
            {
                players[turn].Gold -= soldier/2;
                players[turn].Soldier += soldier;
            }else{
                screen_clear;
                print_map;
                printf("%sinsufficient resourses please try another one again!%s\n", red, reset);
                SW =0;
                continue;
            }
        }
        screen_clear;
        print_map;
        if(choose == 4){
            screen_clear;
            print_map;
            
        }
        round++, SW++;
        if(round == 2){
            print_property(players);
            round =0;
            add_resourse(players);
        }
        if(turn ==0) turn =1;
        else if(turn ==1) turn =0;
    }
}
void print_property(struct player* players)
{
    printf("%splayer one Golds: %.2lf%s\n",Green, players[0].Gold, brightGreen);
    printf("%splayer one Foods: %.2lf%s\n",Green, players[0].Food, brightGreen);
    printf("%splayer one Employees: %d%s\n",Green, players[0].employees,brightGreen);
    printf("%splayer one Soldiers: %d%s\n",Green, players[0].Soldier, brightGreen);
    printf("%splayer two Golds: %.2lf%s\n", Green, players[1].Gold, brightGreen);
    printf("%splayer two Foods: %.2lf%s\n",Green, players[1].Food, brightGreen);
    printf("%splayer two Employees: %d%s\n",Green, players[1].employees, brightGreen);
    printf("%splayer two Soldiers: %d%s\n", Green,players[1].Soldier, brightGreen);
}
void add_resourse(struct player *players){
    players[0].Food++;
    players[0].Gold++;
    players[1].Food++;
    players[1].Gold++;
}