#include<iostream>

using namespace std;

#define SIZE 9999

int binary[100][SIZE];
int flag = 0;

int changetobinary(int _fin_number)
{
	int size = 0; // ������ ���� ���ڸ��� 2�������� ������ ��
	
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
	int input;//�Է� ���� ���� ����
	int number=1; // ���� ������ �����ݴϴ�. 2�� ����̴ϱ� 1�� ó�� ���� �������ݴϴ�. -> 1�ڸ��� 0~1 / 2�ڸ��� 0~3 / 3�ڸ��� 0~7
	
	cin >> input; // ���ڸ� �Է¹޽��ϴ�.

	for (int i = 0; i < input; i++) // ������ ������ �������ֱ� ���� �ڸ� �� ��ŭ 2�� �����ݴϴ�.
	{
		number = number * 2;
	}

	double fin_number = 0; // 2������ �ٲٱ� �� ���� �ȿ� ��� ���� ������ ���� ��.
	
	//number--; // 2�� ����� �������� �ʾƾ��Ͽ�, 1�� ���ݴϴ�.

	/*while (number) // ���� ���� ������ֱ� ���� number ��ü�� �����ݴϴ�. 
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