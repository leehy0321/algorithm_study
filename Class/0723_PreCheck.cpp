#include<stdio.h>
#pragma warning(disable:4996)

/*
// 1. 아스키 코드 - 아스키 코드로 정수형 타입에다가 숫자 를 넣고 char 로 0-9 까지 찍어볼까용
int main()
{
int a = 48;

for (int i = 0; i < 10; i++)
{
printf("%c\n", a + i);
}

return 0;
}
*/

// 2. a 라는 정수가 있는데 4번째 비트가 0인지 아닌지 판단하는 것
//	  -시작이 1번째 비트
/*int main()
{
int a = 11;
int checkbit = 1;

checkbit << 3;

if (a & checkbit)
printf("1");
else
printf("0");

return 0;
}*/

/*
//3. 2번을 함수로 따로 만들기
bool nthbitOne(int x, int y) // x라는 숫자에서 y번째 비트가 1인지 확인하는 것
{
int checkbit = 1;

if (x & (1 << (y - 1)))
return true;
else
return false;
}
int main()
{
if (nthbitOne(11, 4))
printf("1임\n");
else
printf("아님\n");

return 0;
}
*/

/*
// 4. String 
//		- apple 이라는 단어는 몇 번 나왔는가?
//		- 1. 
#include <string.h>
int main()
{
	char s[] = "apple is apple is apple";

	printf("%d ", strcmp(s, "apple"));
	return 0;
}

*/

/*
//array 특징 : 메모리를 연속으로 잡는다. 
//heap ! 
// ** 중요한 것은 Array 와 Linked List , Heap **

int main()
{
	int a[5];
	for (int i = 0; i < 5; i++) // 주소 출력해보기 -> 주소가 연결되어있다.
		printf("%d    ",&a[i]);

	return 0;
}
*/

/*
//문제 정의
//int a[5]
//
//정의 하며
//여기에 interface를 제공한다.
//제공하는 interface는
//add : a 배열에 값을 추가
//delete " a배열의 값을 삭제
//contains : y 값이 배열에 있는지 여부 확인
//find : 몇 번째 위치에 있는지
//size : 현재 item 의 갯수


#define SIZE 5
int cur_size;
int Array[5];

void Add(int _a)
{
	if (cur_size < 5)
	{
		Array[cur_size] = _a;
		cur_size++;
	}
	else
		printf("꽉차서 안되지롱여\n");
}

void Delete()
{
	if (cur_size)
	{
		cur_size--;
		Array[cur_size] = 0;
	}
	else
		printf("제거할 숫자가 없습니다.\n");
}

bool Contains(int _a)
{
	for (int i = 0; i < cur_size; i++)
	{
		if (Array[i] == _a)
		{
			printf("있습니다용 \n");
			return true;
		}
	}
	printf("없습니다용\n");
	return false;
}

int Find(int _a)
{
	for (int i = 0; i < cur_size; i++)
	{
		if (Array[i] == _a)
		{
			printf("있습니다용 %d \n",i);
			return i;
		}
	}
	printf("없습니다용\n");
	return -1;
}

int Size()
{
	return cur_size;
}

int main()
{
	Add(1);
	Add(2);
	Add(3);
	Add(4);
	Add(5);
	Find(3);
	Find(6);
	Contains(3);
	Contains(6);
	Delete();
	Delete();
	printf("%d\n",Size());

	return 0;
}
*/

//Stack
/*

#include <stdlib.h>

struct node{
	int val;
	struct node *next;
};

struct node *cur;

void add(int _v)
{

}
int main()
{
	
	return 0;
}*/

//Queue
#include <stdlib.h>

struct node {
	int val;
	struct node *pre;
	struct node *next;
};

struct node *cur;

void enqueue(int _v)
{

}
int main()
{

	return 0;
}