;/*
 K == 1 -> 1���� tree => BST
 K == 2 -> 2���� 
 */
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int HowManyNode(struct node *cur); // SLL�� ��尡 ��ΰ�?
void doBubbleSort(struct node ** _array, int _byX, int _size);
struct node* rebuildSLL(struct node** _array, int from, int to);

struct node {
	int x;
	int y;
	struct node *next;
};

struct node *head = 0;

//kd-tree�� ��� ����ü�� ����
struct kdtree_node {
	struct node *data;
	struct kdtree_node *left;
	struct kdtree_node *right;
};

//kd_tree�� root�� ����Ű�� root pointer
struct kdtree_node *kd_root = 0;

//kd_tree�� �����س��� �Լ�
// ��ȯ : ������ kdtree node�� �ּҸ� ��ȯ�Ѵ�.
// �Է� : kdtree�� �� linked list
//        depth ���� : x�� Ȥ�� y�࿡ ���ؼ� ���� ����,,
//		  dimension : �������� ����, 
struct kdtree_node *build_kdtree(struct node *sll, 
								int _depth, 
								int _dimension)
{
	//Ż������
	if (sll == 0) //sll �� ���� ��� 
		return 0;


	// 1, SLL ������ �ּҸ� Array�� �����Ѵ�.
	//					-> ������ �˾ƾ���!!!
	int numSLLNodes = HowManyNode(sll);

	//��� �ּҵ��� ���� array�� �Ҵ��Ѵ�.
	struct node ** nodeAddArray = (struct node**)malloc(sizeof(struct node*)*numSLLNodes);

	//array�� �ٰ� ��� �ּҵ��� �ϳ��� �ִ´�.
	int i;
	struct node *temp = sll; // �ϳ��� �����̸鼭 �� ����
	for (i = 0; i < numSLLNodes; i++)
	{
		nodeAddArray[i] = temp;
		temp = temp->next;
	}

	//x�� Ȥ�� y�࿡ ���Ͽ� �����ϴ��� ����
	int axis = _depth % _dimension;
	
	//nodeAddArray�� �̿��ؼ� sorting �Ѵ�.
	doBubbleSort(nodeAddArray, !axis, numSLLNodes); // �ȿ����� x->1�� �آZ�⶧���� !axis�� ���ִ°�

	int _median = numSLLNodes / 2; // �߰��� �� ��Ҵ�.
	
	struct kdtree_node *cur = (struct kdtree_node *)malloc(sizeof(struct kdtree_node*));
	cur->data = nodeAddArray[_median];
	//cur->left = build_kdtree(left_sll, _depth+1, 2);
	cur->left = build_kdtree(rebuildSLL(nodeAddArray,0,_median-1), _depth + 1, 2);

	//cur->right = build_kdtree(right_sll, _depth + 1, 2)
	cur->right = build_kdtree(rebuildSLL(nodeAddArray, _median+1, numSLLNodes-1), _depth + 1, 2);
	
	//**
	free(nodeAddArray); // �ٛ����ϱ� free ���Ѿߵ˴ϴٿ�!!
	
	return cur;


	//����
	//nodeAddArray�� �̿��ؼ� SLL������ ���� ��� ��� 
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

	if (from > to) // Ż�� ���� -> from�� �׻� �۾ƾߵǴµ� �ƴϸ� null
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
//array�� ��� �ּҵ��� xȤ��  y���� ���� ������������ ����
// _byX = 1 ; -> x�� ���ؼ� ����
//	   = 0 ; -> y�� ���ؼ� ����
// _size : array�� ����
void doBubbleSort(struct node ** _array, int _byX, int _size)
{
	int i = 0;
	int j = 0;
	struct node *temp = 0;

	for (j = 0; j < _size; j++)
	{
		for (i = 0; i < _size - 1 -j; i++) //*******_size-1-j �� �ٽ�********
		{
			if (_byX == 1) // -> x�� ���Ͽ� ��
			{
				if (_array[i]->x > _array[i + 1]->x)
				{
					temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
			else // -> y�� ���ؼ� ��
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

int HowManyNode(struct node *cur) // SLL�� ��尡 ��ΰ�?
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

	//kd_root = build_kdtree(head, 0, 2); // head = ��� node�� ���� �� ������ �ִ�.
	build_kdtree(head, 0, 2);

	printf("%d, %d\n", kd_root->data->x, kd_root->data->y);
	return 0;

}