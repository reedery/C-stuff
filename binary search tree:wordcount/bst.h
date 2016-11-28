// ryan reede hw 8
// bst.h:  Functions to support binary search trees

#ifndef BST_H
#define BST_H

struct bstnode {
	void *item;
	struct bstnode *left;
	struct bstnode *right;
};

typedef struct bstnode BSTnode;

BSTnode *createNode(void *thing);

BSTnode *find(BSTnode *n, void *thing, int compare(void *, void *));

void insert(BSTnode *n, void *thing, int compare(void *, void *));


#endif




