#include<stdio.h>

void printall(int *tobedisplayed, int size) //배열에 있는 값을 처음부터 하나씩 보여준다
{
   int i;
   for (i = 0; i < size; i++)
   {
      printf("%d ", tobedisplayed[i]);
   }
   printf("\n");
}
void swap(int *arr, int idx1, int idx2) //서로 바꾸는 함수
{
   int temp = arr[idx1];
   arr[idx1] = arr[idx2];
   arr[idx2] = temp;
}
void performbubblesort(int *tobesorted, int sz)
{
   int i, j;
   for (i = 0; i < sz; i++)
   {
      for (j = 0; j < sz - 1 - i; j++)
      {
         if (tobesorted[j] > tobesorted[j + 1]) //현재상태와 현재다음상태 중 현재가 더크면 바꿔준다
         {
            //j <--> j+1
            swap(tobesorted, j, j + 1);
         }
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

   performbubblesort(data, 10);

}