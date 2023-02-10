#ifndef _DATE_H
#define _DATE_H

#define TRUE    1
#define FALSE   0

#define SUCCESS             1
#define E_INVALID_HANDLE    -1
#define E_INVALID_VAULE      -2

typedef int BOOL;

struct Date
{
    int iDate;
    int iMonth;
    int iYear;
};

void InitDateLib(void);

int CreateDate(int iIntiDay, int iInitMonth, int iInitYear);

int GetDay(int iDateId);
int GetMonth(int iDateId);
int GetYear(int iDateId);

int SetDay(int iDateId, int iNewDay);
int SetMonth(int iDateId, int iNewMonth);
int SetYear(int iDateId, int iNewYear);

int showDate(int iDateId);
int ReleaseDate(int iDateId);

void ReleaseDateLib(void);

#endif  /* _DATE_H */

