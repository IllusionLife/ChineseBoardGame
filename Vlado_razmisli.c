#include <stdio.h>
#define M 7

struct Boardchips
{
    int iPositionX;
    int iPositionY;
    int iValue;
} Chips[7][7], Beginchip, Currentchip;

void printBoard(int (*Chip)[M]);
enum Columns
{
    A,
    B,
    C,
    D,
    E,
    F,
    G
};
void Func1(struct Boardchips (**Chip));

int main()
{
    int ChipValues[][7] = {-1, -1, 16, -1, -1, -1, -1,
                     -1, -1, 11, 3, 13, -1, -1,
                     -1, 22, 6, 7, 8, 9, 21,
                     -1, 19, 12, 4, 14, 15, 0,
                     5, 17, 18, 2, 20, 1, -1,
                     -1, -1, 10, 23, 24, -1, -1,
                     -1, -1, -1, -1, -1, -1, -1};

    printBoard(ChipValues);

    for (int i = 0; i < M; i++)
    {          
        for (int j = 0; j < M; j++)
        {            
            Chips[i][j].iPositionX = i;
            Chips[i][j].iPositionY = j;
            Chips[i][j].iValue = ChipValues[i][j];                         
        }            
    }
   
    int i = Beginchip.iPositionX =  4;
    int j = Beginchip.iPositionY = F;
    Beginchip.iValue = 1;    

    printf("beginchip is %d \n", Beginchip.iValue); 
    printf("up-up-right is %d \n", Chips[i-2][j+1].iValue); // [i-2][j+1]
    printf("up-up-left is %d \n", Chips[i-2][j-1].iValue);  // [i-2][j-1]
    printf("up-left-left is %d \n", Chips[i-1][j-2].iValue); // [i-1][j-2]
    printf("down-left-left is %d \n", Chips[i+1][j-2].iValue); // [i+1][j-2]
// j= "F" = 5, ([i-1]/[i-1]) .PositionY [j+2] > 6 undefined, also for < 0
// Chips[6][E].iValue < 0, undefined

// " \033[32m for green, \033[37m for white    

    return 0;
}

void printBoard(int (*Chip)[M])
{

    printf("Grid:\n\n");
    printf("    A| B| C| D| E| F| G\n");
    for (int i = 0; i < M; i++)
    {
        printf("%d. ", i + 1);
        for (int j = 0; j < M; j++)
        {
            if (Chip[i][j] < 0)
            {
                printf("_ |");
            }
            else if (Chip[i][j] < 10)
            {
                printf(" %d|", Chip[i][j]);
            }
            else
            {
                printf("%d|", Chip[i][j]);
            }
        }
        printf("\n");
    }
}

///print from Array of structs?

