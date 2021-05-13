#pragma once

typedef struct
{
	int digit;
	int count;
}OCCUR;


void q1();
void Q1_A();
void Q1_B();

OCCUR*	createOccurance(long num, int *size);
long	createSortedNum(long num);

void	printOccur(const OCCUR* pData);