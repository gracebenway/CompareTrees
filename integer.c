#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "integer.h"

extern void Fatal(char *,...);

integer *
newInteger(int x)
{
    integer *p = malloc(sizeof(integer));
    if (p == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(-1);
    }
    p->value = x;
    return p;
}

int
getInteger(integer *v)
{
    assert(v!=0);
    return v->value;
}

void
displayInteger(FILE *fp,void *v)
{
    assert(v!=0);
    fprintf(fp,"%d",getInteger((integer *) v));
}

void
freeInteger(integer *v)
{
    free(v);
}
