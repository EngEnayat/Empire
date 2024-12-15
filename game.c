#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

void FindPaths(char array[][5], int village[], int Home[], int num, int villageCount) {
    bool visited[5][5] = {false};
    int pathCount = 0;

    // Find all Kingdoms (C)
    printBanner("PATH FINDING");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (array[i][j] == 'C') {
                printf("%sStarting from Kingdom (%d, %d):%s\n", blue, i, j, reset);
                dfs(array, i, j, num, visited, 0, village, villageCount, &pathCount);
            }
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

    FindPaths(array, VillageCordinateArray, HomeArray, 5, villageNum);

    return 0;
}
