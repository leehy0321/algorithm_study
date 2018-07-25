
#include<stdio.h>
#pragma warning(disable:4996)

/*
// 비트당 1의 갯수 찾기
int main()
{
	int count = 0;
	char num = 3;

	for (int i = 0; i < 8; i++)
	{
		if (num & 1)
			count++;
		num=(num >> 1);
	}

	printf("%d\n", count);
	return 0;

}*/

// 알고리즘 : 문제 / 알고리즘 / stack Queue Tree Graph / Array Linked list
// leetcode.com -> easy 부분만 다 풀어도 된다. Google 이나 해외쪽 문제들 같은 어려운것은 medium
// 


/*
//CircularQueue
//1.배열 : array[3], top, tail
//2.방법 :
//	Enqueue
//	Top 과 tail 의 위치 확인->full 이 아니면 아래 실행
//	Tail + 1 을 하면서 수 추가.
//	Dequeue
//	Top 과 tail 의 위치 확인->empty 가 아니면 아래 실행
//	Top - 1 을 하면서 수 출력
#define SIZE 3
int Array[SIZE], top=0, tail=0;

void enqueue(int val)
{
	if ( (tail + 1) % SIZE == top) //full
		printf("꽉차서 안됩니다.");
	else
	{
		Array[tail] = val;
		tail = (tail + 1) % SIZE;
	}
}

void dequeue()
{
	if (tail == top) // Empty
		printf("비어서 안됩니다.");
	else
	{
		printf("%d \n", Array[top]);
		Array[top] = 0;
		top = (top + 1) % SIZE;
	}
}
int main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	dequeue();
	dequeue();
	dequeue();


	return 0;
}*/

//==================================================================
//==========                Recursion            ===================
//===================================================================

/*
//n까지의 숫자의 합 -> Recursionn
// input : 
int sum(int n)
{
	if (n == 1)
		return 1;
	else
		return sum(n - 1) + n;
}
int main()
{
	printf("%d", sum(3));
	return 0;
}*/

/*
//입력된 문자열을 역순으로 출력하기
void recursion_print(char s[],int size)
{
	if (size == 0)
		return;

	printf("%c", s[size-1]);
	recursion_print(s, size - 1);
}
int main()
{
	char s[] = "123";
	
	recursion_print(s, sizeof(s) - 1);
	return 0;
}*/

//2^5 / 2^7승 부르는 것을 recursion 으로 해보시길
/*int multi(int x, int n)
{
	if (n == 0)
		return 1;
	return x * multi(x, n - 1);
}
int main()
{
	printf("%d\n", multi(2, 3));
	return 0;
}*/

/*
// 배열의 합 Recursion 으로 구하기
int re_sum(int ar[], int size)
{
	if (size == 0)
	{
		return ar[size];
	}
	return ar[size]+re_sum(ar,size-1);
}
int main()
{
	int Array[] = { 11,12,13,14,15 };
	printf("%d", re_sum(Array, (sizeof(Array) / sizeof(int))-1));
	return 0;
}*/

/*
//정수를 2진수로 표현하ㅣ

int main()
{
	return 0;
}*/

/*
//==================================================================
//==========                Tree                  ===================
//===================================================================
// 1. Node 구성 - 정의
// 2. Node 4개만 변수로 만들어주세요 -> n1 , n2 , n3 , n4
// 3. Node : val, left, right

#include<stdlib.h>

struct Tree {
	struct Node *root;
};
struct Node {
	int val;
	struct Node *left;
	struct Node *right;
};

struct Nooe* array_node[4];

int top, tail;

void display_tree(struct Node* root) {
	printf("%d\n", root->val);
	printf("%d     %d\n", root->left->val, root->right->val);
	printf("%d     \n", root->left->left->val);
}

int main()
{
	Node *n1, *n2, *n3, *n4;
	n1 = (struct Node*)malloc(sizeof(struct Node));
	n2 = (struct Node*)malloc(sizeof(struct Node));
	n3 = (struct Node*)malloc(sizeof(struct Node));
	n4 = (struct Node*)malloc(sizeof(struct Node));
	Tree tree;

	n1->val = 1;

	n2->val = 2;
	n2->right = NULL;

	n3->val = 3;
	n3->left = NULL;

	n4->val = 4;
	n4->right = NULL;

	tree.root = n1;
	n1->left = n2;
	n2->left = n4;
	n1->right = n3;

	display_tree(n1);
	//
	//root부터 시작
	//	loop
	//	- queue가 empty면 종료
	//	- queue가 empty가 아니면
	//		 queue에서 pop을 해서 현재 node로 
	//		 값을 출력
	//		 queue에 현재 node의 자식(들)을 enqueue
	//


	return 0;
}*/

