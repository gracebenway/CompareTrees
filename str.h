#include <stdio.h>

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

extern char * getString(char *);
extern void displayString(FILE *,void *);
extern void freeString(char *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif
