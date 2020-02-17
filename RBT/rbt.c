#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rbt.h"
#include "gst.h"
#include "tnode.h"

void insertionFixup(GST *tree, TNODE *);
void deletionFixup(GST *tree, TNODE *);
void roRoFightThePower(GST *tree, TNODE *a, TNODE *b);

typedef struct RBTVALUE{
    void *value;
    int color;
    int freq;
    RBT *tree;
}RBTVALUE;

typedef struct rbt{
	GST *gtree;
	void (*display)(void *, FILE *);
	int (*compare)(void *,void *);
	void (*swap)(TNODE *, TNODE *);
    int size;
    int words;
    int debug;
    void (*free)(void *);
}RBT;

static void freeRBTV(void *value){
	//printf("am I freeing here?\n");
	RBTVALUE *f = value;
	if(f->tree->free) f->tree->free(f->value);
	free(f);
}

static void displayRBTVal(void *value, FILE *f){
	RBTVALUE *v = value;
	v->tree->display(v->value, f);
	if(v->color == 0){
		fprintf(f, "*");
	}
	if(v->freq > 1){
		fprintf(f, "<%d>",freqGST(v->tree->gtree, v->value));
	}
}

void swapper(TNODE *a,TNODE *b)
{
    void *va = getTNODEvalue(a);   //get the GST value
    void *vb = getTNODEvalue(b);   //get the GST value
    setTNODEvalue(a,vb);
    setTNODEvalue(b,va);
    RBTVALUE *x = unwrapGST(a);
    RBTVALUE *y = unwrapGST(b);
    int color = x->color;
    x->color = y->color;
    y->color = color;
}


int rbtComparator(void *x, void *y){
	RBTVALUE *temp1 = x;
	RBTVALUE *temp2 = y;
	return temp1->tree->compare(temp1->value, temp2->value);
}

RBTVALUE *newRBTVALUE(RBT *tree){
	RBTVALUE *node = malloc(sizeof(RBTVALUE));
	//node->display = a;
	//node->compare = b;
	node->freq = 1;
	node->value = NULL;
	node->color = 0;
	node->tree = tree;
	return node;
}



RBT *newRBT(int(*b)(void*,void*)){
	RBT *tree = malloc(sizeof(RBT));
	tree->gtree = newGST(rbtComparator);
	tree->compare = b;
	tree->size = 0;
	tree->words = 0;
	tree->free = NULL;
	tree->debug = 0;
	tree->swap = NULL;
	setGSTswapper(tree->gtree, swapper);
	setGSTdisplay(tree->gtree, displayRBTVal);
	setGSTfree(tree->gtree, freeRBTV);
	return tree;
}

void   setRBTdisplay(RBT *t,void (*d)(void *,FILE *)){
	t->display = d;
}

void   setRBTswapper(RBT *t,void (*s)(TNODE *,TNODE *)){
	t->swap = s;
}

void   setRBTfree(RBT *t,void (*f)(void *)){
	t->free = f;
	//setGSTfree(t->gtree, f);
}

TNODE *getRBTroot(RBT *t){
	return getGSTroot(t->gtree);
}

void   setRBTroot(RBT *t,TNODE *replacement){
	setGSTroot(t->gtree, replacement);
}

void   setRBTsize(RBT *t,int s){
	t->size = s;
	setGSTsize(t->gtree, s);
}

TNODE *insertRBT(RBT *tree, void *value){
	RBTVALUE *sob = newRBTVALUE(tree);
	sob->value = value;
	//TNODE *t = locateGST(tree->gtree, sob);
	TNODE *t = insertGST(tree->gtree, sob);
	if(t != NULL){
		insertionFixup(tree->gtree, t);
		tree->size++;
		tree->words++;
	}
	return t;
}

void *findRBT(RBT *tree, void *target){
	RBTVALUE *cry = newRBTVALUE(tree);
	cry->value = target;
	TNODE *sad = locateGST(tree->gtree, cry);
	free(cry);
	if(!sad) return NULL;
	return ((RBTVALUE *)unwrapGST(sad))->value;
}

TNODE *locateRBT(RBT *t,void *key){
	RBTVALUE *cry = newRBTVALUE(t);
	cry->value = key;
	TNODE *sad = locateGST(t->gtree, cry);
	free(cry);
	if(!sad) return NULL;
	return sad;
}

