#include <stdio.h>
#include <stdlib.h>

struct node
{
	int x;
	int y;
	struct node *next;
};

struct node *head = 0;

// kd-tree의 root를 가리키는 root pointer
struct kdtree_node *kd_root = 0;

// kd-tree의 노드 구조체를 정의
struct kdtree_node
{
	struct node *data;
	struct kdtree_node *left;
	struct kdtree_node *right;
};

// linked list에 노드가 몇 개 있는지를 세는 함수
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
// array에 담긴 주소들을 x 혹은 y값에 따라 오름차순으로 정렬
//
// _byX = 1: x에 대해서 소팅
//      = 0: y에 대해서 소팅
// _size: array의 길이
void doBubbleSort(struct node **_array, int _byX, int _size)
{
	int i = 0;
	int j = 0;

	for (j = 0; j < _size; j++)
	{
		for (i = 0; i < _size - 1 - j; i++)  // (0,1) (1,2), ......
		{
			if (_byX == 1)  // x에 대해서 비교
			{
				if (_array[i]->x > _array[i + 1]->x)
				{
					// swap
					struct node *temp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = temp;
				}
			}
			else            // y에 대해서 비교
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

// kdtree를 생성해내는 함수
// 반환: 생성된 kdtree node의 주소를 반환한다.
// 입력: kdtree에 들어갈 linked list
//       depth정보: x축 혹은 y축에 대해서 비교할 정보,,,
//       dimension: 데이터의 차원, 2차원 점의 경우 2
struct kdtree_node *build_kdtree(struct node *sll,
	int _depth,
	int _dimension)
{
	if (sll == 0)
	{
		return 0;
	}
	// 1. SLL 노드들의 주소를 array에 저장한다.

	// SLL에 담긴 노드의 개수를 가져온다.
	int numSLLNodes = howManyNodes(sll);

	// 노드 주소들을 담을 array를 할당한다.
	struct node **nodeAddrArray = (struct node **)malloc(sizeof(struct node *)*numSLLNodes);

	// array에 다가 노드 주소들을 하나씩 넣는다.
	int i;
	struct node *temp = sll;
	for (i = 0; i < numSLLNodes; i++)
	{
		nodeAddrArray[i] = temp;
		temp = temp->next;
	}

	// 검증
	// nodeAddrArray를 이용해서 SLL 노드들의 값을 모두 출력
	//for (i = 0; i < numSLLNodes; i++)
	//{
	//	int _x = nodeAddrArray[i]->x;
	//	int _y = nodeAddrArray[i]->y;
	//	printf("%d, %d\n", _x, _y);
	//}

	// x축 혹은 y축에 대해서 소팅하는지 결정
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
		if (temp == 0) // (_x,_y)를 찾지 못했음.
			return 0;

		// 내가 찾고자 하는 값인지 비교
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

		axis = (axis + 1) % 2;//axis 바꿔주기
	}
}


void addToSLL(int _x, int _y)
{
	// 데이터를 저장할 노드를 생성한다.
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->x = _x;
	new_one->y = _y;
	new_one->next = 0;

	// SLL에 new_one을 추가한다.
	if (head == 0)
	{
		head = new_one;
		return;
	}
	else  // SLL의 끝을 찾아서 붙여넣는다.
	{
		struct node *temp = head;
		while (1)
		{
			if (temp->next == 0)  // 맨끝을 찾은 경우
			{
				temp->next = new_one;  // 끝에 붙여넣는다.
				return;
			}
			else // 아직 맨끝 노드가 아닌 경우,
			{
				// 그 다음 노드로 이동한다.
				temp = temp->next;
			}
		}
	}
}

//(_x, _y)가 주어졌을때,
//axis를 고려하여
//_root의 left혹은 right로 내려갈지를 반환
struct kdtree_node *whichWayToGo(struct kdtree_node *_root, int _x,int  _y, int axis)
{
	if (axis == 0)// x축 비교
	{
		if (_root->data->x > _x)
			return _root->left;
		else
			return _root->right;
	}
	else // y축 비교
	{
		if (_root->data->y > _y)
			return _root->left;
		else
			return _root->right;
	}
}

//_root의 left혹은 right로 내려갈지를 반환
struct kdtree_node *whichWayNotToGo(struct kdtree_node *_root, int _x, int  _y, int axis)
{
	if (axis == 0)// x축 비교
	{
		if (_root->data->x > _x)
			return _root->right;
		else
			return _root->left;
	}
	else // y축 비교
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
	//탈출조건
	if (_root == 0)
		return _minDiffNode;

	
	//가장 ㅍㅓ펙트
	if (_root->data->x == _x && _root->data->y == _y)
		return _root;

	else
	{
		//얼마나 멀리 떨어져있는지 계산
		// _root와의 거리 계산

		int dist = (_root->data->x - _x) *  (_root->data->x - _x) + (_root->data->y - _y)* (_root->data->y - _y);

		if (dist < _minDiff)
		{
			_minDiff = dist;
			_minDiffNode = _root;
		}

		//이제 root를 떠나, 왼쪽이든, 오른쪽이든 내려간다.
		struct kdtree_node *wayTo = whichWayToGo(_root, _x, _y, axis%dim);

		struct kdtree_node *NN
			= RealNearestNeighbor(wayTo, _x, _y, _minDiff, _minDiffNode, axis + 1, dim);

		//결정된 nearest neighbor까지의 거리를 구다.
		int dist_to_NN = (NN->data->x - _x)*(NN->data->x - _x) + (NN->data->y - _y)*(NN->data->y - _y);

		//nearest neighbor까지의 거리가 경계선을 넘는지 본다.
		if (axis%2 == 0) // x축에 대하여 검사
		{
			if (dist_to_NN > (_x - _root->data->x)*(_x - _root->data->x))
			{
				//경계선 저쪽을 뒤져봐야된다.
				return RealNearestNeighbor(whichWayNotToGo(_root, _x, _y, axis%dim),
					_x, _y, _minDiff, _minDiffNode, axis + 1, dim);
			}
			else
				return NN;
		}
		else // y축에 대해서 검사
		{
			if (dist_to_NN > (_y - _root->data->y)*(_x - _root->data->x))
			{
				//경계선 저쪽을 뒤져봐야된다.
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
	int axis = 0; // x축 부터 시작
	while (1)
	{
		if (temp == 0) // 탈출 조건
			return minDiffNode;

		// (_x,_y)와 temp 간의 거리를 구한다.
		int dist = (temp->data->x - _x) *  (temp->data->x - _x) + (temp->data->y - _y)* (temp->data->y - _y);

		//새로운 'Nearest Neighbor'를 발견햇음
		if (dist < minDiff)
		{
			minDiff = dist;
			minDiffNode = temp;
		}

		//struct kdtree_node *whichWayToGo(temp, _x, _y, axis) 
		temp = whichWayToGo(temp, _x, _y, axis); // 다음 temp 위치를 찾아낸다.

		// 다음 비교를 위해 axis 증가
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

	// (2,5)와 가까운 점을 찾기 위해서,
	// 순진한 방법으로 kd_tree를 타고 내려가면서,
	// 가장 가까운 점을 찾아서 그 포인터를 반환한다.
	// 마치 BST를 타고 내려가듯이 내려간다.
	struct kdtree_node *p = NaiveNearestNeighbor(kd_root, 5, 3); // 결과값은 아마도 (4,7)
	printf("%d , %d \n", p->data->x, p->data->y);
	
	struct kdtree_node *realP = RealNearestNeighbor(kd_root, 5, 3, INT_MAX, 0, 0, 2);

	printf("Rael Nearest is %d, %d\n", realP->data->x, realP->data->y); // 결과는 (2,3)
	return 0;
}