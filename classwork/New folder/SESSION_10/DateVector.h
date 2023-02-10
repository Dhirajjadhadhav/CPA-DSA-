#ifndef _DATE_VECTOR_H
#define _DATE_VECTOR_H

#include "Date.h"

#ifndef SUCCESS    
#define SUCCESS 1
#endif

struct DateVector
{
    struct Date**  pDateTable;
    int iSize;
};

struct DateVector* CreateDateVector(void);
int PushBack(struct DateVector* pDateVector, struct Date* pDate);
int DestroyDateVector(struct DateVector* pDateVector);

#endif /* _DATE_VECTOR_H */