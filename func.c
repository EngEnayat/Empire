#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/ttydefaults.h>
void InitializeGameMap(char **map) {

    // k1 stands for kingdom1 and k2 for kingdom2
    int kingdomx, kingdomy;
    printf("Enter the coordinates of kingdom one and two: ");
    scanf("%d %d", &kingdomx, &kingdomy);
    if(kingdomx >= row || kingdomy >=col || kingdomx <0 || kingdomy<0){ 
        printf("%sInvalid input!!!%s\n%sPLEASE TRY AGAIN.\n%s", red, reset, red, reset);
        InitializeGameMap(map);
    }else map[kingdomx][kingdomy] = 'F';
    
    scanf("%d %d", &kingdomx, &kingdomy);
    if(kingdomx >= row || kingdomy >=col || kingdomy<0 || kingdomx<0){ 
        printf("%sInvalid input!!!%s\n%sPLEASE TRY AGAIN.\n%s", red, reset, red, reset);
        InitializeGameMap(map);
    }else map[kingdomx][kingdomy] = 'S';


    printf("How many villages are there: ");
    int VN; // village number
    scanf("%d", &VN);
    for (int i = 0; i < VN; i++) {
        int Xvillage, Yvillage;
        scanf("%d %d", &Xvillage, &Yvillage);
        if(Xvillage >= row || Yvillage >= col || Xvillage <0 || Yvillage <0){
        printf("%sInvalid input!!!%s\n%sPLEASE TRY AGAIN.\n%s", red, reset, red, reset);
        InitializeGameMap(map);
        }
        map[Xvillage][Yvillage] = 'V';
    }


    printf("How many banned homes are there: ");
    int xNumber; // homes number

    scanf("%d", &xNumber);
    for (int i = 0; i < xNumber; i++) {
        int x1, x2;
        scanf("%d %d", &x1, &x2);
        if(x1 >= row || x2 >= col){
        printf("%sInvalid input!!!%s\n%sPLEASE TRY AGAIN.\n%s", red, reset, red, reset);
        InitializeGameMap(map);
        }
        map[x1][x2] = 'X';
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] != 'X' && map[i][j] != 'V' && map[i][j] != 'F' && map[i][j] != 'S') map[i][j] = '1';
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

void printBanner(const char *message) {


    printf("%s*********************************%s\n", blue, reset);
    printf("*                               *\n");
    printf("*          %s%s%s         *\n", yellow, message,reset);
    printf("%s*                               *%s\n", blue, reset);
    printf("%s*********************************\n", blue);
    printf("%s", reset);
    printf("\n\n");
}

void printFunc(char **array) {

    printBanner("GRID DISPLAY");

    printf("%s", blue);
    printf("  +");
    for (int i = 0; i < col; i++) {
        printf("---+");
    }
    printf("\n");

    for (int i = 0; i < row; i++) {
        printf("  |");
        for (int j = 0; j < col; j++) {
            if (array[i][j] == 'X') {
                printf(" %sX%s |", Green, reset);
            } else if (array[i][j] == 'F' || array[i][j] == 'S') {
                printf(" %s%c%s |", purple, array[i][j], reset);
            } else if (array[i][j] == 'V') {
                printf(" %sV%s |", blue, reset);
            } else {
                printf(" %s%c%s |", red,array[i][j], reset);
            }
        }
        printf("\n");

        if (i != row - 1) {
            printf("  +");
            for (int k = 0; k < col; k++) {
                printf("%s---+%s", yellow, reset);
            }
            printf("\n");
        }
    }

    printf("%s", reset);
    printf("\n\n");
}

