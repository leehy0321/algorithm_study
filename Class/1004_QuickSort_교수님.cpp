#include<stdio.h>

#pragma warning(disable:4996)

#define SZ 10

int numbers[SZ] = { 1,6,7,14,11,8,2,3,5,15 };

//int numbers[SZ] = { 10,11,7,13,5,16,2,12,6 };
//int numbers[SZ] = { 1,2,3,4,5,6,7,8,10,9 };
void change_number(int a, int b)
{
	int copy = numbers[a];
	numbers[a] = numbers[b];
	numbers[b] = copy;
}


// _pivot : 피봇의 인덱스
// _letf : L의 시작위치
// _right : R의 시작위치
void qsort(int _pivot, int _left, int _right)
{
	// recursive :: 탈출조건 ..... 나중에 생각
	if (_pivot < 0 || _pivot >= SZ
	    || _left < 0 || _left >= SZ
		|| _right < 0 || _right >= SZ)
	{
		return;
	}

	if (_pivot > _left) // _pivot은 _left보다 왼쪽에 잇어야
	{
		return;
	}

	if (_left > _right)//_left 가 _rignt 보다는 항상 왼쪽에서 시작
	{
		return;
	}
	// l과 R을 변경시켜야 하기 때문에 복사를 해놓는다.
	int l = _left;
	int r = _right;

	//반복
	while (1)
	{
		//while :: 탈출조건
		
		//L을 이동
		while (numbers[_pivot] > numbers[l])
		{
			l++;
		}
		//R을 이동
		while (numbers[_pivot] < numbers[r])
		{
			r--;
		}

		//L < R 있으면 스왑!
		if (l < r)
		{
			change_number(l, r);
		}
		else //L > R 있으면 recursive 한 후에 종료!
		{
			//pivot하고 바꿔치고, 
			change_number(r, _pivot);

			//recursive하고, 
			qsort(_pivot,_pivot+1,r-1);// 왼쪽
			qsort(r + 1, r + 2, _right);
			//종료!
			return;
		}
	}
}

int main()
{
	qsort(0, 1, SZ - 1);

	for (int i = 0; i < SZ; i++)
	{
		printf("%d  ", numbers[i]);
	}
	return 0;
}
