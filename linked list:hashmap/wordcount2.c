// wordcount2.c ryan reede
// Use a map to count the frequency of the words in the standard input

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertNewWord(Map m, char *word);
void printMax(Map m);
int equalWords(void *word1, void *word2);
int hashWord(void *word);

int main() {
	
	Map m = Map_new(equalWords, hashWord);

	char word[81];
	int status = scanf("%80s", word);	
	while (status != EOF) {
		int *value = (int *) Map_get(m, word);
		if (value != NULL) {
			*value = *value + 1;
			Map_put(m, word, value);
		}
		else {
			insertNewWord(m, word);
		}
		status = scanf("%80s", word);
	}
	printMax(m);
	Map_free(m);
}	

void insertNewWord(Map m, char *word) {
	char *key = (char *) malloc(strlen(word)+1);
	int *value = (int *) malloc(sizeof(int));
	strcpy(key, word);
	*value = 1;
	Map_put(m, key, value); 
}

void printMax(Map m) {
	int maxcount = 0;
	char *maxword = NULL;

	List keys = Map_keys(m);
	Iterator iter = List_iterator(keys);
	while (Iterator_hasNext(iter)) {
		void *key = Iterator_next(iter);
		int *value = (int *) Map_get(m, key);
		if (*value > maxcount) {
			maxcount = *value;
			maxword = (char *) key;
		}
	}		
	printf("\nThe most frequent word is \"%s\", which appears %d times.\n", 
			maxword, maxcount);
}

int equalWords(void *w1, void *w2) {
	return strcmp(w1, w2) == 0;
}

int hashWord(void *w) {
	char *s = (char *) w;
	int count = 0;
	int i;
	for (i=0; i<strlen(s); i++)
		count += s[i];
	return count;
}




	

		

	

