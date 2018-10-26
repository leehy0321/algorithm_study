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
//=====================�������� �ڵ�============================//
//===============================================================//
// /*
#define SZ 15

int numbers[SZ] = { 15, 20, 34, 54, 32,
					97, 45, 87, 43, 21, 
					5,  7,  2,  1,  3 };


// _pivot�� index
// _left�� index
// _right�� index
// _which : ã���� �ϴ� ������ index
void doSelection(int _pivot, int _left, int _right, int _which)
{
	//Ż�� ����
	if (_pivot < 0 || _pivot >= SZ ||
		_left < 0 || _left >= SZ ||
		_right < 0 || _right >= SZ ||
		_left >= _right) 
	{
		printf("found location %d , which is %d\n", _which, numbers[_which]);
		return;
	}


	//�⺻���� Quick Sort
	int left = _left;
	int right = _right;

	while (1)
	{
		//left �̵�, pivot���� ���� ���ڵ��� skip
		while (numbers[_pivot] > numbers[left])
		{
			left++;
		}

		//right �̵�, pivot���� ū ���ڵ��� skip
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
		else // �����ٴ°� -> right <-> pivot
		{
			if (right == _which) // ���� ã���� �ϴ� ��ġ which �� right �� ���� -> ã����!! ����!!
			{
				printf("found %d number is %d \n", right, numbers[_pivot]);
				return;
			}
			else
			{
				//�ϴ� pivot �� right �� ��ġ�� �ٲٰ�,
				int temp = numbers[_pivot];
				numbers[_pivot] = numbers[right];
				numbers[right] = temp;

				// ���� ã�����ϴ� _which�� right�� ��� �ʿ� �մ����� �˻�.
				if (_which < right) // ���ʸ� ã�ƺ���.
				{
					doSelection(_pivot, _pivot + 1, right - 1, _which);
				}
				else // �����ʸ� ã�ƺ���.
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