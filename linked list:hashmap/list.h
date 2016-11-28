// list.h  spec of subset of List/Iterator APIs.

#ifndef LIST_H
#define LIST_H

typedef struct listnode *List;
typedef struct iteratornode *Iterator;


List List_new();

void List_add(List L, void *obj);

void List_free(List L);

Iterator List_iterator(List L);

int Iterator_hasNext(Iterator I);

void *Iterator_next(Iterator I);

void Iterator_free(Iterator I);

#endif
