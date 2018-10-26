
#include<stdio.h>
#include<stdlib.h>
#include<string.h>//memcpy

#pragma warning(disable:4996)

#define SZ 10

int data[SZ] = { 34, 32, 2, 3, 0, 1, 8, 10, 99, 7 };

void showData(int *_data)
{
	for (int i = 0; i < SZ; i++)
	{
		printf("%d  ->  ", _data[i]);
	}
}

int doMerge(int *copied_data, int f_s, int f_e, int s_s, int s_e, int dst_idx)
{
	int f = f_s; // first_start
	int s = s_s; // second_start

	while (f <= f_e && s <= s_e) // ���߿� �ϳ��� ������ �������� ������� �ٿ��ָ� �ȴ�.
	{
		if (data[f] <= data[s])
		{
			copied_data[dst_idx] = data[f];
			f++;
			dst_idx++;
		}
		else
		{
			copied_data[dst_idx] = data[s];
			s++;
			dst_idx++;
		}
	}

	// ��/���� ���� ���ڰ� ���� �ִ� ���,
	// ���� ���� ��� �����ؼ� ���δ�.
	while (f <= f_e) // ��
	{
		copied_data[dst_idx] = data[f];
		f++;
		dst_idx++;
	}
	while (s <= s_e) // ��
	{
		copied_data[dst_idx] = data[s];
		s++;
		dst_idx++;
	}

	//������ ����, ���� ���� ��ġ�� ��ȯ�Ѵ�.
	return dst_idx;
}

int main()
{
	printf("-----------------------------before merge sorting-----------------------------\n");
	showData(data);
	
	//data�� copy���� �ϳ� �����.
	int *copied_data = (int *)malloc(sizeof(int)*SZ);
	memcpy(copied_data, data, sizeof(int)*SZ);

	int step = 1; // ���� 1��¥�� ������ ����
	int dst_idx = 0;//���� ��ġ�� 0���� ����

	while (1)
	{
		if (step >= SZ)
		{
			break;
		}
		for (int i = 0; i < SZ; i=i+step*2)
		{
			int _f_s = i;
			int _f_e = i+step-1;
			int _s_s = i+step;
			int _s_e = i+(step*2)-1;

			//Size�� �� �ȳ����� ���������� ����ó�� ���ش�.
			if (_f_e >= SZ - 1) // merge�� ���� �� ��� �ۿ� ����.
			{
				break;
			}

			if (_s_e > SZ - 1)
			{
				_s_e = SZ - 1;
			}

			dst_idx = doMerge(copied_data, _f_s, _f_e, _s_s, _s_e, dst_idx);
		}

		step = step * 2;
		dst_idx = 0;
		memcpy(data, copied_data, SZ * sizeof(int));
	}
	printf("\n\n-----------------------------after merge sorting-----------------------------\n");
	showData(data);
	printf("\n");
	return 0;
}