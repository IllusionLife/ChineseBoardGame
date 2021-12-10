#ifndef PRINT_CHINESE_GAME
#define PRINT_CHINESE_GAME

#define LETTER_COORD_PRINT "    A| B| C| D| E| F| G\n"
#define EMPTY_SPACE_CHINESE_PRINTSTR "_ |"
#define START_POSITION_COUNT 3
#define POSITION_COORDS 2

void clean_stdin();
void initLayoutPrint();
void updatedLayout(int iHandChipValue, t_turnLogPtr sMovesHistory);
void winScreen();

#endif