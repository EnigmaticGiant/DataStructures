#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tnode.h"

typedef struct tnode{
	void *value;
	TNODE *left;
	TNODE *right;
	TNODE *parent;
	void (*display)(void *, FILE *);
	void (*free)(void *);
	int debug;

}TNODE;

TNODE *newTNODE(void *v,TNODE *l,TNODE *r,TNODE *p){
	TNODE *new = malloc(sizeof(TNODE));
	new->value = v;
	new->left = l;
	new->right = r;
	new->parent = p;
	new->display = NULL;
	new->free = NULL;
	new->debug = 0;
	return new;
}
void   setTNODEdisplay(TNODE *n,void (*d)(void *value,FILE *fp)){
	n->display = d;
	return;
}
void   setTNODEfree(TNODE *n,void (*f)(void *value)){
	n->free = f;
	return;
}
void  *getTNODEvalue(TNODE *n){
	return n->value;
}
void   setTNODEvalue(TNODE *n,void *replacement){
	n->value = replacement;
	return;
}
TNODE *getTNODEleft(TNODE *n){
	return n->left;
}
void   setTNODEleft(TNODE *n,TNODE *replacement){
	n->left = replacement;
	return;
}
TNODE *getTNODEright(TNODE *n){
	return n->right;
}
void   setTNODEright(TNODE *n,TNODE *replacement){
	n->right = replacement;
	return;
} 
TNODE *getTNODEparent(TNODE *n){
	return n->parent;
}
void   setTNODEparent(TNODE *n,TNODE *replacement){
	n->parent = replacement;
	return;
}
void   displayTNODE(TNODE *n,FILE *fp){
	void *address;
	if(n->display){
		n->display(n->value, fp);
		if(n->debug > 0){
			address = &n->value;
			fprintf(fp,"%p", address);
		}
	}
	else{
		address = &n->value;
		fprintf(fp, "%p", address);
	}
	return;
}
int    debugTNODE(TNODE *n,int level){
	int old = n->debug;
	n->debug = level;
	return old;
}
void   freeTNODE(TNODE *n){
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	//n->value = NULL;
	if(n->free) n->free(n->value);
	free(n);
	return;
}