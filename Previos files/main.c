#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

int row, col;

int main() {
    printf("Please enter the map's coordinates (x, y): ");
    scanf("%d %d", &row, &col);

    // Allocate memory for the 2D array
    char **array = (char **)malloc(row * sizeof(char *));
    for (int i = 0; i < row; i++) {
        array[i] = (char *)malloc(col * sizeof(char));
    }

    // Allocating memory for players
    struct player *players = (struct player *) malloc(2 * sizeof(struct player));
    if(players == NULL){
        printf("Failed Allocating memory!");
        exit(0);
    }

    // Call the functions
    AssigningValue(array);
    GenerateRandom(array);
    printFunc(array);
    info(players);

    // the players play by turn
    Game_init(players, array);

    // Free allocated memory
    for (int i = 0; i < row; i++) {
        free(array[i]);
    }
    return 0;
}