#include<stdio.h>

#pragma warning(disable:4996)

#define SIZE 10

int data[SIZE] = { 10,11,7,13,5,16,2,12,6 };

void change_number(int a, int b)
{
	int copy = data[a];
	data[a] = data[b];
	data[b] = copy;
}

void sort(int pivot, int left, int right)
{
	while(1)
	{
		if (pivot + 1 > SIZE || pivot + 2 > SIZE)
			return;

		if (right < left)
		{
			int cpy = pivot;
			sort(cpy + 1, cpy + 2, right-1);
			sort(left, left + 1, SIZE - 1);
		}
		if (data[left] < data[pivot])
		{
			left++;
		}
		else if (data[left] > data[pivot])
		{
			change_number(left, pivot);
		}
		if (data[right] > data[pivot])
		{
			right--;
		}
		else if (data[right] < data[pivot])
		{
			change_number(right, pivot);
		}
	}
}


int main()
{

	sort(0, 1, SIZE-1);

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d   ", data[i]);
	}
	return 0;

}
