#include<stdio.h>
#pragma warning(disable:4996)

/*
// 1. �ƽ�Ű �ڵ� - �ƽ�Ű �ڵ�� ������ Ÿ�Կ��ٰ� ���� �� �ְ� char �� 0-9 ���� �����
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

// 2. a ��� ������ �ִµ� 4��° ��Ʈ�� 0���� �ƴ��� �Ǵ��ϴ� ��
//	  -������ 1��° ��Ʈ
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
//3. 2���� �Լ��� ���� �����
bool nthbitOne(int x, int y) // x��� ���ڿ��� y��° ��Ʈ�� 1���� Ȯ���ϴ� ��
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
printf("1��\n");
else
printf("�ƴ�\n");

return 0;
}
*/

/*
// 4. String 
//		- apple �̶�� �ܾ�� �� �� ���Դ°�?
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
//array Ư¡ : �޸𸮸� �������� ��´�. 
//heap ! 
// ** �߿��� ���� Array �� Linked List , Heap **

int main()
{
	int a[5];
	for (int i = 0; i < 5; i++) // �ּ� ����غ��� -> �ּҰ� ����Ǿ��ִ�.
		printf("%d    ",&a[i]);

	return 0;
}
*/

/*
//���� ����
//int a[5]
//
//���� �ϸ�
//���⿡ interface�� �����Ѵ�.
//�����ϴ� interface��
//add : a �迭�� ���� �߰�
//delete " a�迭�� ���� ����
//contains : y ���� �迭�� �ִ��� ���� Ȯ��
//find : �� ��° ��ġ�� �ִ���
//size : ���� item �� ����


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
		printf("������ �ȵ����տ�\n");
}

void Delete()
{
	if (cur_size)
	{
		cur_size--;
		Array[cur_size] = 0;
	}
	else
		printf("������ ���ڰ� �����ϴ�.\n");
}

bool Contains(int _a)
{
	for (int i = 0; i < cur_size; i++)
	{
		if (Array[i] == _a)
		{
			printf("�ֽ��ϴٿ� \n");
			return true;
		}
	}
	printf("�����ϴٿ�\n");
	return false;
}

int Find(int _a)
{
	for (int i = 0; i < cur_size; i++)
	{
		if (Array[i] == _a)
		{
			printf("�ֽ��ϴٿ� %d \n",i);
			return i;
		}
	}
	printf("�����ϴٿ�\n");
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