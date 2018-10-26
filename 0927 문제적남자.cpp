#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#define SZ 9 // 0�� �ǵڿ� ������ �����ϱ� �ϳ� ���� ����Ѵ�. <- �ֳ��ϸ� int �ִ� ũ�Ⱑ 21�� �̱� ����

int numbers[SZ];

void initNumbers(void)
{
	for (int i = 0; i < SZ; i++)
	{
		numbers[i] = -1;
	} //���� �����̶� ��ȣ�� �� �ľ��մϴ� ... !!! 
}

int makeNumbers(int idx) // �迭 -> ���ڷ� �ٲ��ش�.
{
	// numbers = {1,2,3,-1,-1,...} => 123 ���� ������ִ� ����~

	int sum = numbers[0];
	for (int i = 1; i <= idx; i++)
	{
		sum = sum * 10 + numbers[i];
	}
	return sum;
}

// idx ��ġ�� v��� ���ڸ� �ִ´�.
// �׸���
// �ű���� ������� ���ڰ� ���ǿ� �´����� �˻��Ѵ�.
void checkNumber(int v, int idx)
{

	/*
	0. ���ڸ� ���� �ִ´�.
	*/
	numbers[idx] = v;

	/* 
	   1. idx�տ� v�� ��ġ�� ���ڰ� �ִ��� �˻��Ѵ�.
	.				-> �����ϸ� return
	*/
	for (int i = 0; i < idx; i++)
	{
		if (numbers[i] == v)
		{
			return;
		}
	}

	/*  
	   2. numbers[0,....idx]���� ���ڰ� '����'�� �����ϴ��� �˻��Ѵ�.
					-> �����ϸ� return
	*/
	if (makeNumbers(idx) % (idx + 1) != 0)
	{
		return;
	}

	/*
	Ż������
	*/
	if (idx == 8)
	{
		printf("The NUMBER is %d\n", makeNumbers(8));
		return;
	}



	/*
	3. 1���� 2�� ������ ������ ����ߴٸ�
					-> ���� �ܰ�� ����
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