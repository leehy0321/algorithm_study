#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#define SZ 9 // 0은 맨뒤에 무조건 붙으니까 하나 빼고 계산한다. <- 왜냐하면 int 최대 크기가 21억 이기 때문

int numbers[SZ];

void initNumbers(void)
{
	for (int i = 0; i < SZ; i++)
	{
		numbers[i] = -1;
	} //이제 한줄이라도 괄호를 꼭 쳐야합니당 ... !!! 
}

int makeNumbers(int idx) // 배열 -> 숫자로 바꿔준다.
{
	// numbers = {1,2,3,-1,-1,...} => 123 으로 만들어주는 느낌~

	int sum = numbers[0];
	for (int i = 1; i <= idx; i++)
	{
		sum = sum * 10 + numbers[i];
	}
	return sum;
}

// idx 위치에 v라는 숫자를 넣는다.
// 그리고
// 거기까지 만들어진 숫자가 조건에 맞는지를 검사한다.
void checkNumber(int v, int idx)
{

	/*
	0. 숫자를 집어 넣는다.
	*/
	numbers[idx] = v;

	/* 
	   1. idx앞에 v와 겹치는 숫자가 있는지 검사한다.
	.				-> 실패하면 return
	*/
	for (int i = 0; i < idx; i++)
	{
		if (numbers[i] == v)
		{
			return;
		}
	}

	/*  
	   2. numbers[0,....idx]까지 숫자가 '조건'을 만족하는지 검사한다.
					-> 실패하면 return
	*/
	if (makeNumbers(idx) % (idx + 1) != 0)
	{
		return;
	}

	/*
	탈출조건
	*/
	if (idx == 8)
	{
		printf("The NUMBER is %d\n", makeNumbers(8));
		return;
	}



	/*
	3. 1차와 2차 관문을 무사히 통과했다면
					-> 다음 단계로 진입
	*/
	for (int i = 1; i <= 9; i++)
	{
		checkNumber(i, idx+1);
	}
}
int main()
{
	initNumbers();

	for (int i = 1; i <= 9; i++)
	{
		checkNumber(i, 0);
	}
	
	return 0;
}