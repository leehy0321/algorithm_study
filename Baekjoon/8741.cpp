#include<iostream>

using namespace std;

#define SIZE 9999

int binary[100][SIZE];
int flag = 0;

int changetobinary(int _fin_number)
{
	int size = 0; // 최종의 수가 몇자리의 2진수인지 리턴할 것
	
 	while (_fin_number > 1)
	{
		if (size == SIZE)
		{
			size = 0;
			flag++;
		}

		binary[flag][size] = _fin_number % 2;
		_fin_number = _fin_number / 2;
		size++;
	}

	binary[flag][size] = _fin_number;
	//size++;

	return size;
}
int main()
{
	int input;//입력 받을 숫자 변수
	int number=1; // 숫자 범위를 정해줍니다. 2의 배수이니까 1로 처음 값을 지정해줍니다. -> 1자리면 0~1 / 2자리면 0~3 / 3자리면 0~7
	
	cin >> input; // 숫자를 입력받습니다.

	for (int i = 0; i < input; i++) // 숫자의 범위를 지정해주기 위해 자리 수 만큼 2를 곱해줍니다.
	{
		number = number * 2;
	}

	double fin_number = 0; // 2진수로 바꾸기 전 범위 안에 모든 수를 더해준 최종 값.
	
	//number--; // 2의 배수는 포함하지 않아야하여, 1을 빼줍니다.

	/*while (number) // 최종 수로 만들어주기 위해 number 전체를 더해줍니다. 
	{
		fin_number = fin_number + number;
		number--;
	}*/

	fin_number = (number * (number - 1)) / 2;

	//cout << fin_number << endl;
	
	int size = changetobinary(fin_number);

	//cout << flag<< " :: " << size << endl;

	for (int i = 0; i < size + 1; i++)
	{
		cout << binary[flag][size - i];
	}

	for (int j = 1; j < flag; j++)
	{
		for (int i = 1; i < SIZE+1; i++)
		{
			cout << binary[flag - j][SIZE - i];
		}
	}
	cout << endl;
	return 0;
}