#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H
extern int row, col;
extern int **hardValues;
struct player {
    double Gold;
    double Food;
    int employees;
    int Soldier;
};

#define print_map printFunc(array);
#define screen_clear  clrscr();
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

void AssigningValue(char **map);
void GenerateRandom(char **array);
void XVcoordinates(char **array, int *HomecoordinateArray,int *VillagecoordinateArray,int *HomeAmount,int *VillageAmount);
void printVillage(int *array, int n);
bool isValidMove(int x, int y, bool **visited, char **array, char player, int village[], bool *villageVisited, int villageCount);
void dfs(char **array, int x, int y, bool **visited, int village[], int villageCount, bool *pathFound, char player, bool *villageVisited, int *pathHardValue, int **path, int *pathLength, int **shortestPath, int *shortestPathLength, int *shortestPathHardValue);
void FindPaths(char **array, int village[], int villageNum, char player);
void ExploreKingdom(char **array);
void printFunc(char **array);
void printBanner(const char* title);

void clrscr();
void info(struct player* func_Players);
void Game_init(struct player* players, char **array);
void print_property(struct player* players);
void add_resourse(struct player *players);


#endif // PROJECT_HEADER_H
