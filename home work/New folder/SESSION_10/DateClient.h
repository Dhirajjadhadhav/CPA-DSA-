#ifndef _DATE_CLIENT_H
#define _DATE_CLIENT_H

#include "Date.h"

void InitDateLib(void);

int CreateDate(int iInitDay, int iInitMonth, int iInitYear);

int GetDate(int iDateId);
int GetMonth(int iDateId);
int GetYear(int iDateId);

int SetDay(int iDateId, int iNewDay);
int SetMonth(int iDateId, int iNewMonth);
int SetYear(int iDateId, int iNewYear);

int showDate(int iDateId);
int ReleaseDate(int iDateId);

void ReleaseDateLib(void);

#endif /* _DATE_CLIENT_H */
