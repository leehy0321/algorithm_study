#include <iostream>
using namespace std;

int result = 999999;
void making_number_to_one(int number, int howtomake)
{
	//Recursive�� ���� �� �ִ� ����
	if (number < 1) // ���ǿ� ���� �ʴ´�.
	{
		return;
	}
	if (result < howtomake) // ���ݱ����� Ƚ���� �ּڰ����� ũ�� �ʿ䰡����.
	{
		return;
	}
	if (number == 1) // ������ ��� �����Ͽ� ���� ����.
	{
		result = howtomake;//�ּڰ��� ����
		return;
	}

	howtomake++;//������ ������ �� �� �ϰԵǴϱ� ������ �� �� �÷��ش�.

	//�־��� ���ǿ� �´� ó��
	//
	// ���ǿ� �°� �Ǹ� ������ �� ���� �־� ���� ����� �ϰ� �ȴ�.
	// ������ �ּڰ��� ���� �𸣴ϱ� ��� ��츦 ���캻��.
	//
	if (number % 3 == 0)
	{
		making_number_to_one(number / 3, howtomake);
	}

	if (number % 2 == 0)
	{
		making_number_to_one(number / 2, howtomake);
	}

	if (number > 1)
	{
		making_number_to_one(number-1, howtomake);
	}

}
int main()
{
	int input_number; // ����ڿ��� �Է¹��� ����
	cin >> input_number;//����ڿ��� �Է��� �޴´�.

	making_number_to_one(input_number, 0);

	cout << result << endl;//���
	return 0;

}