#include <stdio.h>


#define FILE_NAME "numbers_comp.bin"
typedef unsigned char BYTE;
void	q3();
void	Q3_A();
void	Q3_B();


int**	createArr(const char* fileName,int* pSize);
int*	createSpecialArr(int* arr, int func(void* elements));
int isEven(void* element);
int isDiv3(void* element);
void	printAllArrs(int** arr,int size);
void	printOneArr(int* arr);
void	freeAll(int** arr, int size);
