#include <stdio.h>
#include <stdlib.h>
#include "main.h"

static int iChipInHand = 0;
static int *iaPieces = NULL;
static t_turnLogPtr sMovesHistory = NULL;

t_position saPossibleMoves[8] = {0};


// finds X value of given value/chip
int findElementCoordCol(int iValue)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (iaPieces[(col * BOARD_SIZE) + row] == iValue)
            {
                return col;
            }
        }
    }
    return -1;
}

// finds Y value of given value/chip
int findElementCoordRow(int iValue)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (iaPieces[(col * BOARD_SIZE) + row] == iValue)
            {
                return row;
            }
            
        }
        
    }
    return -1;
}

// Checks if game is won, skipping EMPTY_SPACE_CHINESE_VALUE(-1) values
int CheckifFinished()
{
    int iCounter = 0;
    for (int iCol = 0; iCol < BOARD_SIZE; iCol++)
    {
        for (int iRow = 0; iRow < BOARD_SIZE; iRow++)
        {
            if (iaPieces[(iCol * BOARD_SIZE) + iRow] != EMPTY_SPACE_CHINESE_VALUE)
            {
                if (iaPieces[(iCol * BOARD_SIZE) + iRow] != ++iCounter)
                {
                    return CHINESE_FALSE;
                }
            }
        }
    }
    return CHINESE_TRUE;
}

// Swaps 2 values on the board
void SwapChips(int iDirection)
{
    // Get the X & Y coord of the the element, that is getting swapped
    int xCoordNext = sMovesHistory->m_oDestinationChip.m_iXCoord;
    int yCoordNext = sMovesHistory->m_oDestinationChip.m_iYCoord;

    // Check if we are reversing or making a new move
    if (iDirection == DIRECTION_FORWARD)
    {
        // Update values/chips to new state using the current stack
        iaPieces[(yCoordNext * BOARD_SIZE) + xCoordNext] = sMovesHistory->m_oCurrentChip.m_iChipValue;
    }
    else if (iDirection == DIRECTION_BACK)
    {
        // Get the X & Y coord of the the element, that is getting swapped
        int xCoordPrev = sMovesHistory->m_oCurrentChip.m_iXCoord;
        int yCoordPrev = sMovesHistory->m_oCurrentChip.m_iYCoord;
        // Update values/chips to previous state using the current stack
        iaPieces[(yCoordNext * BOARD_SIZE) + xCoordNext] = sMovesHistory->m_oDestinationChip.m_iChipValue;
    }
}

// Calls function on each turn || Processing movement
void UpdateGame()
{
    int iChipSelection = 0;

    // Choosing a possible cell to move until valid choice is provided
    do
    {
        updatedLayout(iChipInHand, sMovesHistory);
        printf("Enter your choice:\t");
        scanf("%d", &iChipSelection);

        // Adjust selection to array access value
        iChipSelection--;

        if ((saPossibleMoves[iChipSelection].m_iChipValue == EMPTY_SPACE_CHINESE_VALUE) || iChipSelection > MAX_REACHABLE_CHIPS_PER_TURN)
        {
            printf("\nInvalid option.\n");
        }

    } while ((saPossibleMoves[iChipSelection].m_iChipValue == EMPTY_SPACE_CHINESE_VALUE) || iChipSelection > MAX_REACHABLE_CHIPS_PER_TURN);
    
    if (iChipSelection != REVERSE_MOVEMENT) // For selected movement
    {
        iChipInHand = saPossibleMoves[iChipSelection].m_iChipValue;
        chipLog_append(iChipInHand, saPossibleMoves[iChipSelection].m_iXCoord, saPossibleMoves[iChipSelection].m_iYCoord, &sMovesHistory);
        SwapChips(DIRECTION_FORWARD);
    } 
    else // For previous movement
    {                   
        SwapChips(DIRECTION_BACK);
        freeTurn(&sMovesHistory);
        
        if (!chipLog_isEmpty(sMovesHistory)) 
        {
            if (!chipLog_isEmpty(sMovesHistory->m_pPreviousLog))
            {
                iChipInHand = sMovesHistory->m_oDestinationChip.m_iChipValue;
                if (iChipInHand == 0)
                {
                    SwapChips(DIRECTION_BACK);
                    freeTurn(&sMovesHistory);
                    iChipInHand = sMovesHistory->m_oDestinationChip.m_iChipValue;
                }
            }
            else
            {
                SwapChips(DIRECTION_BACK);
                freeTurn(&sMovesHistory);
                iChipInHand = 0;
            }
        }
        else
        {
            iChipInHand = 0;
        }
    }
}

// Initialise game and handling cases where chip in hand is 0
void StartGame(int *iaChipValuesArg)
{
    iaPieces = iaChipValuesArg;
    do
    {
        initLayoutPrint();
        printf("Enter your choice:\t");
        scanf("%d", &iChipInHand);
        iChipInHand = (iChipInHand == 10) ? 0 : iChipInHand;
        iChipInHand = (iChipInHand == 3) ? SELECTION_LAST : iChipInHand;
        if (((iChipInHand != SELECTION_FIRST) && (iChipInHand != SELECTION_SECOND) && (iChipInHand != SELECTION_LAST)))
        {
            printf("\nInvalid option.\n");
        }
    } while ((iChipInHand != SELECTION_FIRST) && (iChipInHand != SELECTION_SECOND) && (iChipInHand != SELECTION_LAST));

    if (sMovesHistory == NULL)
    {
        sMovesHistory = initializeLogList(findElementCoordRow(iChipInHand), findElementCoordCol(iChipInHand));
    }
    else
    {
        chipLog_append(iChipInHand, findElementCoordRow(iChipInHand), findElementCoordCol(iChipInHand), &sMovesHistory);
    }

    SwapChips(DIRECTION_FORWARD);

    while(!CheckifFinished())
    {
        if (iChipInHand == 0)
        {
            StartGame(iaPieces);
        }
        UpdateGame();
    }

    if (!chipLog_isEmpty(sMovesHistory))
    {
        freeList(&sMovesHistory);
    }
}