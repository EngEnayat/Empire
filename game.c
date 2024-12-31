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

struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
};

void clrscr() {
    // Clear the player action area, but keep the map intact
    printf("\033[6;0H");  // Move cursor to the area for the player's action input (you can adjust this if needed)
    for (int i = 0; i < 5; i++) {  // Adjust this for the height of the action area
        printf("\033[K");  // Clears the current line
    }
}

void printBanner(const char* title) {
    printf("%s\n", blue);
    printf("===========================================\n");
    printf("|%s%20s%13s%s|\n", yellow, "", title, yellow);
    printf("===========================================%s\n\n", reset);
}

void GenerateRandom(char array[][5], int num) {
    srand(time(0));
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (array[i][j] == '1') {
                int randomNum = (rand() % 5) + 1;
                char ch = '0' + randomNum;
                array[i][j] = ch;
            }
        }
    }
}

void printFunc(char array[][5], int num) {
    printBanner("GRID DISPLAY");
    for (int i = 0; i < num; i++) {
        printf("                  %s|%s", yellow, reset);
        for (int j = 0; j < num; j++) {
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
        if (i != num - 1) {
            printf("                  ");
            for (int k = 0; k < (num * 6); k++) {
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

int VillageCoordinate(char array[][5], int village[], int num) {
    int curr = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (array[i][j] == 'V') {
                village[curr] = i;
                village[curr + 1] = j;
                curr += 2;
            }
        }
    }
    return curr;
}

int HomeCoordinates(char array[][5], int Home[], int num) {
    int curr = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (array[i][j] == 'X') {
                Home[curr] = i;
                Home[curr + 1] = j;
                curr += 2;
            }
        }
    }
    return curr;
}

bool isValidMove(int x, int y, int num, bool visited[][5], char array[][5]) {
    return (x >= 0 && x < num && y >= 0 && y < num && !visited[x][y] && array[x][y] != 'X');
}

void dfs(char array[][5], int x, int y, int num, bool visited[][5], int pathValue, int village[], int villageCount, int *pathCount) {
    visited[x][y] = true;

    // Check if the current cell is a village
    for (int i = 0; i < villageCount; i += 2) {
        if (x == village[i] && y == village[i + 1]) {
            printf("%sPath found to Village (%d, %d) with Hard Value: %d%s\n", yellow, x, y, pathValue, reset);
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
            dfs(array, newX, newY, num, visited, pathValue + additionalValue, village, villageCount, pathCount);
        }
    }

    // Backtrack
    visited[x][y] = false;
}

void FindPaths(char array[][5], int village[], int Home[], int num, int villageCount, int SW) {
    bool visited[5][5] = {false};
    int pathCount = 0;

    // Find all Kingdoms (C)
    int king =0;
    if(SW ==2) SW =0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (array[i][j] == 'C' && SW) {
                printf("%sAll Possible Paths for Player %d:%s\n", blue, king+1, reset);
                king++, SW =0;
                dfs(array, i, j, num, visited, 0, village, villageCount, &pathCount);
            }
            else if(array[i][j] == 'C') SW++, king++;
        }
    }

    if (pathCount == 0) {
        printf("%sNo valid paths found.%s\n", red, reset);
    }
}

int main() {
    int n = 5, m = 5;
    char array[5][5] = {
        {'C', '1', '1', 'X', 'V'},
        {'X', '1', 'X', '1', 'X'},
        {'1', '1', '1', 'V', 'X'},
        {'X', 'V', '1', 'X', 'V'},
        {'X', 'X', 'V', '1', 'C'}
    };
    GenerateRandom(array, 5);
    printFunc(array, 5);

    int VillageCordinateArray[20], HomeArray[20];
    int villageNum = VillageCoordinate(array, VillageCordinateArray, n);
    int HomeNum = HomeCoordinates(array, HomeArray, 5);
    struct player *players = (struct player *) malloc(1000 * sizeof(struct player));
    if(players == NULL){
        printf("Allocation Failed!\n");
        return 0;
    }
    printf("Please clarify the initial Gold, Food, Employees, and Soldiers of Player 1:\n");
    scanf("%lf %lf %d %d", &players[0].Gold, &players[0].Food, &players[0].employees, &players[0].Soldier);
    
    // Synchronize player 2 with player 1 initially
    players[1] = players[0];

    while (1) {
        // Player 1's turn
        int SW = 1, check = 0;
        while (SW) {
            if (check > 0) 
                printf("Invalid choice or insufficient resources. Try again.\n");
            
            printf("Player 1, please choose an action:\n");
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n4. Making paths\n");
            
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
                int playerBadge = 1;
                FindPaths(array, VillageCordinateArray, HomeArray, 5, villageNum, playerBadge);
                printf("please enter a path coordinates to start making it: \n");
                int x,y;
                scanf("%d %d", &x, &y);
            }
            check++;
        }
        clrscr();
        // Player 2's turn (similar logic)
        int SW1 = 1, check1 = 0;
        while (SW1) {
            if (check1 > 0) 
                printf("Invalid choice or insufficient resources. Try again.\n");
            
            printf("Player 2, please choose an action:\n");
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n4. Making paths\n");
            
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
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
            } else if (choice == 2) {
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
            } else if (choice == 3) {
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
                int playerBadge = 2;
                FindPaths(array, VillageCordinateArray, HomeArray, 5, villageNum, playerBadge);
                printf("please enter a path coordinates to start making it: \n");
                int x,y;
                scanf("%d %d", &x, &y);
            }
            check1++;
        }
        clrscr();
        // Display the updated properties
        printf("\n\nPlayer 1 Properties:\n");
        printf("Gold: %.2lf, Food: %.2lf, Employees: %d, Soldiers: %d\n", players[0].Gold, players[0].Food, players[0].employees, players[0].Soldier);
        printf("\nPlayer 2 Properties:\n");
        printf("Gold: %.2lf, Food: %.2lf, Employees: %d, Soldiers: %d\n\n", players[1].Gold, players[1].Food, players[1].employees, players[1].Soldier);

        // Update resources
        players[0].Food += 1;
        players[0].Gold += 1;
        players[1].Food += 1;
        players[1].Gold += 1;
    }
    free(players);
    return 0;
    }
