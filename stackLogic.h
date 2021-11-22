#ifndef CHIP_STACK_HEADER
#define CHIP_STACK_HEADER

struct SChipPosition {
    int iXCoord;
    int iYCoord;
    int iChipValue;
};

typedef SChipPosition t_position;

struct SChipTurn
{
    t_position SCurrentChip;
    t_position SDestinationChip;
    int iTurn;
};

#endif
