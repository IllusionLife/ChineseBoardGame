#ifndef CHIP_STACK_HEADER
#define CHIP_STACK_HEADER

// Struct, keeping information on chip position and value 
struct SChipPosition {
    int m_iXCoord;
    int m_iYCoord;
    int m_iChipValue;
};

typedef struct SChipPosition t_position;
typedef t_position* t_positionPtr;

// List of structs, each containing current and destination chips + turn counter
struct SChipTurn
{
    t_position m_oCurrentChip;
    t_position m_oDestinationChip;
    int iTurn;
    struct SChipTurn *m_pPreviousLog;
};

typedef struct SChipTurn t_turnLog;
typedef t_turnLog* t_turnLogPtr;

t_turnLogPtr initializeLogList(int iDestX, int iDestY);
t_turnLogPtr createNewLog(int iValueAtHand, int iDestX, int iDestY);
t_turnLogPtr chipLog_viewTop(t_turnLogPtr chipHistory);

int chipLog_isEmpty(t_turnLogPtr chipHistory); // Check if there are any performed turns so far

void chipLog_append(int iValueAtHand, int iDestX, int iDestY, t_turnLogPtr *pChipHistory); // Add a turn to the list

void freeTurn(t_turnLogPtr (*pChipHistory));
void freeList(t_turnLogPtr (*pChipHistory));

#endif