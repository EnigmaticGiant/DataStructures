#include <stdio.h>

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

typedef struct STRING
    {
    char *value;
    } STRING;

extern STRING *newSTRING(char *);
extern char *getSTRING(STRING *);
extern char *setSTRING(STRING *,char *);
extern void displaySTRING(void *, FILE *);
extern int compareSTRING(void *,void *);
extern void freeSTRING(void *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif