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
int findsmallest(int *arr, int start_idx, int sz) //���� ���� ���� ã�� �Լ�
{
   int smallest_idx = start_idx;
   int smallest = arr[start_idx];
   int i;

   for (i = start_idx; i < sz; i++)
   {
      if (arr[i] < smallest)
      {
         smallest = arr[i]; //���� ���� ���� ����
         smallest_idx = i; //���� ���� ���� ��ȣ�� ����
      }
   }
   return smallest_idx; //���� ���� ���� ��ȣ�� ���
}
void performselectionsort(int *tobesorted, int sz)
{
   int i, j;
   for (i = 0; i < sz; i++)
   {
      //���� ���� ���� ã��, �װ��� �������� �̵�
      j = findsmallest(tobesorted, i, sz);
      swap(tobesorted, i, j);
      printall(tobesorted, sz);
   }
}
void main(void)
{
   int data[10] = { 31, 24, 56, 1, 4, 10, 6, 76, 87, 30 };

   printf("-------------------------------\n");
   printf("Before being sorted\n");
   printall(data, 10);
   printf("-------------------------------\n");

   performselectionsort(data, 10);
}