#include <stdio.h>
#include <string.h>
#include "comparator.h"
#include "integer.h"
//#include "real.h"

int intComparator(void *x, void *y){
	return getINTEGER(x) - getINTEGER(y);
	
}

int realComparator(void *x, void *y){
	double result = ((real *) x)->value - ((real *) y)->value;
	if(result > 0) return 1;
	else if(result == 0) return 0;
	else return -1;
}


int stringComparator(void *x, void *y){
	return strcmp(x, y);
}