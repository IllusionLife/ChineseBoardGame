#include "main.h"
int iChipValues[BOARD_SIZE][BOARD_SIZE] = {
    -1, -1, 16, -1, -1, -1, -1,
    -1, -1, 11, 3, 13, -1, -1,
    -1, 22, 6, 7, 8, 9, 21,
    -1, 19, 12, 4, 14, 15, -1,
    5, 17, 18, 2, 20, 1, -1,
    -1, -1, 10, 23, 24, -1, -1,
    -1, -1, -1, -1, -1, -1, -1
};

// // Testing almost ready case

// int iChipValues[BOARD_SIZE][BOARD_SIZE] = {
//     -1, -1, 4, -1, -1, -1, -1,
//     -1, -1, 2, 3, 1, -1, -1,
//     -1, 5, 6, 7, 8, 9, 10,
//     -1, 11, 12, 13, 14, 15, -1,
//     16, 17, 18, 19, 20, 21, -1,
//     -1, -1, 22, 23, 24, -1, -1,
//     -1, -1, -1, -1, -1, -1, -1
// };

int main(int argc, char** argv) {
    StartGame(iChipValues[0]);
    winScreen();
    return 0;
}