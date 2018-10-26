#include<stdio.h>

#pragma warning(disable:4996)

/*
#define NUM 15

int numbers[NUM] = { 15, 20, 34, 54, 32, 97,45, 87, 43, 21, 5, 7, 2, 1, 3};
int orderToFind = 5; 

void change_number(int a, int b)
{
	int copy = numbers[a];
	numbers[a] = numbers[b];
	numbers[b] = copy;
}

void sort(int pivot, int left, int right)
{
	while (1)
	{
		if (pivot + 1 > NUM || pivot + 2 > NUM)
		{
			//printf("%d\n", numbers[orderToFind - 1]);
			return;
		}

		if (right < left)
		{
			int cpy = pivot;
			if (pivot == orderToFind - 1)
			{
				printf("%d\n", numbers[pivot]);
				return;
			}
			else if(pivot > orderToFind - 1)
			{
				sort(cpy + 1, cpy + 2, right - 1);
			}
			else if (pivot < orderToFind - 1)
			{
				sort(left, left + 1, NUM - 1);
			}
			return;
		}
		if (numbers[left] < numbers[pivot])
		{
			left++;
		}
		else if (numbers[left] > numbers[pivot])
		{
			change_number(left, pivot);
		}
		if (numbers[right] > numbers[pivot])
		{
			right--;
		}
		else if (numbers[right] < numbers[pivot])
		{
			change_number(right, pivot);
		}
	}
}


int main()
{

	sort(0, 1, NUM - 1);

	return 0;

}*/



//===============================================================//
//=====================전교수님 코드============================//
//===============================================================//
// /*
#define SZ 15

int numbers[SZ] = { 15, 20, 34, 54, 32,
					97, 45, 87, 43, 21, 
					5,  7,  2,  1,  3 };


// _pivot의 index
// _left의 index
// _right의 index
// _which : 찾고자 하는 숫자의 index
void doSelection(int _pivot, int _left, int _right, int _which)
{
	//탈출 조건
	if (_pivot < 0 || _pivot >= SZ ||
		_left < 0 || _left >= SZ ||
		_right < 0 || _right >= SZ ||
		_left >= _right) 
	{
		printf("found location %d , which is %d\n", _which, numbers[_which]);
		return;
	}


	//기본적인 Quick Sort
	int left = _left;
	int right = _right;

	while (1)
	{
		//left 이동, pivot보다 작은 숫자들을 skip
		while (numbers[_pivot] > numbers[left])
		{
			left++;
		}

		//right 이동, pivot보다 큰 숫자들을 skip
		while (numbers[_pivot] < numbers[right])
		{
			right--;
		}

		if (left < right)
		{
			int temp = numbers[left];
			numbers[left] = numbers[right];
			numbers[right] = temp;
		}
		else // 끝낫다는것 -> right <-> pivot
		{
			if (right == _which) // 내가 찾고자 하는 위치 which 가 right 와 동일 -> 찾았음!! 리턴!!
			{
				printf("found %d number is %d \n", right, numbers[_pivot]);
				return;
			}
			else
			{
				//일단 pivot 과 right 의 위치를 바꾸고,
				int temp = numbers[_pivot];
				numbers[_pivot] = numbers[right];
				numbers[right] = temp;

				// 내가 찾고자하는 _which가 right의 어느 쪽에 잇는지를 검사.
				if (_which < right) // 왼쪽만 찾아본다.
				{
					doSelection(_pivot, _pivot + 1, right - 1, _which);
				}
				else // 오른쪽만 찾아본다.
				{
					doSelection(right + 1, right + 2, _right, _which);
				}

				return;
			}
		}
	}
}
int main(void)
{
	doSelection(0, 1, SZ - 1, 4);
	return 0;
}