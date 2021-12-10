#ifndef __WIN32__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// cleans stdin before new input
void clean_stdin()
{
    int iBuffer;
    do
    {
        iBuffer = getchar();
    } while (iBuffer != '\n' || iBuffer != EOF);
}

// Print board and starting positions
void initLayoutPrint()
{
    system("clear");
    char caInitialPos[START_POSITION_COUNT][POSITION_COORDS];
    printf("Hello! Board is set.\n\n");
    printf("%s", LETTER_COORD_PRINT);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d. ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (iChipValues[i][j] == EMPTY_SPACE_CHINESE_VALUE)
            {
                printf("%s", EMPTY_SPACE_CHINESE_PRINTSTR);
            }
            else
            {
                if (iChipValues[i][j] == 1 || iChipValues[i][j] == 2 || iChipValues[i][j] == 10)
                {
                    printf("\033[32m%2d\033[37m|", iChipValues[i][j]);
                    // Add value to initial position array
                    switch (iChipValues[i][j])
                    {
                    case 1:
                        caInitialPos[0][0] = j + 'A';
                        caInitialPos[0][1] = i;
                        break;
                    case 2:
                        caInitialPos[1][0] = j + 'A';
                        caInitialPos[1][1] = i;
                        break;
                    case 10:
                        caInitialPos[2][0] = j + 'A';
                        caInitialPos[2][1] = i;
                        break;
                    default:
                        printf("Missing initial value.");
                        break;
                    }
                }
                else
                {
                    printf("%2d|", iChipValues[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n\n In order to be able to undo a previous move, you need to first pick a new position.");
    printf("\n\n You may begin at position:\n\n");
    printf("1. \033[32m%c%c\033[37m\n", caInitialPos[0][0], caInitialPos[0][1] + '1');
    printf("2. \033[32m%c%c\033[37m\n", caInitialPos[1][0], caInitialPos[1][1] + '1');
    printf("3. \033[32m%c%c\033[37m\n", caInitialPos[2][0], caInitialPos[2][1] + '1');
}

int CheckIfPossibleMove(int iYCoord, int iXCoord, int iPossibleMovesFound, t_turnLogPtr sMovesHistory)
{
    if (iYCoord == (sMovesHistory->m_oDestinationChip.m_iYCoord + 2) || iYCoord == (sMovesHistory->m_oDestinationChip.m_iYCoord - 2) )
    {
        if (iXCoord == (sMovesHistory->m_oDestinationChip.m_iXCoord + 1) || iXCoord == (sMovesHistory->m_oDestinationChip.m_iXCoord - 1))
        {
            saPossibleMoves[iPossibleMovesFound].m_iYCoord = iYCoord;
            saPossibleMoves[iPossibleMovesFound].m_iXCoord = iXCoord;
            saPossibleMoves[iPossibleMovesFound].m_iChipValue = iChipValues[iYCoord][iXCoord];
            return CHINESE_TRUE;
        }
    }
    else if (iYCoord == (sMovesHistory->m_oDestinationChip.m_iYCoord + 1) || iYCoord == (sMovesHistory->m_oDestinationChip.m_iYCoord - 1) )
    {
        if (iXCoord == (sMovesHistory->m_oDestinationChip.m_iXCoord + 2) || iXCoord == (sMovesHistory->m_oDestinationChip.m_iXCoord - 2))
        {
            saPossibleMoves[iPossibleMovesFound].m_iYCoord = iYCoord;
            saPossibleMoves[iPossibleMovesFound].m_iXCoord = iXCoord;
            saPossibleMoves[iPossibleMovesFound].m_iChipValue = iChipValues[iYCoord][iXCoord];
            return CHINESE_TRUE;
        }
    }
    return CHINESE_FALSE;
}

// Prints game with possible moves
void updatedLayout(int iHandChipValue, t_turnLogPtr sMovesHistory)
{
    system("clear");
    printf("%s", LETTER_COORD_PRINT);
    int iFoundMoves = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d. ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (iChipValues[i][j] == EMPTY_SPACE_CHINESE_VALUE)
            {
                printf("%s", EMPTY_SPACE_CHINESE_PRINTSTR);
            }
            else 
            {
                if ((j == (sMovesHistory->m_oDestinationChip.m_iXCoord)) && (i == (sMovesHistory->m_oDestinationChip.m_iYCoord))) //sets the begin position in green, double digits
                {
                    printf("\033[32m%2d\033[37m|", iChipValues[i][j]);
                }
                else if (CheckIfPossibleMove(i, j, iFoundMoves, sMovesHistory) > 0) //sets the possible moves in yellow, double digits
                {
                    printf("\033[33m%2d\033[37m|", iChipValues[i][j]);
                    iFoundMoves++;
                }
                else
                {
                    printf("%2d|", iChipValues[i][j]);
                }
            }
        }
        printf("\n");
    }
    for (iFoundMoves; iFoundMoves < MAX_REACHABLE_CHIPS_PER_TURN; iFoundMoves++)
    {
        saPossibleMoves[iFoundMoves].m_iYCoord = -1;
        saPossibleMoves[iFoundMoves].m_iXCoord = -1;
        saPossibleMoves[iFoundMoves].m_iChipValue = -1;
    }
    printf("You have in your hand chip %d\n", iHandChipValue);
    printf("\nPossible moves are: \n");
    for (int i = 0; i < MAX_REACHABLE_CHIPS_PER_TURN; i++)
    {
        if (saPossibleMoves[i].m_iXCoord != -1)
        {
            int yValue = saPossibleMoves[i].m_iYCoord;
            int xValue = saPossibleMoves[i].m_iXCoord;
            printf("%d. \033[33m%c%d\033[37m, which is %d\n", i + 1, xValue + 'A', yValue + 1, iChipValues[yValue][xValue]);
        }
        else {
            i = MAX_REACHABLE_CHIPS_PER_TURN;
        }
    }
    printf("9. Undo previous movement\n");
}

void winScreen()
{
    system("clear");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("%d. ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (iChipValues[i][j] == EMPTY_SPACE_CHINESE_VALUE)
            {
                printf("%s", EMPTY_SPACE_CHINESE_PRINTSTR);
            }
            else 
            {
                printf("%2d|", iChipValues[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n\n");
    printf("\t\t\tCONGRATZ, YOU WIN!!!!!!");
    printf("\n\nPress enter to close.");
    clean_stdin();
    getc(stdin);
}