#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"
#include <limits.h>
void InitializeGameMap(char **map) {
    // k1 stands for kingdom1 and k2 for kingdom2
    int kingdomx, kingdomy;
    printf("Enter the coordinates of kingdom one: ");
    getchar();
    fscanf(file, "%d %d", &kingdomx, &kingdomy);
    printf("you entered %d %d\n", kingdomx, kingdomy);
    // scanf("%d %d", &kingdomx, &kingdomy);

    if(kingdomx >= row || kingdomy >=col || kingdomx <0 || kingdomy<0){ 
        printf("%sInvalid input!!!%s\n%sProgram end\n%s", red, reset, red, reset);
        exit(0);
    }else map[kingdomx][kingdomy] = 'F';
    printf("Enter the coordinates of kingdom two: ");
    getchar();
    // scanf("%d %d", &kingdomx, &kingdomy);
    fscanf(file, "%d %d", &kingdomx, &kingdomy);
    printf("you entered %d %d\n", kingdomx, kingdomy);
    if(kingdomx >= row || kingdomy >=col || kingdomy<0 || kingdomx<0){ 
        printf("%sInvalid input!!!%s\n%sPROGRAM END.\n%s", red, reset, red, reset);
        exit(0);
    }else map[kingdomx][kingdomy] = 'S';

    printf("How many villages are there: ");
    getchar();
    int VN; // village number
    fscanf(file, "%d", &VN);
    printf("you entered %d\n", VN);
    // scanf("%d", &VN);
    for (int i = 0; i < VN; i++) {
        int Xvillage, Yvillage;
        printf("enter the coordinated of village x and y");
        getchar();
        fscanf(file, "%d %d",&Xvillage, &Yvillage);
        printf("you entered %d %d\n", Xvillage, Yvillage);
        // scanf("%d %d", &Xvillage, &Yvillage);
        if(Xvillage >= row || Yvillage >= col || Xvillage <0 || Yvillage <0){
            printf("%sInvalid input!!!%s\n%sPROGRAM END.\n%s", red, reset, red, reset);
            exit(0);
        }
        map[Xvillage][Yvillage] = 'V';
    }


    printf("How many banned homes are there: ");
    getchar();
    int xNumber; // homes number
    fscanf(file, "%d", &xNumber);
    printf("you entered %d\n", xNumber);
    // scanf("%d", &xNumber);
    for (int i = 0; i < xNumber; i++) {
        int x1, x2;
        printf("enter the coordinates of x and y homes: ");
        getchar();
        fscanf(file, "%d %d", &x1, &x2);
        printf("you entered %d %d\n", x1, x2);
        // scanf("%d %d", &x1, &x2);
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

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
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

    gotoxy(1,60);
    printf("%s*********************************%s\n", blue, reset);
    gotoxy(2,60);
    printf("*                               *\n");
    gotoxy(3,60);
    printf("*          %s%s%s         *\n", yellow, message,reset);
    gotoxy(4,60);
    printf("%s*                               *%s\n", blue, reset);
    gotoxy(5,60);
    printf("%s*********************************\n", blue);
    gotoxy(6,60);
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
    //screen_clear;
    //print_map;
    int round =0, SW=1;
    while(true){
        // the user one turn
        int player = turn;
        int choose;
        screen_clear;
        print_map;
        if(SW) printf("\n%sPlayer %d's Turn%s\n\n",purple, player+1 , purple);
        printf("%s1 : buying food\n2 : hiring employee\n3 : hiring soldiers\n4 : making paths: \n5 for starting fight if state available: \n%s", blue, brightBlue);
        printf("%splease choose an action: %s", yellow, yellow);
        // scanf("%d", &choose);
        getchar();
        fscanf(file, "%d", &choose);
        printf("you entered %d", choose);
        getchar();


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
            // scanf("%lf", &food);
            getchar();
            fscanf(file, "%lf", &food);
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
            getchar();
            printf("%sYou have %.lf Food and can Hire up to %d employee, please enter your desire: %s",blue, players[turn].Food, (int)players[turn].Food /3, brightBlue);
            // scanf("%d", &employee);
            fscanf(file, "%d", &employee);
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
            // scanf("%d", &soldier);
            getchar();
            fscanf(file, "%d", &soldier);
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
        if(choose == 5) // I put 5 a sign for checking fight state but you replace in your code and it should check each round, may in the first in making map stage the kingdoms locate beside each other
        {
            screen_clear;
            print_map;
            char Athlete = (player == 0)?'F':'S';
            CheckFightState(array, 3, 4, Athlete, players);
            getchar();
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
void AbsoluteFight(struct player* players)
{
    screen_clear;
    if(players[0].Soldier > players[1].Soldier)
    {
        printf("%sCongratulations!!!\nPlayer One %s%c%s is Winner!%s", Green, blue, 'F',blue, Green);
        printf("\nGame END!");
        exit(0);
    }
    else if(players[1].Soldier > players[0].Soldier)
    {
        printf("%sCongratulations!!!\nPlayer two %s%c%s is Winner!%s", Green, blue, 'S',blue, Green);
        printf("\nGame END!");
        exit(0);
    }
    char winner = (players[0].Gold > players[1].Gold)? 'F' : 'S';
    gotoxy(1, 60);
    printf("%sCongratulations Player %c %s\n", Green,winner,Green);
    gotoxy(2, 60);
    printf("Hope you enjoy, GAME END!");
    exit(0);

}

// first shape of function CheckFightState
void CheckFightState(char** array,int x,int y,char player, struct player* players){
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    char enemy = (player == 'F')? 'S' : 'F';
    for(int i=0; i<4;i++)
    {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if(newX >= 0 && newX < row && newY >= 0 && newY < col)
        {
            if(array[newX][newY] == enemy) // if it reaches into enemy kingdom
            {
                AbsoluteFight(players);
            }
            else if(array[newX][newY] == '=') // if there found an enemy path, consider '=' is the hard value of enemy paths that is shown in the map
            {
                
                PathFighting(array, players); // subsidiary fight for making path beside enemy's road
            }
        }
    }

}
void PathFighting(char **array,struct player* players)
{
    // F for player first and S for second player
    char winner = (players[0].Soldier > players[1].Soldier)? 'F' : 'S';
    if(winner == 'F')
    {
        for(int i=0; i< row;i++)
        {
            for(int j=0; j<col; j++)
            {
                if(array[i][j] == 0) // consider player two or S kigdom path's sign is 0, replace with real cahracter that you've chosen saeed
                {
                    array[i][j] = hardValues[i][j];
                }
            }
        }
        players[1].Soldier = players[0].Soldier - players[1].Soldier; // soldeirs dead
    }
    else
    {
        for(int i=0; i< row;i++)
        {
            for(int j=0; j<col; j++)
            {
                if(array[i][j] == 9) // consider player two path sign is 9, replace with real character on your own codes
                {
                    array[i][j] = hardValues[i][j];
                }
            }
        }
    }
    players[0].Soldier = players[1].Soldier - players[0].Soldier;
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

void FindPaths(char **array, int village[], int villageNum, char player) {
    bool **visited = malloc(row * sizeof(bool *));
    for (int i = 0; i < row; i++) {
        visited[i] = calloc(col, sizeof(bool));
    }

    bool *villageVisited = calloc(villageNum / 2, sizeof(bool));  // Track visited villages
    bool pathFound = false;  // Track if a valid path has been found for this player

    int **path = malloc(row * col * sizeof(int *));  // Track the coordinates of the path
    for (int i = 0; i < row * col; i++) {
        path[i] = malloc(2 * sizeof(int));
    }
    int pathLength = 0, pathHardValue = 0;  // Track the length and the hard value of the path

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
        printf("%sShortest path for %c with total hard value %d%s\n", Green, player, shortestPathHardValue, brightGreen);
        printf("Path: ");
        for (int i = 0; i < shortestPathLength; i++) {
            printf("(%d, %d) ", shortestPath[i][0], shortestPath[i][1]);
        }
        printf("\n");
    } else {
        printf("No path found for player %c\n", player);
    }

    // Free allocated memory
    for (int i = 0; i < row; i++) {
        free(visited[i]);
    }
    free(visited);

    for (int i = 0; i < row * col; i++) {
        free(path[i]);
        free(shortestPath[i]);
    }
    free(path);
    free(shortestPath);
    free(villageVisited);
}

void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited, int *pathHardValue, int **path, int *pathLength, int **shortestPath, int *shortestPathLength, int *shortestPathHardValue) {
    visited[x][y] = true;
    path[*pathLength][0] = x;
    path[*pathLength][1] = y;
    (*pathLength)++;
    *pathHardValue += hardValues[x][y];

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
    int directionValues[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX}; // Initialize with max values

    // Evaluate hard values in all four directions
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries and avoid enemy cells
        if (newX >= 0 && newY >= 0 && newX < row && newY < col && !visited[newX][newY] && array[newX][newY] != 'X' && array[newX][newY] != (player == 'F' ? 'S' : 'F')) {
            directionValues[i] = hardValues[newX][newY];
        }
    }

    // Sort directions based on hard values (ascending order)
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (directionValues[i] > directionValues[j]) {
                int tempValue = directionValues[i];
                directionValues[i] = directionValues[j];
                directionValues[j] = tempValue;

                int tempDir[2] = {directions[i][0], directions[i][1]};
                directions[i][0] = directions[j][0];
                directions[i][1] = directions[j][1];
                directions[j][0] = tempDir[0];
                directions[j][1] = tempDir[1];
            }
        }
    }

    // Proceed to explore further in all four directions based on sorted hard values
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries
        if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
            continue;
        }

        // Check if the cell is already visited or is an obstacle
        if (visited[newX][newY] || array[newX][newY] == 'X' || array[newX][newY] == (player == 'F' ? 'S' : 'F')) {
            continue;
        }

        // Recursively visit the next cell
        dfs(array, newX, newY, visited, village, villageCount, pathFound, player, villageVisited, pathHardValue, path, pathLength, shortestPath, shortestPathLength, shortestPathHardValue);

        // Stop further exploration if the shortest path is found
        if (*pathFound) {
            break;
        }
    }

    visited[x][y] = false;  // Backtrack
    (*pathLength)--;
    *pathHardValue -= hardValues[x][y];
}

