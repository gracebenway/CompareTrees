#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "string.h"


extern void Fatal(char *,...);


char *
getString(char *v)
{
    assert(v!=0);
    return v;
}

void
displayString(FILE *fp,void *v)
{
    assert(v!=0);
    fprintf(fp,"\"%s\"",(char *) v);
}

void
freeString(char *v)
{
    free(v);
}
