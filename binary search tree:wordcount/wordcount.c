// wordcount.c ryan reede 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "wordcount.h"

WordCount *addWordCount(char *str);

int c(void *one, void *two){ 
	return ( strcmp( (char *)one, (char *)two) );
}

int main(){
	int currmax = 1;
	char lim[80];
	scanf("%s", lim); // for root, first word read
	WordCount *rootWordCount = addWordCount(lim);
	BSTnode *rootNode = createNode(rootWordCount);  
	WordCount *max = rootWordCount; //for max

	char currstr[80];
	int (*compare)(void *, void *); // func ptr
	compare = c;

	while(scanf("%s", currstr) != EOF ){		
		WordCount *currWordCount = addWordCount(currstr);
		BSTnode *curr = find(rootNode, currWordCount, compare);
		WordCount *testWordCount = curr->item;

		if (strcmp(currWordCount->word, testWordCount->word) == 0 ){  // combine
			testWordCount->count++; // from find()
			if (testWordCount->count > currmax){
				currmax = testWordCount->count;
				max = testWordCount;
			}
		} else {
			insert(rootNode, currWordCount, compare);
		}
	}	
	printf("\nThe word \"%s\" appears most frequently (%d instances).\n", max->word, currmax);	
}

WordCount *addWordCount(char *str) {
    WordCount *wc = (WordCount *) malloc(sizeof(WordCount));
	strcpy(wc->word, str);
	wc->count = 1;
    return wc;
}




