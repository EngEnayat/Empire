#include <stdio.h>

typedef struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
} player;

int main() {
    player players[2] = {{0, 0, 0, 0}, {1, 1, 1, 1}};
    
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
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n");
            
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
            check++;
        }

        // Player 2's turn (similar logic)
        int SW1 = 1, check1 = 0;
        while (SW1) {
            if (check1 > 0) 
                printf("Invalid choice or insufficient resources. Try again.\n");
            
            printf("Player 2, please choose an action:\n");
            printf("1. Buy Food\n2. Hire Employees\n3. Hire Soldiers\n");
            
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
            check1++;
        }

        // Display the updated properties
        printf("\n\nPlayer 1 Properties:\n");
        printf("Gold: %.2lf, Food: %.2lf, Employees: %d, Soldiers: %d\n", players[0].Gold, players[0].Food, players[0].employees, players[0].Soldier);
        
        printf("\nPlayer 2 Properties:\n");
        printf("Gold: %.2lf, Food: %.2lf, Employees: %d, Soldiers: %d\n", players[1].Gold, players[1].Food, players[1].employees, players[1].Soldier);

        // Update resources
        players[0].Food += 1;
        players[0].Gold += 1;
        players[1].Food += 1;
        players[1].Gold += 1;
    }
    return 0;
}
