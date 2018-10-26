#include <iostream>
using namespace std;

int result = 999999;
void making_number_to_one(int number, int howtomake)
{
	//Recursive를 끝낼 수 있는 조건
	if (number < 1) // 조건에 맞지 않는다.
	{
		return;
	}
	if (result < howtomake) // 지금까지의 횟수가 최솟값보다 크면 필요가없다.
	{
		return;
	}
	if (number == 1) // 조건을 모두 실행하여 끝이 났다.
	{
		result = howtomake;//최솟값을 정의
		return;
	}

	howtomake++;//들어오면 연산을 한 번 하게되니까 무조건 한 번 올려준다.

	//주어진 조건에 맞는 처리
	//
	// 조건에 맞게 되면 연산을 한 수를 넣어 다음 계산을 하게 된다.
	// 무엇이 최솟값이 될지 모르니까 모든 경우를 살펴본다.
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
	int input_number; // 사용자에게 입력받을 변수
	cin >> input_number;//사용자에게 입력을 받는다.

	making_number_to_one(input_number, 0);

	cout << result << endl;//출력
	return 0;

}