void info(struct player* func_Players){
    func_Players[0].employees = func_Players[1].employees = 1;
    func_Players[0].Gold = func_Players[1].Gold = 5;
    // printf("please enter the ratio of Gold, Food , Emoloyees and Soldiers: ");
    // int i=0;
    // scanf("%lf %lf %d %d", &func_Players[0].Gold, &func_Players[0].Food, &func_Players[0].employees, &func_Players[0].Soldier);
    // func_Players[1] = func_Players[0];
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
        if(SW) printf("\n%sPlayer %d's Turn%s\n\n",purple, player+1 , purple);
        printf("%s1 : buying food\n2 : hiring employee\n3 : hiring soldiers\n4 : making paths: \n5 for nothing: \n%s", blue, brightBlue);
        printf("%splease choose an action: %s", yellow, yellow);
        if (scanf("%d", &choose) != 1) {
            // If input is not an integer
            screen_clear;
            print_map;
            printf("%sInvalid input. Please enter a number between 1 and 5.%s\n", red, reset);
            SW =0;
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Check if the input is within the valid range
        if (choose < 1 || choose > 5) {
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
            if(players[turn].Food >= employee && players[turn].Food >3)
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
            printf("%sYou have %.lf Gold and can hire up to %d soldiers, please enter the number of soldires you want to hire: %s",blue,players[turn].Gold, (int)players[turn].Gold/2, brightBlue);
            scanf("%d", &soldier);
            if(players[turn].Gold>= 2*soldier && players[turn].Gold > 2)
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
        if(choose == 5)
        {
            screen_clear;
            print_map;
        }
        round++, SW++;
        if(round == 2){
            print_property(players);
            round =0;
            add_resourse(players);
        }
        // update the turn after each action
        turn = (turn == 0)? 1: 0;
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

void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited, int *pathHardValue, int **path, int *pathLength, int **shortestPath, int *shortestPathLength, int *shortestPathHardValue) {
    visited[x][y] = true;
    path[*pathLength][0] = x;
    path[*pathLength][1] = y;
    *pathHardValue += hardValues[x][y];
    (*pathLength)++;

    // Check if the current cell is a village
    for (int i = 0; i < villageCount; i += 2) {
        if (x == village[i] && y == village[i + 1] && !villageVisited[i / 2]) {
            // Village found, print path details
            printf("Path found for %c with total hard value %d\n", player, *pathHardValue);
            printf("Path: ");
            for (int j = 0; j < *pathLength; j++) {
                printf("(%d, %d) ", path[j][0], path[j][1]);
            }
            printf("\n");

            // Check if this path is the shortest
            if (*shortestPathLength == 0 || *pathLength < *shortestPathLength || (*pathLength == *shortestPathLength && *pathHardValue < *shortestPathHardValue)) {
                *shortestPathLength = *pathLength;
                *shortestPathHardValue = *pathHardValue;
                for (int j = 0; j < *pathLength; j++) {
                    shortestPath[j][0] = path[j][0];
                    shortestPath[j][1] = path[j][1];
                }
            }

            villageVisited[i / 2] = true;  // Mark village as visited
            *pathFound = true;  // Mark path as found
            visited[x][y] = false;  // Backtrack
            (*pathLength)--;
            *pathHardValue -= hardValues[x][y];
            return;
        }
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // Check all four directions for the presence of a village
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries
        if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
            continue;
        }

        // Check if the cell is a village
        for (int j = 0; j < villageCount * 2; j += 2) {
            if (village[j] == newX && village[j + 1] == newY && !villageVisited[j / 2]) {
                // Mark village as visited
                villageVisited[j / 2] = true;
                *pathFound = true;

                // Check if this path is the shortest
                if (*shortestPathLength == 0 || *pathLength < *shortestPathLength || (*pathLength == *shortestPathLength && *pathHardValue < *shortestPathHardValue)) {
                    *shortestPathLength = *pathLength;
                    *shortestPathHardValue = *pathHardValue;
                    for (int k = 0; k < *pathLength; k++) {
                        shortestPath[k][0] = path[k][0];
                        shortestPath[k][1] = path[k][1];
                    }
                }
            }
        }
    }

    // Proceed to explore further in all four directions
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries
        if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
            continue;
        }

        // Check if the cell is already visited or is an obstacle
        if (visited[newX][newY] || array[newX][newY] == 'X') {
            continue;
        }

        // Recursively visit the next cell
        dfs(array, newX, newY, visited, village, villageCount, pathFound, player, villageVisited, pathHardValue, path, pathLength, shortestPath, shortestPathLength, shortestPathHardValue);
    }

    visited[x][y] = false;  // Backtrack
    (*pathLength)--;
    *pathHardValue -= hardValues[x][y];

}
/*



    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries
        if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
            continue;
        }

        // Check if the cell is already visited or is an obstacle
        if (visited[newX][newY] || array[newX][newY] == 'X') {
            continue;
        }

        // Recursively visit the next cell
        dfs(array, newX, newY, visited, village, villageCount, pathFound, player, villageVisited, pathHardValue, path, pathLength, shortestPath, shortestPathLength, shortestPathHardValue);
    }

    visited[x][y] = false;  // Backtrack
    (*pathLength)--;
    *pathHardValue -= hardValues[x][y];



void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited, int *pathHardValue, int **path, int *pathLength, int **shortestPath, int *shortestPathLength, int *shortestPathHardValue) {
    visited[x][y] = true;
    path[*pathLength][0] = x;
    path[*pathLength][1] = y;
    (*pathLength)++;
    *pathHardValue += hardValues[x][y];

}
*/

void FindPaths(char **array, int village[], int villageNum, char player) {
    bool **visited = malloc(row * sizeof(bool *));
    for (int i = 0; i < row; i++) {
        visited[i] = calloc(col, sizeof(bool));
    }

    bool *villageVisited = calloc(villageNum / 2, sizeof(bool));  // Track visited villages
    bool pathFound = false;  // Track if a valid path has been found for this player
    int pathHardValue = 0;  // Track the total hard value of the path
    int **path = malloc(row * col * sizeof(int *));  // Track the coordinates of the path
    for (int i = 0; i < row * col; i++) {
        path[i] = malloc(2 * sizeof(int));
    }
    int pathLength = 0;  // Track the length of the path

    int **shortestPath = malloc(row * col * sizeof(int *));  // Track the coordinates of the shortest path
    for (int i = 0; i < row * col; i++) {
        shortestPath[i] = malloc(2 * sizeof(int));
    }
    int shortestPathLength = 0;  // Track the length of the shortest path
    int shortestPathHardValue = 0;  // Track the total hard value of the shortest path

    // Start search only from player's kingdom
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (array[i][j] == player) {
                dfs(array, i, j, visited, village, villageNum, &pathFound, player, villageVisited, &pathHardValue, path, &pathLength, shortestPath, &shortestPathLength, &shortestPathHardValue);
            }
        }
    }

    printf("Searching paths completed for player %c\n", player);
    if (shortestPathLength > 0) {
        printf("%sShortest path for %c with total hard value %d%s\n",Green, player, shortestPathHardValue, brightGreen);
        printf("Path: ");
        for (int i = 0; i < shortestPathLength; i++) {
            printf("(%d, %d) ", shortestPath[i][0], shortestPath[i][1]);
        }
        printf("\n");
    } else {
        printf("No path found for player %c\n", player);
    }

    for (int i = 0; i < row; i++) {
        free(visited[i]);
    }
    free(visited);
    free(villageVisited);
    for (int i = 0; i < row * col; i++) {
        free(path[i]);
        free(shortestPath[i]);
    }
    free(path);
    free(shortestPath);
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