/*화영쓰 방법 ↑
#include<iostream>
#include<queue>
using namespace std;

struct node {
int v;
struct node* left=NULL;
struct node* right=NULL;
};

struct Tree {
struct node* root;
};

queue<struct node*> q;
struct node* cur;

void display_tree(struct node* root);
void dfs(struct node* cur);

int main(void) {
//
////struct node* n1 = (struct node*)malloc(sizeof(struct node));
////struct node* n2 = (struct node*)malloc(sizeof(struct node));
////struct node* n3 = (struct node*)malloc(sizeof(struct node));
////struct node* n4 = (struct node*)malloc(sizeof(struct node));
//n1->v = 1;
//n2->v = 2;
//n3->v = 3;
//n4->v = 4;
//
//n1->left = NULL;
//n2->left = NULL;
//n3->left = NULL;
//n4->left = NULL;
//n1->right = NULL;
//n2->right = NULL;
//n3->right = NULL;
//n4->right = NULL;
//
struct node n1, n2, n3, n4;

n1.v = 1;
n2.v = 2;
n3.v = 3;
n4.v = 4;

struct Tree tree;
tree.root = &n1;

n1.left = &n2;
n1.right = &n3;
n2.left = &n4;

//display_tree(tree.root);

//bfs
//q.push(tree.root);
//bfs();

dfs(tree.root);
return 0;
}

void bfs() {
	while (!q.empty()) {
		cur = q.front();  // 반환
		q.pop(); // 지우기
		cout << cur->v << " ";
		if (cur->left != NULL) {
			q.push(cur->left);
		}
		if (cur->right != NULL) {
			q.push(cur->right);
		}
	}
}

//recursive 방식으로 구현
// pre-Order, In-Order, Post-Order
void dfs(struct node* cur) {
	//Pre-Order
	cout << cur->v << " ";
	if (cur->left != NULL) dfs(cur->left);
	if (cur->right != NULL) dfs(cur->right);
}

void display_tree(struct node* root) {
	printf("%d\n", root->v);
	printf("%d     %d\n", root->left->v, root->right->v);
	printf("%d     \n", root->left->left->v);
}*/


/*
// BST + insert
#include<stdlib.h>

struct Node {
	int val;
	struct Node *left;
	struct Node *right;
};

struct Node* head;

void insert(Node *_new)
{
	struct Node *cur;
	struct Node *cur2;
	cur = head;
	cur2 = head;
	int  _val = _new->val;
	bool flag;
	while (cur != NULL)
	{
		if (cur->val > _val)
		{
			cur2 = cur;
			cur = cur->left;
			flag = 1;
		}
		else if (cur->val < _val)
		{
			cur2 = cur;
			cur = cur->right;
			flag = 0;
		}
	}
	if (flag)
		cur2->left = _new;
	else
		cur2->right = _new;
}
bool search(int _val)
{
	struct Node *cur;
	cur = head;
	
	while (cur != NULL)
	{
		if (cur->val > _val)
			cur = cur->left;
		else if (cur->val < _val)
			cur = cur->right;
		else if (cur->val == _val)
		{
			printf("%d        ", cur->val);
			return true;
		}
	}
	return false;
	
}

int main()
{
	Node *n1, *n2, *n3, *n4, *nn;
	n1 = (struct Node*)malloc(sizeof(struct Node));
	n2 = (struct Node*)malloc(sizeof(struct Node));
	n3 = (struct Node*)malloc(sizeof(struct Node));
	n4 = (struct Node*)malloc(sizeof(struct Node));
	
	nn = (struct Node*)malloc(sizeof(struct Node));
	nn->val = 3;
	nn->left = NULL;
	nn->right = NULL;

	head = n1;

	n1->val = 10;

	n2->val = 5;
	n2->right = NULL;

	n3->val = 15;
	n3->left = NULL;

	n4->val = 1;
	n4->right = NULL;

	n1->left = n2;
	n2->left = n4;
	n1->right = n3;

	insert(nn);

	if (search(3))
		printf("3찾음\n");

	return 0;
}*/

//==================================================================
//==========               Hash                  ===================
//===================================================================

/*
#include<stdlib.h>

struct HashTable {
	int num;
	const char *phone;
	const char *name;
};

struct HashTable *students[10];// 10명의 학생의 정보 -> DB

int hash(int n)
{
	return n % 10;
}
int main()
{
	//n4 = (struct Node*)malloc(sizeof(struct Node));
	struct HashTable  *s1= (struct HashTable*)malloc(sizeof(struct HashTable));
	s1->num = 2014001;
	s1->name = "홍길동";

	students[hash(s1->num)] = s1;

	printf("%d , %s\n", students[1]->num, s1->name);
	return 0;
}*/

/*int main()
{
	return 0;
}*/