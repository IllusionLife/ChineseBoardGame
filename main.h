#ifndef HEADER_FILE_LIST
#define HEADER_FILE_LIST

#include "stackLogic.h"
#include "gameLogic.h"
#include "printFile.h"

#define EMPTY_SPACE_CHINESE_VALUE -1
#define CHINESE_FALSE 0
#define CHINESE_TRUE 1
#define BOARD_SIZE 7
#define MAX_REACHABLE_CHIPS_PER_TURN 8 //includes undo movement

extern int iChipValues[BOARD_SIZE][BOARD_SIZE];

#endif