int deleteRBT(RBT *tree, void *target){
	RBTVALUE *apathy = newRBTVALUE(tree);
	apathy->value = target;
	TNODE *t = locateGST(tree->gtree, apathy);
	free(apathy);
	if(t == NULL){
		return -1;
	}
	else{
		RBTVALUE *x = unwrapGST(t);
		if(freqGST(tree->gtree, x) > 1){
			deleteGST(tree->gtree, x);
		}
		else{
			TNODE *p = swapToLeafGST(tree->gtree, t);
			deletionFixup(tree->gtree, p);
			pruneLeafGST(tree->gtree, p);
			setRBTsize(tree, sizeRBT(tree) - 1);
			free(x);
			freeTNODE(p);
		}
		tree->words--;
	}
	return 0;
}

///red black tree frees tnode and rbtVAL
///

TNODE *swapToLeafRBT(RBT *t,TNODE *node){
	TNODE *leaf = swapToLeafGST(t->gtree, node);
	return leaf;
}

void   pruneLeafRBT(RBT *t,TNODE *leaf){
	pruneLeafGST(t->gtree, leaf);
}
 
int sizeRBT(RBT *tree){
	int size = sizeGST(tree->gtree);
	return size;
}

int wordsRBT(RBT *tree){
	return tree->words;
}

void statisticsRBT(RBT *tree, FILE *f){
	statisticsGST(tree->gtree, f);
}

void displayRBT(RBT *tree, FILE *f){
	displayGST(tree->gtree, f);
}

int    debugRBT(RBT *t,int level){
	int old = debugGST(t->gtree, level);
	return old;
}

void   freeRBT(RBT *t){
	freeGST(t->gtree);
	free(t);
}

void   *unwrapRBT(TNODE *n){
	RBTVALUE *set = unwrapGST(n);
	return set->value;
}

int    freqRBT(RBT *r,void *key){
	TNODE *t = locateRBT(r, key);
	if(!t){
		return 0;
	}
	else{
		return freqGST(r->gtree, unwrapGST(t));
	}
}

int    duplicatesRBT(RBT *t){
	return duplicatesGST(t->gtree);
	
}

/* ONLY MESS WITH THE TNODE, NOT THE STRUCTURE!!!!*/

void deletionFixup(GST *tree, TNODE *p){
	TNODE *parent = NULL;
	TNODE *sibling = NULL;
	TNODE *niece = NULL;
	TNODE *nephew = NULL;
	while(1){
		if(p == getGSTroot(tree)){
			//printf("CASE : root\n");
			break;
		}
		if(((RBTVALUE *)(unwrapGST(p)))->color == 0){
			//printf("CASE : red \n");
			break;
		}
		parent = getTNODEparent(p);
		if(parent != NULL && ((RBTVALUE *)(unwrapGST(p)))->color == 0){
			//printf("CASE : parent \n");
			break;
		}
		if(getTNODEleft(parent) == p){
			sibling = getTNODEright(parent);
			if(sibling){
			niece = getTNODEleft(sibling);
			nephew = getTNODEright(sibling);
			}	
		}
		else{
			sibling = getTNODEleft(parent);
			if(sibling){
			niece = getTNODEright(sibling);
			nephew = getTNODEleft(sibling);
			}
		}
		if(sibling != NULL && ((RBTVALUE *)(unwrapGST(sibling)))->color == 0){
				//printf("CASE : sibling \n");
				((RBTVALUE *)(unwrapGST(parent)))->color = 0;
				((RBTVALUE *)(unwrapGST(sibling)))->color = 1;
				roRoFightThePower(tree, sibling, parent);
		}
		else if(nephew != NULL && ((RBTVALUE *)(unwrapGST(nephew)))->color == 0){
				//printf("CASE : nephew \n");
				((RBTVALUE *)(unwrapGST(sibling)))->color = ((RBTVALUE *)(unwrapGST(parent)))->color;
				((RBTVALUE *)(unwrapGST(parent)))->color = 1;
				((RBTVALUE *)(unwrapGST(nephew)))->color = 1;
				roRoFightThePower(tree, sibling, parent);
			break;
		}
		else if(niece != NULL && ((RBTVALUE *)(unwrapGST(niece)))->color == 0){
				//printf("CASE : niece \n");
				((RBTVALUE *)(unwrapGST(niece)))->color = 1;
				((RBTVALUE *)(unwrapGST(sibling)))->color = 0;
				roRoFightThePower(tree, niece, sibling);
		}
		else{
			//printf("CASE : None of the above\n");
			if(sibling) ((RBTVALUE *)(unwrapGST(sibling)))->color = 0;
			p = parent;
		}
	}
	((RBTVALUE *)(unwrapGST(p)))->color = 1;
}



