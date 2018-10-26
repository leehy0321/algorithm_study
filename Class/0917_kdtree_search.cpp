#include <stdio.h>
#include <stdlib.h>

struct node
{
	int x;
	int y;
	struct node *next;
};

struct node *head = 0;

// kd-tree�� root�� ����Ű�� root pointer
struct kdtree_node *kd_root = 0;

// kd-tree�� ��� ����ü�� ����
struct kdtree_node
{
	struct node *data;
	struct kdtree_node *left;
	struct kdtree_node *right;
};

// linked list�� ��尡 �� �� �ִ����� ���� �Լ�
int howManyNodes(struct node *_head)
{
	int cnt = 0;
	struct node *temp = _head;

	while (1)
	{
		if (temp == 0)
		{
			return cnt;
		}
		else
		{
			cnt++;
			temp = temp->next;
		}
	}
}

//
// array�� ��� �ּҵ��� x Ȥ�� y���� ���� ������������ ����
//
// _byX = 1: x�� ���ؼ� ����
//      = 0: y�� ���ؼ� ����
// _size: array�� ����
void doBubbleSort(struct node **_array, int _byX, int _size)
{
	int i = 0;
	int j = 0;

	for (j = 0; j < _size; j++)
	{
		for (i = 0; i < _size - 1 - j; i++)  // (0,1) (1,2), ......
		{
			if (_byX == 1)  // x�� ���ؼ� ��
			{
				if (_array[i]->x > _array[i + 1]->x)
				{
					// swap
					struct node *temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
			else            // y�� ���ؼ� ��
			{
				if (_array[i]->y > _array[i + 1]->y)
				{
					// swap
					struct node *temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
		}
	}
}

struct node *rebuildSLL(struct node **_array, int from, int to)
{
	if (from > to)
	{
		return 0;
	}
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

// kdtree�� �����س��� �Լ�
// ��ȯ: ������ kdtree node�� �ּҸ� ��ȯ�Ѵ�.
// �Է�: kdtree�� �� linked list
//       depth����: x�� Ȥ�� y�࿡ ���ؼ� ���� ����,,,
//       dimension: �������� ����, 2���� ���� ��� 2
struct kdtree_node *build_kdtree(struct node *sll,
	int _depth,
	int _dimension)
{
	if (sll == 0)
	{
		return 0;
	}
	// 1. SLL ������ �ּҸ� array�� �����Ѵ�.

	// SLL�� ��� ����� ������ �����´�.
	int numSLLNodes = howManyNodes(sll);

	// ��� �ּҵ��� ���� array�� �Ҵ��Ѵ�.
	struct node **nodeAddrArray = (struct node **)malloc(sizeof(struct node *)*numSLLNodes);

	// array�� �ٰ� ��� �ּҵ��� �ϳ��� �ִ´�.
	int i;
	struct node *temp = sll;
	for (i = 0; i < numSLLNodes; i++)
	{
		nodeAddrArray[i] = temp;
		temp = temp->next;
	}

	// ����
	// nodeAddrArray�� �̿��ؼ� SLL ������ ���� ��� ���
	//for (i = 0; i < numSLLNodes; i++)
	//{
	//	int _x = nodeAddrArray[i]->x;
	//	int _y = nodeAddrArray[i]->y;
	//	printf("%d, %d\n", _x, _y);
	//}

	// x�� Ȥ�� y�࿡ ���ؼ� �����ϴ��� ����
	int axis = _depth % _dimension;

	doBubbleSort(nodeAddrArray, !axis, numSLLNodes);

	int _median = numSLLNodes / 2;

	struct kdtree_node *cur = (struct kdtree_node *)malloc(sizeof(struct kdtree_node));
	cur->data = nodeAddrArray[_median];
	cur->left = build_kdtree(rebuildSLL(nodeAddrArray, 0, _median - 1), _depth + 1, 2);
	cur->right = build_kdtree(rebuildSLL(nodeAddrArray, _median + 1, numSLLNodes - 1), _depth + 1, 2);
	free(nodeAddrArray);

	return cur;

}

//return 1 if (1,4) is in kd-tree
//	     0 if not
int searchKdTree(struct kdtree_node *_root, int _x, int _y)
{
	struct kdtree_node *temp = _root;
	int axis = 0;

	while (1)
	{
		if (temp == 0) // (_x,_y)�� ã�� ������.
			return 0;

		// ���� ã���� �ϴ� ������ ��
		if (temp->data->x == _x && temp->data->y == _y)
			return 1;

		if (axis == 0) // compare x coordinates
		{
			if (temp->data->x > _x)
				temp = temp->left;
			else
				temp = temp->right;
		}
		else // axis =1 -> compare y coordinates
		{
			if (temp->data->y > _y)
				temp = temp->left;
			else
				temp = temp->right;
		}

		axis = (axis + 1) % 2;//axis �ٲ��ֱ�
	}
}


void addToSLL(int _x, int _y)
{
	// �����͸� ������ ��带 �����Ѵ�.
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->x = _x;
	new_one->y = _y;
	new_one->next = 0;

	// SLL�� new_one�� �߰��Ѵ�.
	if (head == 0)
	{
		head = new_one;
		return;
	}
	else  // SLL�� ���� ã�Ƽ� �ٿ��ִ´�.
	{
		struct node *temp = head;
		while (1)
		{
			if (temp->next == 0)  // �ǳ��� ã�� ���
			{
				temp->next = new_one;  // ���� �ٿ��ִ´�.
				return;
			}
			else // ���� �ǳ� ��尡 �ƴ� ���,
			{
				// �� ���� ���� �̵��Ѵ�.
				temp = temp->next;
			}
		}
	}
}

//(_x, _y)�� �־�������,
//axis�� ����Ͽ�
//_root�� leftȤ�� right�� ���������� ��ȯ
struct kdtree_node *whichWayToGo(struct kdtree_node *_root, int _x,int  _y, int axis)
{
	if (axis == 0)// x�� ��
	{
		if (_root->data->x > _x)
			return _root->left;
		else
			return _root->right;
	}
	else // y�� ��
	{
		if (_root->data->y > _y)
			return _root->left;
		else
			return _root->right;
	}
}

//_root�� leftȤ�� right�� ���������� ��ȯ
struct kdtree_node *whichWayNotToGo(struct kdtree_node *_root, int _x, int  _y, int axis)
{
	if (axis == 0)// x�� ��
	{
		if (_root->data->x > _x)
			return _root->right;
		else
			return _root->left;
	}
	else // y�� ��
	{
		if (_root->data->y > _y)
			return _root->right;
		else
			return _root->left;
	}
}

struct kdtree_node *RealNearestNeighbor(struct kdtree_node *_root, 
										int _x, int _y,
										int _minDiff,
									struct kdtree_node * _minDiffNode, int axis, int dim)
{
	//Ż������
	if (_root == 0)
		return _minDiffNode;

	
	//���� ������Ʈ
	if (_root->data->x == _x && _root->data->y == _y)
		return _root;

	else
	{
		//�󸶳� �ָ� �������ִ��� ���
		// _root���� �Ÿ� ���

		int dist = (_root->data->x - _x) *  (_root->data->x - _x) + (_root->data->y - _y)* (_root->data->y - _y);

		if (dist < _minDiff)
		{
			_minDiff = dist;
			_minDiffNode = _root;
		}

		//���� root�� ����, �����̵�, �������̵� ��������.
		struct kdtree_node *wayTo = whichWayToGo(_root, _x, _y, axis%dim);

		struct kdtree_node *NN
			= RealNearestNeighbor(wayTo, _x, _y, _minDiff, _minDiffNode, axis + 1, dim);

		//������ nearest neighbor������ �Ÿ��� ����.
		int dist_to_NN = (NN->data->x - _x)*(NN->data->x - _x) + (NN->data->y - _y)*(NN->data->y - _y);

		//nearest neighbor������ �Ÿ��� ��輱�� �Ѵ��� ����.
		if (axis%2 == 0) // x�࿡ ���Ͽ� �˻�
		{
			if (dist_to_NN > (_x - _root->data->x)*(_x - _root->data->x))
			{
				//��輱 ������ �������ߵȴ�.
				return RealNearestNeighbor(whichWayNotToGo(_root, _x, _y, axis%dim),
					_x, _y, _minDiff, _minDiffNode, axis + 1, dim);
			}
			else
				return NN;
		}
		else // y�࿡ ���ؼ� �˻�
		{
			if (dist_to_NN > (_y - _root->data->y)*(_x - _root->data->x))
			{
				//��輱 ������ �������ߵȴ�.
				return RealNearestNeighbor(whichWayNotToGo(_root, _x, _y, axis%dim),
					_x, _y, _minDiff, _minDiffNode, axis + 1, dim);
			}
			else
				return NN;
		}
	}
}
struct kdtree_node *NaiveNearestNeighbor(struct kdtree_node *_root, int _x, int _y)
{
	int minDiff = INT_MAX;
	struct kdtree_node *minDiffNode = 0;

	struct kdtree_node *temp = _root;
	int axis = 0; // x�� ���� ����
	while (1)
	{
		if (temp == 0) // Ż�� ����
			return minDiffNode;

		// (_x,_y)�� temp ���� �Ÿ��� ���Ѵ�.
		int dist = (temp->data->x - _x) *  (temp->data->x - _x) + (temp->data->y - _y)* (temp->data->y - _y);

		//���ο� 'Nearest Neighbor'�� �߰�����
		if (dist < minDiff)
		{
			minDiff = dist;
			minDiffNode = temp;
		}

		//struct kdtree_node *whichWayToGo(temp, _x, _y, axis) 
		temp = whichWayToGo(temp, _x, _y, axis); // ���� temp ��ġ�� ã�Ƴ���.

		// ���� �񱳸� ���� axis ����
		axis = (axis + 1) % 2;
	}
}

int main(void)
{
	/*addToSLL(2, 3);
	addToSLL(5, 4);
	addToSLL(9, 6);
	addToSLL(4, 7);
	addToSLL(8, 1);
	addToSLL(7, 2);*/

	addToSLL(5, 1);
	addToSLL(6, 9);
	addToSLL(1, 1);
	addToSLL(2, 3);
	addToSLL(1, 5);
	addToSLL(4, 6);
	addToSLL(7, 10);
	addToSLL(3, 7);

	int num = howManyNodes(head);
	printf("num of SLL nodes: %d\n", num);


	kd_root = build_kdtree(head, 0, 2);

	//printf("(%d,%d)\n", kd_root->data->x, kd_root->data->y);
	//printf("(%d,%d)\n", kd_root->left->data->x, kd_root->left->data->y);
	//printf("(%d,%d)\n", kd_root->right->data->x, kd_root->right->data->y);
	//printf("(%d,%d)\n", kd_root->left->left->data->x, kd_root->left->left->data->y);

	//return 1 if (1,4) is in kd-tree
	//	     0 if not
	//int result = searchKdTree(kd_root, 1, 4);
	//printf("%d\n", result);

	// (2,5)�� ����� ���� ã�� ���ؼ�,
	// ������ ������� kd_tree�� Ÿ�� �������鼭,
	// ���� ����� ���� ã�Ƽ� �� �����͸� ��ȯ�Ѵ�.
	// ��ġ BST�� Ÿ�� ���������� ��������.
	struct kdtree_node *p = NaiveNearestNeighbor(kd_root, 5, 3); // ������� �Ƹ��� (4,7)
	printf("%d , %d \n", p->data->x, p->data->y);
	
	struct kdtree_node *realP = RealNearestNeighbor(kd_root, 5, 3, INT_MAX, 0, 0, 2);

	printf("Rael Nearest is %d, %d\n", realP->data->x, realP->data->y); // ����� (2,3)
	return 0;
}