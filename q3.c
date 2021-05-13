#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q3.h"

void q3()
{
	printf("\n------- Q3_A ------------ \n");
	Q3_A();
	printf("\n------- Q3_B ------------ \n");
	Q3_B();
}

void	Q3_A()
{
	int size;
	int** arr = createArr(FILE_NAME,&size);
	printAllArrs(arr, size);
	freeAll(arr, size);
}

void	Q3_B()
{
	int arr[] = {6, 5, 6, 3, 2, 7, 4};
	int* newArr = createSpecialArr(arr, isEven);
	printOneArr(newArr);
	free(newArr);
	printf("\n-------------------------------------------------------------------\n");
	newArr = createSpecialArr(arr, isDiv3);
	printOneArr(newArr);
	free(newArr);

}

int** createArr(const char* fileName, int* pSize)
{
	FILE* fp = fopen(fileName,"rb");
	if (!fp)
		return NULL;
	BYTE first;
	if (fread(&first, sizeof(BYTE), 1, fp) != 1)
		return NULL;
	(*pSize) = first;
	int** matrix = (int**)malloc(sizeof(int*)*(*pSize));
	if (!matrix)
		return NULL;

	for (int i = 0; i < (*pSize); i++)
	{
		if (fread(&first, sizeof(BYTE), 1, fp) != 1)
			return NULL;
		int size = (first & 0xF0) >> 4;
		matrix[i] = (int*)malloc(sizeof(int)*(size + 1));
		if (!matrix[i])
			return NULL;
		for (int j = 0; j < (size + 1); j = j +2)
		{
			matrix[i][j] = (first & 0xF0) >> 4;
			if (j != size)
			{
				matrix[i][j + 1] = (first & 0xF);
				if ((j!=(size-1)) &&fread(&first, sizeof(BYTE), 1, fp) != 1)
					return NULL;
			}
		}
	}
	return matrix;
}

int*	createSpecialArr(int* arr, int func(void* elements))
{
	int index = 0 , count = 0;
	if (!func)
		return NULL;
	for (int i = 1; i < (arr[0] + 1); i++)
		if (func(&arr[i]))
			count++;//count the num of numbers that fit what we want
	int* newArr = (int*)calloc((count + 1), sizeof(int));//make new arr in the exact size that we need
	if (!newArr)
		return NULL;
	newArr[index++] = count;//put in 0 the size of arr
	for (int i = 1; i < (arr[0] + 1); i++)
		if (func(&arr[i]))
			newArr[index++] = arr[i];
	return newArr;
}

int isEven(void* element)
{
	int x = *(int*)element;
	return (x % 2) == 0 ? 1 : 0;
}
int isDiv3(void* element)
{
	int x = *(int*)element;
	return (x % 3) == 0 ? 1 : 0;
}
void  printAllArrs(int** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("arr number %d:\t", (i + 1));
		printOneArr(arr[i]);
	}
}

void	printOneArr(int* arr)
{
	int count = arr[0];
	if (count == 0)
		printf("Empty Arr\n");
	for (int j = 0; j < count; j++)
		printf("%d ", arr[j + 1]);
	printf("\n");
}

void freeAll(int** arr, int size)
{
	for (int i = 0; i < size; i++)
		free(arr[i]);
	free(arr);
}
