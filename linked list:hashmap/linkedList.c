// ryan reede (subset) linked-node implementation

#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "map.h"


struct listnode {
    void *info;
    struct listnode *next;
};

struct iteratornode {
    struct listnode *currentnode;
};

List List_new() {
    // allocate header node
    List L = (List) malloc(sizeof(struct listnode));
    L->next = NULL;
    return L;
}

void List_add(List L, void *obj) {
    while (L->next != NULL)
        L = L->next;
    // allocate new node
    List newnode = (List) malloc(sizeof(struct listnode));
    newnode->info = obj;
    newnode->next = NULL;
    L->next = newnode;
}

void List_free(List node) {
    while (node != NULL) {
        List next = node->next;
        free(node);
        node = next;
    }
}

Iterator List_iterator(List L) {
    Iterator I = (Iterator) malloc(sizeof(struct iteratornode));
    I->currentnode = L;
    return I;
}

int Iterator_hasNext(Iterator I) {
    return I->currentnode->next != NULL;
}

void *Iterator_next(Iterator I) {
    I->currentnode = I->currentnode->next;
    return I->currentnode->info;
}

void Iterator_free(Iterator I) {
    free(I);
}






