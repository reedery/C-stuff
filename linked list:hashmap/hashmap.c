// ryan reede hashmap.c

#include "map.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 100

struct map {
	List table[TABLE_SIZE];
	int (*hash)(void *); //hash function
	int (*equals)(void *, void *); //equality function
};
struct mapentry {
	void *key;
	void *value;
};
typedef struct mapentry *MapEntry;

Map Map_new(int (*equals)(void *key1, void *key2), int (*hash)(void *key)){
	Map result = (Map) malloc(sizeof(struct map));
	int i;
	for(i=0; i<TABLE_SIZE;i++){
		(result->table)[i]= List_new();
	}
	result->hash=hash;
	result->equals=equals;
	return result;
}


void *Map_get(Map m, void *key){
	int hash = m->hash(key)% TABLE_SIZE;
	List l = (m->table[hash]);
	Iterator iter =  List_iterator(l);
	while(Iterator_hasNext(iter)){
		MapEntry mapent = Iterator_next(iter);
		int res = m->equals(mapent->key,key);
		if(res == 1){ //key matches
			return mapent->value;
		}
	}
	return NULL;
}

void Map_put(Map m, void *key, void *value){
	int *val = Map_get(m, key);
	
	if (val!=NULL){
		val=value;
	}

	else{ //not in the list
		int hash = m->hash(key)%TABLE_SIZE;
		MapEntry ment = (MapEntry) malloc(sizeof(MapEntry));
		List l = (m->table[hash]);
		ment->key=key;
		ment->value=value;
		List_add(l, ment);	
		
	}

}

List Map_keys(Map m){
	int i;
	List result = List_new();
	for(i=0; i<TABLE_SIZE; i++){
		List list = m->table[i];
		Iterator iter = List_iterator(list);
		while(Iterator_hasNext(iter)){
			MapEntry mapent = Iterator_next(iter);
			List_add(result, mapent->key);
		}
	}
	return result;
}

void Map_free(Map m){
	free(m);

}





