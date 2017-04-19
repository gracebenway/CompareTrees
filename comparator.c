//
//  comparator.c
//  
//
//  Created by Grace Benway on 3/8/17.
//
//

#include <stdio.h>
#include <limits.h>
#include <assert.h> 
#include <string.h> 
#include "comparator.h"
#include "str.h"
#include "integer.h"
#include "real.h"

//returns >0 if p is > q, returns 0 if equal, returns <0 is q is > p
int intComparator(void *p, void *q)
{
    return ((integer *) p)->value - ((integer *) q)->value;
}

////returns >0 if p is > q, returns 0 if equal, returns <0 is q is > p
int realComparator(void *p,void *q)
{
    int a = ((real *) p)->value - ((real *) q)->value;
    if (a > 0)
        return 1;
    else if (a == 0)
        return 0;
    else
        return -1;
}

int stringComparator(void *p,void *q)
{
    int r = strcmp((char *)p, (char *)q);
    return r;
}


