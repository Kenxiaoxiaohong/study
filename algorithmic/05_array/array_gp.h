#ifndef __ARRAY_H__
#define __ARRAY_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct Array {
	size_t size;
	size_t len;
	size_t typeSize;
	void(*dup) (void *ptr, void *key);
	void(*free) (void *ptr);
	int(*match) (void *ptr, void *key);
	void *p;
}Array;

#define arraySetDupMethod(a,m) ((a)->dup=(m))
#define arraySetFreeMethod(a,m) ((a)->free=(m))
#define arraySetMatchMethod(a,m) ((a)->match=(m))

#define arrayGetDupMethod(a) ((a)->dup)
#define arrayGetFreeMethod(a) ((a)->free)
#define arrayGetMatchMethod(a) ((a)->match)

Array* arrayCreate();
void arrayInit(Array *arr, int size, int typeSize);

int arrayInsert(Array *arr, size_t pos, void *const value);
size_t arraySearchValue(Array *arr, void *const vaule);
void* arrayIndex(Array *arr, size_t index);
int arrayModify(Array *arr, size_t pos, void *const value);

size_t arrayLen(Array *arr);
size_t arraySize(Array *arr);

void arrayEmpty(Array *arr);
void arrayDelValue(Array *arr, void *value);
void arrayDelIndex(Array *arr, size_t index);


#endif