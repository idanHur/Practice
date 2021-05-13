#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q1.h"



void q1()
{
	printf("\n------- Q1_A ------------ \n");
	Q1_A();
	printf("\n------- Q1_B ------------ \n");
	Q1_B();

}

void Q1_A()
{
	long num = 435536111;
	int size = 0;
	OCCUR* arrOccur = createOccurance(num, &size);
	for (int i = 0; i < size; i++)
		printOccur(&arrOccur[i]);

	free(arrOccur);
}

void Q1_B()
{
	long num = 435536111;
	long res = createSortedNum(num);
	printf("Orig num %ld New Num %ld\n", num, res);
}


OCCUR* createOccurance(long num, int *size)
{
	long temp = num;
	int times[10] = { 0 };//arr size of all possible num to cheack occurance and etc 
	int index = 0; //index in occur arr to set every num occur val and num of occurence
	while (0 < temp)
	{
		int modulo = temp % 10;//get the most right num from long
		if (times[modulo] == 0)// if its the first time of occurenc of this num then size++ 
			(*size)++;
		times[modulo]++;//uplode  the num of occur of this num 
		temp = temp / 10;
	}
	OCCUR* arr = (OCCUR*)malloc(sizeof(OCCUR)*(*size));
	if (!arr)
		return NULL;
	for (int i = 0; i < 10; i++)
		if (times[i] != 0)
		{
			arr[index].digit = i;
			arr[index].count = times[i];
			index++;
		}
	return arr;
}

long createSortedNum(long num)
{
	int size = 0;
	OCCUR* arr = createOccurance(num, &size);//get sorted list of num and num of occurence
	long newNum = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < arr[i].count; j++)
			newNum = newNum * 10 + arr[i].digit;//mult the newnum by 10 to have new place for new occurence of num and add the new occurence of num
	free(arr);
	return newNum;
}

void printOccur(const OCCUR* pData)
{
	printf("(%d,%d)\t", pData->digit, pData->count);

}