// DFS for finding all possible paths
/*void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited, int *pathHardValue, int **path, int *pathLength, int **shortestPath, int *shortestPathLength, int *shortestPathHardValue) {
    visited[x][y] = true;
    path[*pathLength][0] = x;
    path[*pathLength][1] = y;
    (*pathLength)++;
    *pathHardValue += hardValues[x][y];

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
    int directionValues[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX}; // Initialize with max values

    // Evaluate hard values in all four directions
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries and avoid enemy cells
        if (newX >= 0 && newY >= 0 && newX < row && newY < col && !visited[newX][newY] && array[newX][newY] != 'X' && array[newX][newY] != (player == 'F' ? 'S' : 'F')) {
            directionValues[i] = hardValues[newX][newY];
        }
    }

    // Sort directions based on hard values (ascending order)
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (directionValues[i] > directionValues[j]) {
                int tempValue = directionValues[i];
                directionValues[i] = directionValues[j];
                directionValues[j] = tempValue;

                int tempDir[2] = {directions[i][0], directions[i][1]};
                directions[i][0] = directions[j][0];
                directions[i][1] = directions[j][1];
                directions[j][0] = tempDir[0];
                directions[j][1] = tempDir[1];
            }
        }
    }

    // Proceed to explore further in all four directions based on sorted hard values
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // Check boundaries
        if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
            continue;
        }

        // Check if the cell is already visited or is an obstacle
        if (visited[newX][newY] || array[newX][newY] == 'X' || array[newX][newY] == (player == 'F' ? 'S' : 'F')) {
            continue;
        }

        // Recursively visit the next cell
        dfs(array, newX, newY, visited, village, villageCount, pathFound, player, villageVisited, pathHardValue, path, pathLength, shortestPath, shortestPathLength, shortestPathHardValue);
    }

    visited[x][y] = false;  // Backtrack
    (*pathLength)--;
    *pathHardValue -= hardValues[x][y];
}*/
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