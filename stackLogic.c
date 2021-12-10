#include <stdio.h> // remove with printLogs()
#include <stdlib.h>
#include "main.h"

// Return positions X and Y for current and destination chip
static int getCurrentXPos(t_turnLogPtr pChipHistory)
{
    return (pChipHistory->m_oCurrentChip.m_iXCoord);
}
static int getCurrentYPos(t_turnLogPtr pChipHistory)
{
    return (pChipHistory->m_oCurrentChip.m_iYCoord);
}
static int getDestXPos(t_turnLogPtr pChipHistory)
{
    return (pChipHistory->m_oDestinationChip.m_iXCoord);
}
static int getDestYPos(t_turnLogPtr pChipHistory)
{
    return (pChipHistory->m_oDestinationChip.m_iYCoord);
}

// Create a new turn entry
t_turnLogPtr createNewLog(int iValueAtHand, int iDestX, int iDestY)
{
    t_turnLogPtr pNewEntry = (t_turnLogPtr)malloc(sizeof(t_turnLog));

    // Set destination chip information
    pNewEntry->m_oDestinationChip.m_iXCoord = iDestX;
    pNewEntry->m_oDestinationChip.m_iYCoord = iDestY;
    pNewEntry->m_oDestinationChip.m_iChipValue = iValueAtHand;

    pNewEntry->m_pPreviousLog = NULL;
    pNewEntry->iTurn = 0;
    return pNewEntry;
}

t_turnLogPtr initializeLogList(int iDestX, int iDestY)
{
    t_turnLogPtr pNewLog = createNewLog(iChipValues[iDestY][iDestX], iDestX, iDestY);
    // Set current chip information
    pNewLog->m_oCurrentChip.m_iXCoord = iDestX;
    pNewLog->m_oCurrentChip.m_iYCoord = iDestY;
    pNewLog->m_oCurrentChip.m_iChipValue = 0;
    return pNewLog;
}

// Add a turn to the list
void chipLog_append(int iValueAtHand, int iDestX, int iDestY, t_turnLogPtr *pChipHistory)
{
    int iCurrentX = (*pChipHistory)->m_oDestinationChip.m_iXCoord;
    int iCurrentY = (*pChipHistory)->m_oDestinationChip.m_iYCoord;
    t_turnLogPtr pNewLog = createNewLog(iValueAtHand, iDestX, iDestY);
    pNewLog->m_oCurrentChip.m_iXCoord = iCurrentX;
    pNewLog->m_oCurrentChip.m_iYCoord = iCurrentY;
    pNewLog->m_oCurrentChip.m_iChipValue = (*pChipHistory)->m_oDestinationChip.m_iChipValue;
    if (chipLog_isEmpty((*pChipHistory)))
    {
        pNewLog->iTurn = 1;
        (*pChipHistory) = pNewLog;
    }
    else
    {
        pNewLog->iTurn = ((*pChipHistory)->iTurn + 1);
        pNewLog->m_pPreviousLog = (*pChipHistory);
        (*pChipHistory) = pNewLog;
    }
}

// Check if there are any performed turns so far
int chipLog_isEmpty(t_turnLogPtr pChipHistory)
{
    if (pChipHistory == NULL)
    {
        return CHINESE_TRUE; // Return 1 for empty list
    }
    else
    {
        return CHINESE_FALSE; // Return 0 for not empty list
    }
    return -1; // Error -1
}

// Free last turn from list of turns
void freeTurn(t_turnLogPtr *pChipHistory)
{
    t_turnLogPtr temp = (*pChipHistory);
    if (!chipLog_isEmpty((*pChipHistory)->m_pPreviousLog))
    {
        (*pChipHistory) = (*pChipHistory)->m_pPreviousLog;
    }
    else
    {
        (*pChipHistory) = NULL;
    }
    free(temp);
}

void freeList(t_turnLogPtr(*pChipHistory))
{
    while (!chipLog_isEmpty((*pChipHistory)))
    {
        t_turnLogPtr temp = (*pChipHistory);
        (*pChipHistory) = (*pChipHistory)->m_pPreviousLog;
        free(temp);
    }
}