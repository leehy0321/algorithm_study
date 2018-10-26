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


// _pivot : �Ǻ��� �ε���
// _letf : L�� ������ġ
// _right : R�� ������ġ
void qsort(int _pivot, int _left, int _right)
{
	// recursive :: Ż������ ..... ���߿� ����
	if (_pivot < 0 || _pivot >= SZ
	    || _left < 0 || _left >= SZ
		|| _right < 0 || _right >= SZ)
	{
		return;
	}

	if (_pivot > _left) // _pivot�� _left���� ���ʿ� �վ��
	{
		return;
	}

	if (_left > _right)//_left �� _rignt ���ٴ� �׻� ���ʿ��� ����
	{
		return;
	}
	// l�� R�� ������Ѿ� �ϱ� ������ ���縦 �س��´�.
	int l = _left;
	int r = _right;

	//�ݺ�
	while (1)
	{
		//while :: Ż������
		
		//L�� �̵�
		while (numbers[_pivot] > numbers[l])
		{
			l++;
		}
		//R�� �̵�
		while (numbers[_pivot] < numbers[r])
		{
			r--;
		}

		//L < R ������ ����!
		if (l < r)
		{
			change_number(l, r);
		}
		else //L > R ������ recursive �� �Ŀ� ����!
		{
			//pivot�ϰ� �ٲ�ġ��, 
			change_number(r, _pivot);

			//recursive�ϰ�, 
			qsort(_pivot,_pivot+1,r-1);// ����
			qsort(r + 1, r + 2, _right);
			//����!
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
