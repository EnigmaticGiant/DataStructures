#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "cda.h"
#include "queue.h"

void srandom(unsigned int);
long int random(void);

static void
display(QUEUE *p,char *intro)
    {
    printf("%s",intro);
    if (sizeQUEUE(p) < 200)
        {
        displayQUEUE(p,stdout);
        }
    else
        {
        printf("(displaying top element)\n");
        displayINTEGER(peekQUEUE(p),stdout);
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(2015);
    int i,r,rounds=2,size=174;
    printf("INTEGER test of QUEUE, insertions at the front\n");
    QUEUE *p = newQUEUE();
    setQUEUEdisplay(p,displayINTEGER);
    setQUEUEfree(p,freeINTEGER);
    debugQUEUE(p,1);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            enqueue(p,newINTEGER(j));
            }
        display(p,"items: ");
        printf("size is %d\n",sizeQUEUE(p));
        }
    freeQUEUE(p);
    return 0;
    }
