#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "da.h"
#include "stack.h"

void srandom(unsigned int);
long int random(void);

static void
display(STACK *p,char *intro)
    {
    printf("%s",intro);
    if (sizeSTACK(p) < 200)
        {
        displaySTACK(p,stdout);
        }
    else
        {
        printf("(displaying top element)\n");
        displayINTEGER(peekSTACK(p),stdout);
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(2013);
    printf("REAL test of STACK, simple\n");
    int i;
    STACK *p = newSTACK();
    setSTACKdisplay(p,displayREAL);
    setSTACKfree(p,freeREAL);
    display(p,"items: ");
    for (i = 0; i < 3; ++i)
        {
        push(p,newREAL(3.3));
        push(p,newREAL(2.2));
        push(p,newREAL(4.4));
        push(p,newREAL(1.1));
        debugSTACK(p,i);
        display(p,"items: ");
        }
    debugSTACK(p,0);
    freeREAL(pop(p));
    display(p,"items: ");
    freeREAL(pop(p));
    display(p,"items: ");
    freeREAL(pop(p));
    display(p,"items: ");
    freeREAL(pop(p));
    display(p,"items: ");
    printf("size: %d\n",sizeSTACK(p));
    freeSTACK(p);
    return 0;
    }
