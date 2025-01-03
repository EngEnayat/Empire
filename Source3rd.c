#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define blue "\033[1;34m"
#define brightBlue "\033[0;34m"
#define Green "\033[1;32m"
#define brightGreen "\033[0m"
#define white "\033[1;10m"
#define brightRed "\033[0m"
#define red "\033[1;31m"
#define yellow "\033[1;33m"
#define purple "\033[1;35m"
#define reset "\033[0m"
int n,m;
struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
};
void AssigningValue(char map[][m], int n, int m){
    int k1,k2;
    printf("enter the coordinates of kingdom one and two");
    scanf("%d %d", &k1, &k2);
    map[k1][k2] = 'C';
    scanf("%d %d", &k1, &k2);
    map[k1][k2] = 'C';
    printf("how many villages are there: ");
    int VN;
    scanf("%d", &VN);
    for(int i=0;i<VN;i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        map[v1][v2] = 'V';
    }
    printf("how many banned homes are there: ");
    int XN;
    scanf("%d", &XN);
    for(int i=0; i<XN;i++){
        int x1, x2;
        scanf("%d %d", &x1, &x2);
        map[x1][x2] = 'X';
    }
    for(int i=0 ;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]!='X' && map[i][j]!='V' && map[i][j]!='C') map[i][j] = '1';
        }
    }
    
}
void clrscr() {
    // Clear the player action area, but keep the map intact
    printf("\033[6;0H");  // Move cursor to the area for the player's action input (you can adjust this if needed)
    for (int i = 0; i < 5; i++) {  // Adjust this for the height of the action area
        printf("\033[K");  // Clears the current line
    }
}
bool isValidMove(int x, int y, int num, bool visited[][m], char array[][m]) {
    return (x >= 0 && x < num && y >= 0 && y < num && !visited[x][y] && array[x][y] != 'X');
}

void printBanner(const char* title) {
    printf("%s\n", blue);
    printf("===========================================\n");
    printf("|%s%20s%13s%s|\n", yellow, "", title, yellow);
    printf("===========================================%s\n\n", reset);
}
void GenerateRandom(char array[][m], int n, int m) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] == '1') {
                int randomNum = (rand() % 5) + 1;
                char ch = '0' + randomNum;
                array[i][j] = ch;
            }
        }
    }
}

void printFunc(char array[][m], int n,int m) {
    printBanner("GRID DISPLAY");
    for (int i = 0; i < n; i++) {
        printf("                  %s|%s", yellow, reset);
        for (int j = 0; j < m; j++) {
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
        if (i != n - 1) {
            printf("                  ");
            for (int k = 0; k < (m* 6); k++) {
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

int VillageCoordinate(char array[][m], int village[], int n, int m) {
    int curr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] == 'V') {
                village[curr] = i;
                village[curr + 1] = j;
                curr += 2;
            }
        }
    }
    return curr;
}

int HomeCoordinates(char array[][m], int Home[], int n, int m) {
    int curr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] == 'X') {
                Home[curr] = i;
                Home[curr + 1] = j;
                curr += 2;
            }
        }
    }
    return curr;
}

void dfs(char array[][m], int x, int y, int num, bool visited[][m], int pathValue, int village[], int villageCount, int *pathCount, int path[]) {
    visited[x][y] = true;
    path[pathValue] = x * m + y; // Store the path coordinates

    // Check if the current cell is a village
    for (int i = 0; i < villageCount; i += 2) {
        if (x == village[i] && y == village[i + 1]) {
            printf("%sPath found to Village (%d, %d) with Hard Value: %d%s\n", yellow, x, y, pathValue, reset);
            // Print the path
            for (int i = 0; i <= pathValue; i++) {
                int cx = path[i] / m;
                int cy = path[i] % m;
                printf("(%d, %d) -> ", cx, cy);
            }
            printf("\n");
            (*pathCount)++;
            break;
        }
    }

    // Move in all four directions
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (isValidMove(newX, newY, num, visited, array)) {
            int additionalValue = (array[newX][newY] >= '1' && array[newX][newY] <= '5') ? array[newX][newY] - '0' : 0;
            dfs(array, newX, newY, num, visited, pathValue + additionalValue, village, villageCount, pathCount, path);
        }
    }

    // Backtrack (do not unmark as visited immediately after finding a path)
    visited[x][y] = false;
}

