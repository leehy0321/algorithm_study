#include<stdio.h>

void printall(int *tobedisplayed, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d ", tobedisplayed[i]);
	}
	printf("\n");
}
void swap(int *arr, int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}
void performinsertionsort(int *tobesorted, int sz)
{
	int i;

	for (i = 1; i < sz; i++)
	{
		int j = i;

		while (((j - 1) >= 0) && tobesorted[j - 1]>tobesorted[j])
		{
			swap(tobesorted, j - 1, j);
			j = j - 1; //=j--
		}
		printall(tobesorted, 10);
	}
}
void main(void)
{
	int data[10] = { 31, 24, 56, 1, 4, 10, 6, 76, 87, 30 };

	printf("-------------------------------\n");
	printf("Before being sorted\n");
	printall(data, 10);
	printf("-------------------------------\n");

	performinsertionsort(data, 10);
}