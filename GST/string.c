#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "string.h"

//extern void Fatal(char *,...);

STRING *
newSTRING(char* x)
    {
    STRING *p = malloc(sizeof(STRING));
    assert(p != 0);
    p->value = x;
    return p;
    }

char* getSTRING(STRING *v){
    return v->value;
}

char* setSTRING(STRING *v,char *x){
    char *old = v->value;
    v->value = x;
    return old;
}

void 
displaySTRING(void *v, FILE *fp)
    {
    fprintf(fp,"%s",getSTRING((STRING *) v));
    }

int compareSTRING(void *x,void *y){
    return strcmp(getSTRING(x), getSTRING(y));
}

void freeSTRING(void *v){
    free(v);
}