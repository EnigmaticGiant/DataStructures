#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(2028);
    //simple INTEGER test of BST
    int i;
    BST *p = newBST(compareINTEGER);
    setBSTdisplay(p,displayINTEGER);
    setBSTfree(p,freeINTEGER);
    for (i = 0; i < 18; ++i)
        {
        int j = random() % 18;
        INTEGER *a = newINTEGER(j);
        if (findBST(p,a) == 0)
            insertBST(p,a);
        else
            freeINTEGER(a);
        }
    if (sizeBST(p) < 200)
        {
        debugBST(p,0);
        printf("BST:\n");
        displayBST(p,stdout);
        debugBST(p,1);
        printf("debug (in-order): ");
        displayBST(p,stdout);
        printf("\n");
        debugBST(p,2);
        printf("debug (pre-order): ");
        displayBST(p,stdout);
        printf("\n");
        debugBST(p,3);
        printf("debug (post-order): ");
        displayBST(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeBST(p));
    for (i = 0; i < 18; ++i)
        {
        int j = random() % 18;
        INTEGER *a = newINTEGER(j);
        if (locateBST(p,a) != 0)
            {
            INTEGER *x = findBST(p,a);
            deleteBST(p,a);
            //printf("delete done\n");
            //displayBST(p, stdout);
            //printf("freeing integer\n");
            freeINTEGER(x);
            //printf("integer freed\n");
            }
            //printf("loop ened\n");
        freeINTEGER(a);
        //printf("last freeing\n");
        }
    if (sizeBST(p) < 200)
        {
        debugBST(p,0);
        printf("BST:\n");
        displayBST(p,stdout);
        debugBST(p,1);
        printf("debug (in-order): ");
        displayBST(p,stdout);
        printf("\n");
        debugBST(p,2);
        printf("debug (pre-order): ");
        displayBST(p,stdout);
        printf("\n");
        debugBST(p,3);
        printf("debug (post-order): ");
        displayBST(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeBST(p));
    statisticsBST(p,stdout);
    freeBST(p);
    return 0;
    }