void FindPaths(char array[][5], int village[], int Home[], int villageCount, int n, int m, int SW) {
    bool visited[5][5] = {false};
    int pathCount = 0;
    int path[100]; // Adjust the size based on the maximum path length

    // Find all Kingdoms (C)
    int king = 0;
    if (SW == 2) SW = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] == 'C' && SW) {
                printf("%sAll Possible Paths for Player %d:%s\n", blue, king + 1, reset);
                king++, SW = 0;
                dfs(array, i, j, n, visited, 0, village, villageCount, &pathCount, path);
            }
            else if (array[i][j] == 'C') SW++, king++;
        }
    }

    if (pathCount == 0) {
        printf("%sNo valid paths found.%s\n", red, reset);
    }
}

int main() {
    printf("please enter the size of the map: ");
    scanf("%d %d", &n, &m);
    char array[n][m];
    AssigningValue(array, n, m);

    GenerateRandom(array, n,m);
    printFunc(array, n,m);

    int VillageCordinateArray[20], HomeArray[20];
    int villageNum = VillageCoordinate(array, VillageCordinateArray, n,m);
    int HomeNum = HomeCoordinates(array, HomeArray, n,m);
    struct player *players = (struct player *) malloc(2 * sizeof(struct player));
    if(players == NULL){
        printf("Allocation Failed!\n");
        return 0;
    }

    // Get Player 1 details
    printf("Please clarify the initial Gold, Food, Employees, and Soldiers of Player 1:\n");
    scanf("%lf %lf %d %d", &players[0].Gold, &players[0].Food, &players[0].employees, &players[0].Soldier);
    
    // Sync Player 2 with Player 1 initially
    players[1] = players[0];

    while (1) {
        // Player 1's turn
        int SW = 1, check = 0;
        while (SW) {
            if (check > 0) 
                printf("Invalid choice or insufficient resources. Try again.\n");
            
            printf("Player 1, please choose an action:\n");
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n4. Make Paths\n");
            
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
            else if(choice == 4){
                FindPaths(array, VillageCordinateArray, HomeArray, villageNum,n, m, 1);
                printf("Please enter a path coordinates to start making it: \n");
                int x, y;
                scanf("%d %d", &x, &y);
            }
            check++;
        }

        // Clear action area for Player 1
        clrscr();

        // Player 2's turn
        int SW1 = 1, check1 = 0;
        while (SW1) {
            if (check1 > 0) 
                printf("Invalid choice or insufficient resources. Try again.\n");
            
            printf("Player 2, please choose an action:\n");
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n4. Make Paths\n");
            
            int choice;
            scanf("%d", &choice);

            if (choice == 1) { // Buy Food
                if (players[1].Gold >= 1) {
                    printf("You have %.2lf Gold and can buy up to %.2lf Food. How much would you like to buy? ", players[1].Gold, players[1].Gold);
                    int amount;
                    scanf("%d", &amount);
                    if (amount <= players[1].Gold) {
                        players[1].Gold -= amount;
                        players[1].Food += amount;
                        SW1 = 0;
                    }
                }
            } else if (choice == 2) { // Hire Employees
                if (players[1].Food >= 3) {
                    printf("You have %.2lf Food and can hire up to %d Employees. How many would you like to hire? ", players[1].Food, (int)(players[1].Food / 3));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 3 <= players[1].Food) {
                        players[1].employees += amount;
                        players[1].Food -= amount * 3;
                        SW1 = 0;
                    }
                }
            } else if (choice == 3) { // Hire Soldiers
                if (players[1].Gold >= 2) {
                    printf("You have %.2lf Gold and can hire up to %d Soldiers. How many would you like to hire? ", players[1].Gold, (int)(players[1].Gold / 2));
                    int amount;
                    scanf("%d", &amount);
                    if (amount * 2 <= players[1].Gold) {
                        players[1].Soldier += amount;
                        players[1].Gold -= amount * 2;
                        SW1 = 0;
                    }
                }
            }
            else if(choice == 4){
                FindPaths(array, VillageCordinateArray, HomeArray, villageNum,n, m, 2);
                printf("Please enter a path coordinates to start making it: \n");
                int x, y;
                scanf("%d %d", &x, &y);
            }
            check1++;
        }
        // Clear action area for Player 2
        clrscr();
    }

    free(players); 
    return 0;
}
