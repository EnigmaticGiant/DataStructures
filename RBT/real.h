#include <stdio.h>

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

typedef struct REAL
    {
    double value;
    } REAL;

extern REAL *newREAL(double);
extern double getREAL(REAL *);
extern double setREAL(REAL *,double);
extern void displayREAL(void *, FILE *);
extern int compareREAL(void *,void *);
extern void freeREAL(void *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif
