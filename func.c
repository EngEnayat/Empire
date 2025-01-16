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
    if(k1 >= row || k2 >=col){ 
        printf("%sInvalid input%s!!!\n%sPROGRAM END.\n%s", red, reset, red, reset);
        exit (0);
    }else map[k1][k2] = 'F';
    
    scanf("%d %d", &k1, &k2);
    if(k1 >= row || k2 >=col){ 
        printf("%sInvalid input!!!%s\n%sPROGRAM END.\n%s", red, reset, red, reset);
        exit (0);
    }else map[k1][k2] = 'S';
    printf("How many S_Village_flage are there: ");
    int VN;
    scanf("%d", &VN);
    for (int i = 0; i < VN; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        if(v1 >= row || v2 >= col){
            printf("%sInvalid input!!!%s\n%sPROGRAM END.\n%s", red, reset, red, reset);
            exit(0);
        }
        map[v1][v2] = 'V';
    }

    printf("How many banned homes are there: ");
    int XN;
    scanf("%d", &XN);
    for (int i = 0; i < XN; i++) {
        int x1, x2;
        scanf("%d %d", &x1, &x2);
        if(x1 >= row || x2 >= col){
            printf("%sInvalid input!!!%s\n%sPROGRAM END.\n%s", red, reset, red, reset);
            exit(0);
        }
        map[x1][x2] = 'X';
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] != 'X' && map[i][j] != 'V' && map[i][j] != 'F' && map[i][j] != 'S') map[i][j] = '1';
        }
    }
}

void GenerateRandom(char **array, int col) {
    srand(time(0));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (array[i][j] == '1') {
                int randomNum = (rand() % 5) + 1;
                char ch = '0' + randomNum;
                array[i][j] = ch;
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
            } else if (array[i][j] == 'F' || array[i][j] == 'S') {
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
void Game_init(struct player* players, char **array, int village[], int villageNum){
    int turn =0;
    screen_clear;
    print_map;
    int round =0, SW=1;
    while(true){
        // the user one turn
        int player = turn;
        int choose;
        // screen_clear;
        // printFunc(array, row, col);
        if(SW) printf("\n%sPlayer %d's Turn%s\n",purple, player+1 , purple);
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
            char Athlete = (player == 0)?'F':'S';
            screen_clear;
            print_map;
            FindPaths(array, village, village_num, Athlete);
            continue;
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

void FindPaths(char **array, int village[], int villageNum, char player) {
    screen_clear;
    print_map;
    bool **visited = malloc(row * sizeof(bool *));
    for (int i = 0; i < row; i++) {
        visited[i] = calloc(col, sizeof(bool));
    }
    if(visited == NULL){
        printf("Allocating memory for visited goes wrong! ");
        exit (0);
    }

    bool *villageVisited = calloc(villageNum / 2, sizeof(bool));  // Track visited villages
    if(villageVisited == NULL){
        printf("Allocating memory for village visiting Failed!");
        exit (0);
    }
    bool pathFound = false;  // Track if a valid path has been found for this player
    path = (player == 'F') ? 0 : 1;  // Set path index for player (0 for player 1, 1 for player 2)

    // Start search only from player's kingdom
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (array[i][j] == player) {
                dfs(array, i, j, visited, village, villageNum, &pathFound, player, villageVisited);
                if (pathFound) break;  // Stop after finding the first valid path
            }
        }
        if (pathFound) break;  // Stop after finding the first valid path
    }
    printf("Searching paths completed for player %c\n", player);

    for (int i = 0; i < row; i++) {
        free(visited[i]);
    }
    free(visited);
    free(villageVisited);
}

void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited)
{
    //if (*pathFound) return;  // Stop if a valid path is already found

    visited[x][y] = true;

    // Check if the current cell is a village
    for (int i = 0; i < villageCount; i += 2) {
        if (x == village[i] && y == village[i + 1] && !villageVisited[i / 2]) {
            // Village found, print path details
            path++;
            printf("Path found for %c at (%d, %d) with total hard value %d\n", player, x, y, HardValue[path]);
            villageVisited[i / 2] = true;  // Mark village as visited
            *pathFound = true;  // Mark path as found
            visited[x][y] = false;  // Backtrack
            return;
        }
    }
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        // Check if this cell is a village
        for (int j = 0; j < villageCount; j += 2) {
            if (newX == village[j] && newY == village[j + 1]) {
                *pathFound = true;  // Set path found flag
                printf("Path found for %c at (%d, %d) with total hard value %d\n", player, newX, newY, HardValue[path]);
                visited[x][y] = false;  // Backtrack
                return;
            }
        }
    }
    int sign_move = 0;
    int i, xMove, yMove;
    char move_value = '5';

    for (i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        // Check if the new position is valid
        if (isValidMove(newX, newY, visited, array, player, village, villageVisited, villageCount)) {
            sign_move = 1;
            // printf("It was valid and I am here current x y and hard %d %d %c\n", newX, newY, array[newX][newY]);
            // If the value at new position is less than the current best move_value
            if (array[newX][newY] < move_value) {
                //printf("%c %c array value and move_value\n", array[newX][newY], move_value);
                move_value = array[newX][newY];  // Convert char to integer (e.g., '3' -> 3)
                xMove = newX;
                yMove = newY;
            }
        }
    }
    int number_move = move_value - '0';
    if (sign_move) 
    {
        HardValue[path] += number_move;
        
        // printf("hard value and current: %d %d\n", HardValue[path], array[xMove][yMove]-'0');
        //printf("%d hard_value\n", array[xMove,yMove]-'0');
        printf(" (%d,%d)-->", xMove, yMove);  // Append to path

        //if (*pathFound) return;  // Stop recursion if a path is found
        // // Call dfs with new position
        dfs(array, xMove, yMove, visited, village, villageCount, pathFound, player, villageVisited);
    }
        visited[x][y] = false;  // Backtrack
}

bool isValidMove(int x, int y, bool **visited, char **array, char player, int village[], bool *villageVisited, int villageCount) {
    char enemy = (player == 'F') ? 'S' : 'F';

    // Ensure the move is within bounds and valid
    if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || array[x][y] == 'X' || array[x][y] == enemy) {
        return false;
    }

    // Check if the target cell is a previously visited village
    for (int i = 0; i < villageCount; i += 2) {
        if (x == village[i] && y == village[i + 1] && villageVisited[i / 2]) {
            return false;  // Already visited village
        }
    }

    return true;
}
void XVcoordinates(char **array, int *HomeCoordinateArray,int *VillageCoordinateArray,int *HomeAmount,int *VillageAmount){
    // finding the Village Coordinates
    int HomeCurr =0, VillageCurr=0;
    for(int i=0; i<row;i++)
    {
        for(int j=0; j<col;j++)
        {
            if(array[i][j] == 'V')
            {
                *(VillageCoordinateArray + VillageCurr) = i;
                *(VillageCoordinateArray + VillageCurr+1) = j;
                F_Village_flage[VillageCurr] = i;
                F_Village_flage[VillageCurr+1] = j;
                S_Village_flage[VillageCurr] = i;
                S_Village_flage[VillageCurr+1] = j;
                VillageCurr+=2;
                // printf("%d", *VillageAmount);
            }
        }
    }
    for(int i=0; i<row;i++)
    {
        for(int j=0; j<col;j++)
        {
            if(array[i][j] == 'X')
            {
                *(HomeCoordinateArray +HomeCurr) = i;
                *(HomeCoordinateArray +HomeCurr+1) = j;
                HomeCurr+=2;
            }
        }
    }
    *VillageAmount = VillageCurr;
    village_num = VillageCurr;
    *HomeAmount = HomeCurr;
}