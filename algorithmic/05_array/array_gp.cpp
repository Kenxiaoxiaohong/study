// 05_array.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "array_gp.h"
#include <string.h>
#include <stdbool.h>

Array* arrayCreate()
{
	struct Array *array = NULL;
	array = (Array*)malloc(sizeof(*array));
	if (NULL == array)
	{
		return NULL;
	}
	array->p = NULL;
	array->size = 0;
	array->typeSize = 0;
	array->len = 0;

	array->dup = NULL;
	array->free = NULL;
	array->match = NULL;

	return array;
}

void arrayInit(Array *array, int size, int typeSize)
{
	if (NULL == array || size <= 0 || typeSize <= 0)
	{
		return;
	}

	void *p = calloc(1, size* typeSize);
	if (NULL == p)
	{
		return;
	}

	array->p = p;
	array->len = 0;
	array->size = size;
	array->typeSize = typeSize;
}

int arrayInsert(Array *array, size_t pos, void *const value)
{
	if (NULL == array)
		return -1;

	if (array->len >= array->size)
		return -2;

	if (pos > array->size || pos <= 0)
		return -3;

	char *pBegin = (char*)array->p;
	for (size_t i = array->len; i > pos - 1; --i)
	{
		void *pNew = pBegin + i * array->typeSize;
		void *pOld = pBegin + (i - 1)*array->typeSize;
		if (NULL != array->dup)
			array->dup(pNew, pOld);
		else
			memcpy(pNew, pOld, array->typeSize);
	}

	void *pCopy = (void*)(pBegin + ((pos - 1)*array->typeSize));
	if (NULL != array->dup)
		array->dup(pCopy, value);
	else
		memcpy(pCopy, value, array->typeSize);
	++array->len;
	return 0;
}

size_t arraySearchValue(Array *array, void *const value)
{
	if (NULL == array)
		return -1;

	char *pBegin = (char*)array->p;
	size_t i = 0;
	for (; i < array->len; ++i)
	{
		int nCmp = 0;
		if (NULL != array->match)
			nCmp = (array->match(pBegin + i * array->typeSize, value));
		else
			nCmp = memcmp(pBegin + i * array->typeSize, value, array->typeSize);

		if (0 == nCmp)
			break;
	}
	return i;
}

void* arrayIndex(Array *array, size_t index)
{
	if (NULL == array)
		return NULL;

	if (index > array->len || index <= 0)
		return NULL;

	char *pBegin = (char*)array->p;
	return pBegin + array->typeSize*(index - 1);
}

int arrayModify(Array *array, size_t pos, void *const value)
{
	if (NULL == array)
		return -1;
	if (pos > array->len || pos <= 0)
		return -2;

	char *pBegin = (char*)array->p;
	void *pOld = pBegin + (pos - 1)*array->typeSize;
	if (NULL != array->dup)
		array->dup(pOld, value);
	else
		memcpy(pOld, value, array->typeSize);
	return 0;
}

size_t arrayLen(Array *array)
{
	if (NULL == array)
		return 0;
	return array->len;
}

void arrayEmpty(Array *array)
{
	if (NULL == array)
		return;

	free(array->p);
	array->p = NULL;
	free(array);
	array = NULL;
}

void arrayDelValue(Array *array, void *value)
{
	if (NULL == array)
		return;

	char *pBegin = (char*)array->p;
	bool pCopy = false;
	for (size_t i = 0; i < array->len; ++i)
	{
		if (!pCopy)
		{
			int nCmp = 0;
			if (NULL != array->match)
				nCmp = array->match(pBegin + i * array->typeSize, value);
			else
				nCmp = memcmp(pBegin + i * array->typeSize, value, array->typeSize);

			if (0 == nCmp)
			{
				pCopy = true;
				continue;
			}
		}
		else
		{
			void *pOld = pBegin + (i + 1)*array->typeSize;
			void *pNew = pBegin + i * array->typeSize;
			if (NULL != array->dup)
				array->dup(pNew, pOld);
			else
				memcpy(pNew, pOld, array->typeSize);
		}
	}

	if (pCopy)
		--array->len;
}

void arrayDelIndex(Array * array, size_t pos)
{
	if (NULL == array)
		return;
	if (pos > array->len || pos <= 0)
		return;

	char* pBegin = (char*)array->p;
	for (size_t i = pos - 1; i < array->len; ++i)
	{
		void *pOld = pBegin + (i + 1)*array->typeSize;
		void *pNew = pBegin + i * array->typeSize;
		if (NULL != array->dup)
			array->dup(pNew, pOld);
		else
			memcpy(pNew, pOld, array->typeSize);
	}
	--array->len;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件