// ryan reede: gc

#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "memorymgr.h"

void *stackBottom();
void sweep();
void mark(int *ptr);
int *getHeader(int *ptr);

void gc(){
	int *p; // = &o; 
	int **top = &p;
	int **bot = (int**)stackBottom();
	while (top <= bot){
		mark(*top);
		top++;	
	}	
	sweep();
}


void mark(int *ptr){
	int *f;
	f = (int *)firstBlock();
	int *l;
	l = (int *)lastBlock();
	// check if in heap
	if ( ptr > l || ptr < f){
		return;
	} 
	int *header = getHeader(ptr);
	int *stop = nextBlock(header);

	int size = 0;
	if (isAllocated(header)){
		size = (*header - 1 )/ 4;
		// mark 	
		*header = *header + 2;
	}

	int *ptr2 = header;
	int count = 0;
	while (count <= size){
		ptr2++;
		if (*ptr2 != NULL)
			mark(ptr2);
		count++;
	}
}


int *getHeader(int *ptr){
	int *prev = firstBlock();
	int *next = nextBlock(prev);
	int *last = lastBlock();
	while (prev != last){
		if (ptr < next)
			return prev;
		next = nextBlock(next);
		prev = nextBlock(prev);
	}
}


void sweep(){
	int *first =(int *)firstBlock();
	int *last = (int *)lastBlock();

	while (first != last){
		if (((*first) % 4) != 3){ // if not marked
			*first = (*first)/2 * 2;
		} else {
			*first = (*first) - 2;
		}
		first = nextBlock(first);
	}
	coalesce();
}


void *stackBottom() {
	unsigned long bottom;
    FILE *statfp = fopen("/proc/self/stat", "r");
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*u %*u %*u %*u %*u %*u %*d %*d "
           "%*d %*d %*d %*d %*u %*u %*d "
           "%*u %*u %*u %lu", &bottom);
    fclose(statfp);
	return (void *) bottom;
}
