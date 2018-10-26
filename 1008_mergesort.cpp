
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

	while (f <= f_e && s <= s_e) // 둘중에 하나가 끝나면 나머지를 순서대로 붙여주면 된다.
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

	// 앞/뒤의 블럭에 숫자가 남아 있는 경우,
	// 남은 것을 모두 복사해서 붙인다.
	while (f <= f_e) // 앞
	{
		copied_data[dst_idx] = data[f];
		f++;
		dst_idx++;
	}
	while (s <= s_e) // 뒤
	{
		copied_data[dst_idx] = data[s];
		s++;
		dst_idx++;
	}

	//종료할 때는, 다음 붙일 위치를 반환한다.
	return dst_idx;
}

int main()
{
	printf("-----------------------------before merge sorting-----------------------------\n");
	showData(data);
	
	//data의 copy본을 하나 만든다.
	int *copied_data = (int *)malloc(sizeof(int)*SZ);
	memcpy(copied_data, data, sizeof(int)*SZ);

	int step = 1; // 길이 1개짜리 블럭부터 시작
	int dst_idx = 0;//복사 위치는 0부터 시작

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

			//Size가 딱 안나누어 떨어질때는 예외처리 해준다.
			if (_f_e >= SZ - 1) // merge할 것이 한 덩어리 밖에 없다.
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