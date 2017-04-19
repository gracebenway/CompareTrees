#include <stdio.h>

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

typedef struct real
{
    double value;
} real;

extern real *newReal(double);
extern double getReal(real *);
extern void displayReal(FILE *,void *);
extern void freeReal(real *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif
