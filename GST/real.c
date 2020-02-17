#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "real.h"

//extern void Fatal(char *,...);

REAL *
newREAL(double x)
    {
    REAL *p = malloc(sizeof(REAL));
    assert(p != 0);
    p->value = x;
    return p;
    }

double 
getREAL(REAL *v)
    {
    return v->value;
    }

double 
setREAL(REAL *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayREAL(void *v, FILE *fp)
    {
    fprintf(fp,"%f",getREAL((REAL *) v));
    }

int
compareREAL(void *v,void *w){
    double result = ((REAL *) v)->value - ((REAL *) w)->value;
    if(result > 0) return 1;
    else if(result == 0) return 0;
    else return -1;
}

void
freeREAL(void *v)
    {
    free(v);
    }