void insertionFixup(GST *tree, TNODE *p){

	TNODE *temp = p;
	TNODE *uncle;
	TNODE *parentHolder;
	int rotationOrder;
	while(1){
		parentHolder = getTNODEparent(temp);
		if(getTNODEvalue(getGSTroot(tree)) == getTNODEvalue(temp)){
			//printf("This node is the root\n");
			((RBTVALUE *)(unwrapGST(temp)))->color = 1;
			//printf("This part is done\n");
			return;
		}
		if(((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color == 1 || ((RBTVALUE *)(unwrapGST(temp)))->color == 1 ){
			return;
		}
		if(getTNODEleft(getTNODEparent(parentHolder)) == getTNODEparent(temp)){
			//printf("rotating right\n");
			rotationOrder = 0;
			uncle = getTNODEright(getTNODEparent(getTNODEparent(temp)));
			//printf("mark\n");
		}
		else{	
			rotationOrder = 1;
			uncle = getTNODEleft(getTNODEparent(getTNODEparent(temp)));
		}

		if(uncle && ((RBTVALUE *)(unwrapGST(uncle)))->color == 0 && ((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color == 0 ){
			((RBTVALUE *)(unwrapGST(uncle)))->color = 1;
			((RBTVALUE *)(unwrapGST(parentHolder)))->color = 1;
			((RBTVALUE *)(unwrapGST(getTNODEparent(getTNODEparent(temp)))))->color = 0;
			temp = getTNODEparent(getTNODEparent(temp));
		}
		else{
			//printf("uncle doesn't exist \n");
			if(((RBTVALUE *)unwrapGST(getTNODEparent(temp)))->color == 0){
			//	printf("parent is red too. That's not good\n");
			int check;
			if(getTNODEleft(getTNODEparent(temp)) == temp){
				if(rotationOrder == 0){
					//printf("linear rotation from the left side\n");
					check = ((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color = ((RBTVALUE *)(unwrapGST(getTNODEparent(getTNODEparent(temp)))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(getTNODEparent(temp)))))->color = check;
					//printf("bout to rotate this sucka\n");
					roRoFightThePower(tree, getTNODEparent(temp), getTNODEparent(getTNODEparent(temp)));
					temp = parentHolder;
				}
				else{ //nonlinear
					//printf("nonlinear rotation from the left side\n");
					roRoFightThePower(tree, temp, getTNODEparent(temp));
					check = ((RBTVALUE *)(unwrapGST(temp)))->color;
					((RBTVALUE *)(unwrapGST(temp)))->color = ((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color = check;
					roRoFightThePower(tree, temp, getTNODEparent(temp));
					temp = parentHolder;
				}
			}
			else{ //nonlinear
				if(rotationOrder == 0){
					//printf("nonlinear rotation from the right side\n");
					roRoFightThePower(tree, temp, getTNODEparent(temp));
					check = ((RBTVALUE *)(unwrapGST(temp)))->color;
					((RBTVALUE *)(unwrapGST(temp)))->color = ((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color = check;
					roRoFightThePower(tree, temp, getTNODEparent(temp));
					temp = parentHolder;
				}
				else{
					//printf("nonlinear rotation from the right side\n");
					check = ((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(temp))))->color = ((RBTVALUE *)(unwrapGST(getTNODEparent(getTNODEparent(temp)))))->color;
					((RBTVALUE *)(unwrapGST(getTNODEparent(getTNODEparent(temp)))))->color = check;
					roRoFightThePower(tree, getTNODEparent(temp), getTNODEparent(getTNODEparent(temp)));
					temp = parentHolder;
				}
			}
		}
	}
	}

	return;
}

void roRoFightThePower(GST *tree, TNODE *a, TNODE *b){
	if(getTNODEleft(b) == a){
		setTNODEleft(b, getTNODEright(a));
		if(getTNODEleft(b)){
			setTNODEparent(getTNODEleft(b),b);
		}
		if(getTNODEparent(b) != b){
			setTNODEparent(a, getTNODEparent(b));
		}
		else{
			setTNODEparent(a, a);
			setGSTroot(tree, a);
		}
		if(getTNODEleft(getTNODEparent(a)) == b){
			setTNODEleft(getTNODEparent(a), a);
		}
		else{
			setTNODEright(getTNODEparent(a), a);
		}
		setTNODEright(a, b);
		setTNODEparent(b, a);
	}
	else{
		setTNODEright(b, getTNODEleft(a));
		if(getTNODEright(b)) setTNODEparent(getTNODEright(b), b);
		if(getTNODEparent(b) != b) setTNODEparent(a, getTNODEparent(b));
		else{
			setTNODEparent(a, a);
			setGSTroot(tree, a);
		}
		if(getTNODEright(getTNODEparent(a)) == b) setTNODEright(getTNODEparent(a), a);
		else setTNODEleft(getTNODEparent(a), a);
		setTNODEleft(a, b);
		setTNODEparent(b, a);
	}
	return;
}