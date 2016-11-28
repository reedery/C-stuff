// ryan reede: mm

#include <stdio.h>
#include <stdlib.h>
#include "memorymgr.h"

void  allocate(int *p);
void  deallocate(int *p);
int   nextMultipleOf8(int n);
void  setLength(int *p, int n);
int   getLength(int *p);


// globals
int *firstblock;
int *sentinelblock;

void initmemory(int size) {
	int heaplength = nextMultipleOf8(size + 12); // 4 bytes wasted, 4 for the two headers each
	int *heap = (int *)malloc(heaplength);        
							               
  	if (heap == NULL) {
		printf("Cannot init that much space\n");
		exit(1);
	}

	firstblock = heap + 1;    // align on 4-bytes
	setLength(firstblock, heaplength-8);   
	deallocate(firstblock);

	sentinelblock = nextBlock(firstblock);
	setLength(sentinelblock, 0);
	allocate(sentinelblock);
}

void *myalloc(int length) {
	int newlength = nextMultipleOf8(length + 4); // add 4 bytes for the header
	int *ptr   = firstBlock();
	int blklen = getLength(ptr);
	int *newptr;

	while (ptr != lastBlock() && (blklen < newlength || isAllocated(ptr))) {
		ptr = nextBlock(ptr);
		blklen = getLength(ptr);
	}
	if (ptr == lastBlock()) {  // sentinel reached
		return NULL;
	}
	if (blklen - newlength >= 8) {  // split
		setLength(ptr, newlength);
		newptr = nextBlock(ptr);
		setLength(newptr, blklen - newlength);
		deallocate(newptr);
	}
	allocate(ptr);
	return ptr+1;
}

void myfree(void *p) {
	int *ptr = (int *)p - 1;
	if (!isAllocated(ptr))
		printf("Already deallocated!\n");
	else
		deallocate(ptr);
}

void coalesce() {
	int *ptr = firstBlock();
	int *nextptr = nextBlock(ptr);
	while (nextptr != lastBlock()) {
		if (!isAllocated(ptr) && !isAllocated(nextptr))
			setLength(ptr, getLength(ptr) + getLength(nextptr));
		else 
			ptr = nextptr;
	nextptr = nextBlock(ptr);
	}
} 

void printallocation() {  // test
	int *ptr = firstBlock();
	int count = 0;
	while (ptr != lastBlock()) {
        int length = getLength(ptr);
		printf("Block %d: size %d \t", count, length);
		if (isAllocated(ptr))
			printf("allocated\n");
		else
			printf("unallocated\n");
		ptr = nextBlock(ptr);
		count++;
	}
    printf("\n");
}

int *firstBlock() {
	return firstblock;
}

int *lastBlock() {
	return sentinelblock;
}

int isAllocated(int *p) {
	return (*p) % 2 == 1;
}

void allocate(int *p) {
	*p = (*p) / 2 * 2 + 1;
}

void deallocate(int *p) {
	*p = (*p) / 2 * 2;
}

int *nextBlock(int *p) {
	return p + (getLength(p)/4);
}

int getLength(int *p) {
	return (*p)/8*8;
}

int nextMultipleOf8(int n) {
	return ((n + 7) / 8) * 8;
}

void setLength(int *p, int n) {
	*p = n;
}

