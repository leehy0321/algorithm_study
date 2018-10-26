;/*
 K == 1 -> 1차원 tree => BST
 K == 2 -> 2차원 
 */
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int HowManyNode(struct node *cur); // SLL의 노드가 몇개인가?
void doBubbleSort(struct node ** _array, int _byX, int _size);
struct node* rebuildSLL(struct node** _array, int from, int to);

struct node {
	int x;
	int y;
	struct node *next;
};

struct node *head = 0;

//kd-tree의 노드 구조체를 정희
struct kdtree_node {
	struct node *data;
	struct kdtree_node *left;
	struct kdtree_node *right;
};

//kd_tree의 root를 가리키는 root pointer
struct kdtree_node *kd_root = 0;

//kd_tree를 생성해내는 함수
// 반환 : 생성된 kdtree node의 주소를 반환한다.
// 입력 : kdtree에 들어갈 linked list
//        depth 정보 : x축 혹은 y축에 대해서 비교할 정보,,
//		  dimension : 데이터의 차원, 
struct kdtree_node *build_kdtree(struct node *sll, 
								int _depth, 
								int _dimension)
{
	//탈출조건
	if (sll == 0) //sll 이 없을 경우 
		return 0;


	// 1, SLL 노드들의 주소를 Array에 저장한다.
	//					-> 갯수를 알아야지!!!
	int numSLLNodes = HowManyNode(sll);

	//노드 주소들을 담을 array를 할당한다.
	struct node ** nodeAddArray = (struct node**)malloc(sizeof(struct node*)*numSLLNodes);

	//array에 다가 노드 주소들을 하나씩 넣는다.
	int i;
	struct node *temp = sll; // 하나씩 움직이면서 할 아이
	for (i = 0; i < numSLLNodes; i++)
	{
		nodeAddArray[i] = temp;
		temp = temp->next;
	}

	//x축 혹은 y축에 대하여 소팅하는지 결정
	int axis = _depth % _dimension;
	
	//nodeAddArray를 이용해서 sorting 한다.
	doBubbleSort(nodeAddArray, !axis, numSLLNodes); // 안에서는 x->1로 해줫기때문에 !axis를 해주는것

	int _median = numSLLNodes / 2; // 중간을 딱 잡았다.
	
	struct kdtree_node *cur = (struct kdtree_node *)malloc(sizeof(struct kdtree_node*));
	cur->data = nodeAddArray[_median];
	//cur->left = build_kdtree(left_sll, _depth+1, 2);
	cur->left = build_kdtree(rebuildSLL(nodeAddArray,0,_median-1), _depth + 1, 2);

	//cur->right = build_kdtree(right_sll, _depth + 1, 2)
	cur->right = build_kdtree(rebuildSLL(nodeAddArray, _median+1, numSLLNodes-1), _depth + 1, 2);
	
	//**
	free(nodeAddArray); // 다썻으니까 free 시켜야됩니다요!!
	
	return cur;


	//검증
	//nodeAddArray를 이용해서 SLL노드들의 값을 모두 출력 
	/*
	for (i = 0; i < numSLLNodes; i++)
	{
		int _x = nodeAddArray[i]->x;
		int _y = nodeAddArray[i]->y;

		printf("%d, %d \n", _x, _y);
	}*/

	
}

struct node* rebuildSLL(struct node** _array, int from, int to)
{

	if (from > to) // 탈출 조건 -> from이 항상 작아야되는데 아니면 null
		return 0;

	struct node *cur = _array[from];
	cur->next = 0;
	struct node *temp = cur;

	for (int i = from + 1; i <= to; i++)
	{
		temp->next = _array[i];
		temp->next->next = 0;
		temp = temp->next;
	}

	return cur;
}
//array에 담긴 주소들을 x혹은  y값에 따라 오름차순으로 정렬
// _byX = 1 ; -> x에 대해서 소팅
//	   = 0 ; -> y에 대해서 소팅
// _size : array의 길이
void doBubbleSort(struct node ** _array, int _byX, int _size)
{
	int i = 0;
	int j = 0;
	struct node *temp = 0;

	for (j = 0; j < _size; j++)
	{
		for (i = 0; i < _size - 1 -j; i++) //*******_size-1-j 가 핵심********
		{
			if (_byX == 1) // -> x에 대하여 비교
			{
				if (_array[i]->x > _array[i + 1]->x)
				{
					temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
			else // -> y에 대해서 비교
			{
				if (_array[i]->y > _array[i + 1]->y)
				{
					temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
		}
	}
}

void addToSLL(int _x, int _y)
{
	struct node *newone = (struct node *)malloc(sizeof(struct node));
	newone->x = _x;
	newone->y = _y;
	newone->next = 0;

	if (head == 0)
	{
		head = newone;
	}
	else {
		struct node *temp = head;

		while(!temp ->next == 0)
		{
			temp = temp->next;
		}
		temp->next = newone;
	}
}

int HowManyNode(struct node *cur) // SLL의 노드가 몇개인가?
{
	//struct node *cur = head;
	int cnt = 0;
	while (cur != 0)
	{
		cnt++;
		cur = cur->next;
	}
	return cnt;
}

int main()
{
	addToSLL(5, 54);
	addToSLL(1, 14);
	addToSLL(6, 64);
	addToSLL(2, 24);
	addToSLL(4, 44);
	addToSLL(3, 34);

	//printf("%d\n", HowManyNode(head));

	//kd_root = build_kdtree(head, 0, 2); // head = 모든 node의 값을 다 가지고 있다.
	build_kdtree(head, 0, 2);

	printf("%d, %d\n", kd_root->data->x, kd_root->data->y);
	return 0;

}