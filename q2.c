#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "q2.h"



void q2()
{
	Q2_A();
	printf("\n---------------------------------------------------------------------\n");
	Q2_B();
}

void Q2_A()
{
	char** arrStr = NULL;
	int count;
	char* str1 = "aaaXXXzYkL";

	arrStr = splitOneString(&count, str1);

	for (int i = 0; i < count; i++)
		printf("%s\n", arrStr[i]);

	for (int i = 0; i < count; i++)
		free(arrStr[i]);
	free(arrStr);

}

void Q2_B()
{
	char** arrStr = NULL;
	int count;
	char* str1 = "aaaXXXzYkL";
	char* str2 = "BBBll";
	char* str3 = "ccc";
	arrStr = splitUpperLower(&count, str1, str2, str3, NULL);

	for (int i = 0; i < count; i++)
		printf("%s\n", arrStr[i]);

	for (int i = 0; i < count; i++)
		free(arrStr[i]);
	free(arrStr);
}


char** splitOneString(int* pCount, const char* str)
{
	if (!str)
		return NULL;
	char** arrStrNew = NULL;
	int size = 0;
	char temp[MAX_CHAR] = { '\0' };
	int index = 0;
	int indexInChar = 0;
	(*pCount) = 0;
	do
	{
		if ((isupper(str[index]) && isupper(str[index + 1])) | (islower(str[index]) && islower(str[index + 1])))//cheack if cureent and next char are both the same
		{
			temp[indexInChar] = str[index];//we did it bc we cant do strcpy on  char bc we dont have '\0'
			temp[indexInChar + 1] = '\0';//so it will be string
			indexInChar++;
		}
		else
		{
			temp[indexInChar] = str[index];//if  curent and next arent the same add the curent to the temp string
			temp[indexInChar + 1] = '\0';
			size++;//add one to the num of disasmbled strings
			arrStrNew = (char**)realloc(arrStrNew, sizeof(char*)*size);//array of strings
			if (!arrStrNew)
				return NULL;
			arrStrNew[size - 1] = (char*)malloc(sizeof(char)*(strlen(temp)+1));//plaace for new string
			if (!arrStrNew[size - 1])
				return NULL;
			strcpy(arrStrNew[size - 1], temp);//copy temp string to new string location
			(*pCount)++;//add 1 to num of strings in array
			indexInChar = 0;
		}
		index++;
	} while (str[index] != '\0');
	return arrStrNew;
}


char** splitUpperLower(int* pCount, const char *str1, ...)
{
	(*pCount) = 0;
	char** arrStr;
	char** combainedArrStr = NULL;
	va_list strings;
	va_start(strings, str1);
	int countOfArrStr;
	const char* temp = str1;
	while (temp)
	{
		arrStr = splitOneString(&countOfArrStr, temp);
		combainedArrStr = (char**)realloc(combainedArrStr, sizeof(char*)*(countOfArrStr + (*pCount)));
		if (!combainedArrStr)
			return NULL;
		for (int i = 0; i < countOfArrStr; i++)
			combainedArrStr[(*pCount) + i] = arrStr[i];
	//	memcpy(combainedArrStr[(*pCount)], arrStr, (sizeof(char*)*(countOfArrStr)));
		(*pCount) += countOfArrStr;
		free(arrStr);
		temp = va_arg(strings, const char*);
	}
	va_end(strings);

	return combainedArrStr;
}