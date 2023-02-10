#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Date.h"
#include "DateVector.h"

struct DateVector* pHandleTable = NULL;

struct DateVector* CreateDateVector(void)
{
    struct DateVector* pDateVector = NULL;

    pDateVector = (struct DateVector*)malloc(sizeof(struct DateVector));
    assert(pDateVector);

    pDateVector->pDateTable = NULL;
    pDateVector->iSize = 0;

    return (pDateVector);
}

int PushBack(struct DateVector* pDateVector, struct Date* pDate)
{
    pDateVector->iSize += 1;
    pDateVector->pDateTable = (struct Date**)realloc(
                                                    pDateVector->pDateTable, 
                                                    pDateVector->iSize * 
                                                    sizeof(struct Date)
                                                );
    assert(pDateVector->pDateTable);
    pDateVector->pDateTable[pDateVector->iSize-1] = pDate;
    return (SUCCESS);
}

int DestroyDateVector(struct DateVector* pDateVector)
{
    int i;
    for(int i = 0; i<pDateVector->iSize; ++i)
        if(pDateVector->pDateTable[i])
            free(pDateVector->pDateTable[i]);
    free(pDateVector->pDateTable);
    free(pDateVector);
    pDateVector = NULL; 

    return (SUCCESS);   
}

void InitDateLib(void)
{
    pHandleTable = CreateDateVector();
}

int CreateDate(int iIntiDay, int iInitMonth, int iInitYear)
{
    struct Date* pNewDate = NULL;
    int i;
    BOOL bFreeHandle = FALSE;
    int iNewHandle;

    pNewDate = (struct Date*)malloc(sizeof(struct Date));
    assert(pNewDate);

    pNewDate->iDate = iIntiDay;
    pNewDate->iMonth = iInitMonth;
    pNewDate->iYear = iInitYear;

    for(i = 0; i<pHandleTable->iSize; ++i)
    {
        if(pHandleTable->pDateTable[i] == NULL)
        {
            bFreeHandle = TRUE;
            break;
        }
        bFreeHandle = FALSE;
    }
    if(bFreeHandle == FALSE)
    {
        PushBack(pHandleTable, pNewDate);
        iNewHandle = pHandleTable->iSize-1;
    }
    return (iNewHandle);
}

int GetDay(int iDateId)
{
    if(
        iDateId<0 || 
        iDateId>=pHandleTable->iSize || 
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
    return (pHandleTable->pDateTable[iDateId]->iDate);
}

int GetMonth(int iDateId)
{
    if(
        iDateId<0 ||
        iDateId>=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
    
    return (pHandleTable->pDateTable[iDateId]->iMonth);
}

int GetYear(int iDateId)
{
    if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
    
    return (pHandleTable->pDateTable[iDateId]->iYear);
}

int SetDay(int iDateId, int iNewDay)
{
    if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
     pHandleTable->pDateTable[iDateId]->iDate = iNewDay;
     return (SUCCESS);
}
int SetMonth(int iDateId, int iNewMonth)
{
    if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
    
    pHandleTable->pDateTable[iDateId]->iMonth = iNewMonth;
    return(SUCCESS);
}

int SetYear(int iDateId, int iNewYear)
{
    if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);

    pHandleTable->pDateTable[iDateId]->iYear = iNewYear;
    return (SUCCESS);
}

int showDate(int iDateId)
{
     if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);
    
    printf("%d-%d-%d\n", pHandleTable->pDateTable[iDateId]->iDate, 
                        pHandleTable->pDateTable[iDateId]->iMonth,
                        pHandleTable->pDateTable[iDateId]->iYear
        );

    return (SUCCESS);
}

int ReleaseDate(int iDateId)
{
      if(
        iDateId<0 || 
        iDateId <=pHandleTable->iSize ||
        pHandleTable->pDateTable[iDateId] == NULL
    )
        return (E_INVALID_HANDLE);

    free(pHandleTable->pDateTable[iDateId]);
    pHandleTable->pDateTable[iDateId]  = NULL;
    return (SUCCESS);
}

void ReleaseDateLib(void)
{
    DestroyDateVector(pHandleTable);
}
