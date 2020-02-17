#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "gst.h"
#include "tnode.h"


typedef struct gst{
	BST *bstree;
	void (*display)(void *, FILE *);
	int (*compare)(void *, void *);
	int size;
	int words;
	void (*swap)(TNODE *, TNODE *);
	void (*free)(void *);
	int debug;
}GST;

typedef struct GSTNode{
    void *value;
    int freq;
    GST *tree;
} GSTNode;

static void swapper(TNODE *a, TNODE *b){
	void *x = getTNODEvalue(a);
	void *y = getTNODEvalue(b);
	setTNODEvalue(a, y);
	setTNODEvalue(b, x);
}


static void displayVal(void *value, FILE *f){
	GSTNode *g = value;
	g->tree->display(g->value, f);
	if(g->freq > 1){
		fprintf(f, "<%d>",g->freq);
	}
}

void decreaseFreq(TNODE *t){
	GSTNode *g = getTNODEvalue(t);
	g->freq--;
	return;
}

static void freeGSTV(void *value){
	GSTNode *f = value;
	if(f->tree->free) f->tree->free(f->value);
	free(f);
}

int GSTComparator(void *x, void *y){
	GSTNode *first = x;
	GSTNode *second = y;
	return first->tree->compare(first->value, second->value);
}

GST *newGST(int (*c)(void *,void *)){
	GST *tree = malloc(sizeof(GST));
	tree->bstree = newBST(GSTComparator);
	tree->compare = c;
	tree->size = 0;
	tree->words = 0;
	tree->debug = 0;
	setBSTdisplay(tree->bstree, displayVal);
	setBSTswapper(tree->bstree, swapper);
	setBSTfree(tree->bstree, freeGSTV);
	return tree;
}

void   setGSTdisplay(GST *t,void (*d)(void *,FILE *)){
	t->display = d;
}

void   setGSTswapper(GST *t,void (*s)(TNODE *,TNODE *)){
	t->swap = s;
	setBSTswapper(t->bstree, s);
}

void   setGSTfree(GST *t,void (*f)(void *)){
	t->free = f;
	//setBSTfree(t->bstree, f);
}

GSTNode *newGSTNode(void *value, GST *tree){
	GSTNode *gnode = malloc(sizeof(GSTNode));
	gnode->value = value;
	gnode->freq = 1;
	gnode->tree = tree;
	//gnode->display = d;
	//gnode->compare = c;
	return gnode;
}

TNODE *getGSTroot(GST *t){
	return getBSTroot(t->bstree);
}

void   setGSTroot(GST *t,TNODE *replacement){
	//printf("setting the root(GST)\n");
	setBSTroot(t->bstree, replacement);
}

void   setGSTsize(GST *t,int s){
	setBSTsize(t->bstree, s);
}

TNODE *insertGST(GST *GST, void *value){
	GSTNode *sob = newGSTNode(value, GST);
	TNODE *t = locateBST(GST->bstree, sob);
	if(!t) {
		t = insertBST(GST->bstree, sob);
		GST->size++;
	}
	else{
		((GSTNode *)getTNODEvalue(t))->freq++;
		freeGSTV(sob);
		//free(sob);
		//free(t);
		t = NULL;
	}
	//free(sob);
	GST->words++;
	return t;
}

void* findGST(GST *t, void *value){
	GSTNode *cry = newGSTNode(value, t);
	TNODE *sad = locateBST(t->bstree, cry);
	free(cry);
	if(!sad){
		return NULL;
	}
	return ((GSTNode *) getTNODEvalue(sad))->value;
}

TNODE *locateGST(GST *t,void *key){
	GSTNode *cry = newGSTNode(key, t);
	TNODE *sad = locateBST(t->bstree, cry);
	free(cry);
	if(!sad) return NULL;
	return sad;
}

int deleteGST(GST *GST, void *value){
	GSTNode *despair = newGSTNode(value, GST);
	TNODE *t = locateBST(GST->bstree, despair);
	free(despair);
	if(t == NULL){
		return -1;
	}
	else{
		GSTNode *meh = getTNODEvalue(t);
		if(((GSTNode *)getTNODEvalue(t))->freq>1){
			//printf("i should be here\n");
			meh->freq--;
		}
		else{
			//printf("I shouldn't be here\n");
			deleteBST(GST->bstree, getTNODEvalue(t));
			free(meh);
			//free(getTNODEvalue(t));
			//free(t);
		}
		//free(despair);
		GST->words--;
	}
	return 0;
}

TNODE *swapToLeafGST(GST *t,TNODE *node){
	//setBSTswapper(t->bstree, t->swap);
	TNODE *leaf = swapToLeafBST(t->bstree, node);
	return leaf;
}

void   pruneLeafGST(GST *t,TNODE *leaf){
	free(getTNODEvalue(leaf));
	pruneLeafBST(t->bstree, leaf);
	t->words--;
}

int sizeGST(GST *GST){
	int size = sizeBST(GST->bstree);
	return size;

}

int wordsGST(GST *tree){
	return tree->words;
}

void statisticsGST(GST *GST, FILE *f){
	int x = duplicatesGST(GST);
	fprintf(f, "Duplicates: %d\n", x);
	statisticsBST(GST->bstree, f);
}

void displayGST(GST *GST, FILE *f){
	displayBST(GST->bstree, f);
}

int    debugGST(GST *t,int level){
	int old = debugBST(t->bstree, level);
	return old;
}

void   freeGST(GST *t){
	freeBST(t->bstree);
	free(t);
}

void *unwrapGST(TNODE *n){
	GSTNode *g = getTNODEvalue(n);
	return g->value;
}

int    freqGST(GST *g,void *key){
	TNODE *d = locateGST(g, key);
	if(d==0){
		return 0;
	}
	else{
		return ((GSTNode *)getTNODEvalue(d))->freq;
	}
}

int    duplicatesGST(GST *g){
	return wordsGST(g) - sizeGST(g);
}

