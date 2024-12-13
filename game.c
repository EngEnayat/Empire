#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define blue "\033[1;34m"
#define brightBlue "\033[0;34m"
#define Green "\033[1;32m"
#define brightGreen "\033[0m"
#define white "\033[1;10m"
#define brightRed "\033[0m"
#define red "\033[1;31m"
#define yellow "\033[1;33m"
#define purple "\033[1;35m"

void GenerateRandom(char array[][5], int num){
    srand(time(0));

    for(int i=0; i<num;i++){
        for(int j=0; j<num;j++){
            if(array[i][j] == '1'){

                int randomNum = (rand() % 5) +1;
                char ch = '0'+ randomNum;
                array[i][j] = ch;
            }
        }
    }
}
void printFunc(char array[][5], int num){
    for (int i = 0; i < num; i++) {
        printf("                                      ");
            for (int j = 0; j < num; j++) {
                if (array[i][j] == 'X') {
                    // Print 'x' in green
                    printf(Green"%c    "brightGreen,array[i][j]); // 1;32 -> Bright Green
                }
                else if(array[i][j] == 'C'){
                        printf(purple"%c    "yellow,array[i][j]);
                    }
                else if(array[i][j]=='V'){
                        printf(blue"%c    ",array[i][j]);
                    }
                else{
                    // Print '1' in red
                    printf(red"%c    ",array[i][j]);
                } 
            }
            printf("\n\n"); // Move to the next row
        }    
    };
void PrintPaths(char array[][5], int num){
    for(int i=0; i<num;i++){
        for(int j=0; j<num;j++){
            
        }
    }
};
int main()
{
    int n=5, m=5;
    char array[5][5]={
        {'C', '1', '1', 'X', 'V'},
        {'X', '1', 'X', '1', 'X'},
        {'1', '1', '1', 'V', 'X'},
        {'X', 'V', '1', 'X', 'V'},
        {'X', 'X', 'V', '1', 'C'}
    };
    GenerateRandom(array, 5);
    printFunc(array, 5);
    PrintPaths(array, 5); // print the possible ways in through the villages

    int temp[20], curr=0; // temporary array will store the x and y cordinates that has V value
    for(int i=0; i<5;i++){
        for(int j=0; j<5;j++){
            if(array[i][j] == 'V'){
                temp[curr] = i;
                temp[curr+1] = j;
                curr+=2;
            }
        }
    }
    printf("\n");
    for(int i=0; i<curr;i+=2){
        printf("x-axis:%d  y-axis:%d\n", temp[i], temp[i+1]);
    }
}
