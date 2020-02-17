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
    srandom(18);
    //simple INTEGER test of BST
    int i;
    BST *p = newBST(compareINTEGER);
    setBSTdisplay(p,displayINTEGER);
    setBSTfree(p,freeINTEGER);
    for (i = 0; i < 198; ++i)
        {
        int j = random() % 198;
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
    for (i = 0; i < 198; ++i)
        {
        int j = random() % 198;
        //printf("deletion nummber %d\n", i);
        INTEGER *a = newINTEGER(j);
        //int g = getINTEGER(a);
        /*if(i == 63){
            printf("deleting the integer ");
            displayINTEGER(a, stdout);
            printf("\n");
            debugBST(p, 0);
            displayBST(p, stdout);
            exit(-1);
        }*/
        if (locateBST(p,a) != 0)
            {
            //printf("attempting to find ");
            //displayINTEGER(a, stdout);
            //printf("\n");
            INTEGER *x = findBST(p,a);

            // ISSUE MAY BE IN MY FINDBST
            //printf("deleting the integer ");
            //displayINTEGER(a, stdout);
            //printf("\n");
            deleteBST(p,a);
            freeINTEGER(x);
            }
            else{
                //printf("couldn't find the item to delete\n");
                //printf("that number was ");
                //displayINTEGER(a, stdout);
                //printf("\n");
            }
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
    statisticsBST(p,stdout);
    freeBST(p);
    return 0;
    }
