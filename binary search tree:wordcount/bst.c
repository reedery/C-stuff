// bst.c ryan reede

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "wordcount.h"

BSTnode *createNode(void *thing){	
	BSTnode *node = (BSTnode *)malloc(sizeof(BSTnode));
	node -> item = thing;  
	node -> right = NULL; 
	node -> right = NULL;
	WordCount *wc = node->item;
	return node;
}

BSTnode *find(BSTnode *n, void *thing, int compare(void *, void *) ){
	WordCount *nodewc = n->item;
	WordCount *thingwc = thing;
	int c = compare(nodewc->word, thingwc->word);
	if (c == 0) {
		return n;
	} else if (c < 0 && (n->left!=NULL)) { // go left
		return find(n->left, thing, compare);  
	} else if ( c > 0 && (n->right!=NULL)) {  // go right
		return find(n->right, thing, compare);		
	}
	// no children
	return n;
}


void insert(BSTnode *n, void *thing, int compare(void *, void *)){
	WordCount *nodewc = n->item;
	WordCount *thingwc = thing;
	int c = compare(nodewc->word, thingwc->word);
	if (c < 0 )  { // go left
		if (n->left!=NULL){
			insert(n->left, thing, compare); 
		} else {
			// insert at n->left
			BSTnode *new = createNode(thingwc);	
			n->left = new;
		}
	} else if (c > 0 ) {  // go right
		if (n->right!=NULL){
			insert(n->right, thing, compare); 
		} else {
			// insert at n->left
			BSTnode *new = createNode(thingwc);
			n->right = new;
		}
	}
}













   
