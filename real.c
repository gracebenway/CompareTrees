#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "real.h"

extern void Fatal(char *,...);

real *
newReal(double x)
{
    real *p = malloc(sizeof(real));
    if (p == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(-1);
    }
    p->value = x;
    return p;
}

double
getReal(real *v)
{
    assert(v!=0);
    return v->value;
}


void
displayReal(FILE *fp,void *v)
{
    assert(v!=0);
    fprintf(fp,"%f",getReal((real *) v));
}

void
freeReal(real *v)
{
    free(v);
}
