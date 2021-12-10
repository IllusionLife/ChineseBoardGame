#ifndef CHINESE_GAME_LOGIC
#define CHINESE_GAME_LOGIC

#define DIRECTION_BACK -1
#define DIRECTION_FORWARD 1
#define REVERSE_MOVEMENT 8

enum INITIAL_VALUE {
    SELECTION_FIRST = 1,
    SELECTION_SECOND,
    SELECTION_LAST = 10
};

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

extern t_position saPossibleMoves[8];

void StartGame();

#endif