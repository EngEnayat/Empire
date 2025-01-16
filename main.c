#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

int row, col;
int sx,sy,fx,fy;
// village x just store the S_Village_flage and also when a path found the village's coordinates will change
int F_Village_flage[40],village_num, S_Village_flage[40];

int HardValue[100]={}, path=0;


int main() {
    printf("Please enter the map's coordinates (x, y): ");
    scanf("%d %d", &row, &col);
    if(row >17 || col >17){
        printf("%sMaximum 17x17!!%s\n%sPROGRAM END!%s\n", red,reset,red,reset);
        exit(0);
    }
    // Allocate memory for the 2D array
    char **array = (char **)malloc(row * sizeof(char *));
    for (int i = 0; i < row; i++) {
        array[i] = (char *)malloc(col * sizeof(char));
    }
    if(array == NULL){
        printf("Allocation failed!");
        exit(0);
    }
    // Allocating memory for players
    struct player *players = (struct player *) malloc(2 * sizeof(struct player));
    if(players == NULL){
        printf("Failed Allocating memory!");
        exit(0);
    }

    // Call the functions
    AssigningValue(array);
    GenerateRandom(array, col);
    printFunc(array);
    int HomeCoordinateArray[50],HomeAmount=0;
    int VillageCoordinateArray[50], VillageAmount=0;
    XVcoordinates(array, HomeCoordinateArray,VillageCoordinateArray,&HomeAmount,&VillageAmount);
    info(players);

    // the players play by turn
    Game_init(players, array, VillageCoordinateArray, village_num);

    // Free allocated memory
    for (int i = 0; i < row; i++) {
        free(array[i]);
    }
    return 0;
}