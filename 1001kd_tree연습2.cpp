#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct node {
	int x;
	int y;
	struct node *next;
};
struct node *head;

struct kd_node {
	struct node *data;
	struct kd_node *left;
	struct kd_node *right;
};
void addToSLL(int _x, int _y)
{
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->x = _x;
	newnode->y = _y;
	newnode->next = 0;

	if (head == 0)
	{
		head = newnode;
	}
	else
	{
		struct node *cur = head;

		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = newnode;
	}
}

int howmanynodes(struct node * _head)
{
	struct node *cur = _head;
	int cnt = 0;
	while (cur != 0)
	{
		cnt++;
		cur = cur->next;
	}
	return cnt;
}

void bubble_sort(struct node **_array, int _size, int _axis)
{
	struct node *copyforkd = 0;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size - 1 - i; j++)
		{
			if (_axis == 0)//x 기준
			{
				if (_array[j]->x > _array[j + 1]->x)
				{
					copyforkd = _array[j];
					_array[j] = _array[j + 1];
					_array[j + 1] = copyforkd;
				}
			}
			else if (_axis == 1)//y기준
			{
				if (_array[j]->y > _array[j + 1]->y)
				{
					copyforkd = _array[j];
					_array[j] = _array[j + 1];
					_array[j + 1] = copyforkd;
				}
			}
		}
	}
}

struct node *reBuildSLL(struct node **_array, int _from, int _to)
{
	struct node *start = _array[_from];
	if (_from > _to)
	{
		return 0;
	}
	start->next = 0;

	struct node *cur = start;
	for (int i = _from + 1; i <= _to; i++)
	{
		cur->next = _array[i];
		cur->next->next = 0;
		cur = cur->next;
	}

	return start;
}
kd_node *Buildkdtree(struct node *sll, int _axis, int _dimension)
{
	if (sll == 0)
		return 0;
	
	//size
	int size = howmanynodes(sll);
	
	//배열 생성
	struct node **arraynodes = (struct node **)malloc(sizeof(struct node*)*size);

	// 값 넣어주기
	struct node *cur = sll;
	for (int i = 0; i < size; i++)
	{
		arraynodes[i] = cur;
		cur = cur->next;
	}

	//axis
	_axis = _axis % _dimension;

	//정렬
	bubble_sort(arraynodes, size, _axis);

	// mid
	int mid = size / 2;

	//중간기준으로 나누기
	struct kd_node *newkdnode = (struct kd_node*)malloc(sizeof(struct kd_node));
	newkdnode->data = arraynodes[mid];
	newkdnode->left = Buildkdtree(reBuildSLL(arraynodes, 0, mid - 1), _axis + 1, _dimension);
	newkdnode->right = Buildkdtree(reBuildSLL(arraynodes, mid + 1, size - 1), _axis + 1, _dimension);

	free(arraynodes);

	return newkdnode;
}

kd_node *WayToGo(struct kd_node *_root, int _x, int _y, int axis)
{
	if (axis == 0)//x
	{
		if (_root->data->x > _x)
		{
			return _root->left;
		}
		else
		{
			return _root->right;
		}
	}
	else if (axis == 1) //y
	{
		if (_root->data->y > _y)
		{
			return _root->left;
		}
		else
		{
			return _root->right;
		}
	}
}

kd_node *WayNotToGo(struct kd_node *_root, int _x, int _y, int axis)
{
	if (axis == 0)//x
	{
		if (_root->data->x < _x)
		{
			return _root->left;
		}
		else
		{
			return _root->right;
		}
	}
	else if (axis == 1) //y
	{
		if (_root->data->y > _y)
		{
			return _root->left;
		}
		else
		{
			return _root->right;
		}
	}
}
kd_node *realNearestSearch(struct kd_node *_root, int _x, int _y, int _minDiff, struct kd_node *_minDiffNode, int _axis, int _dimension)
{
	_axis = _axis % _dimension;

	//탈출조건
	if (_root == 0)
	{
		return _minDiffNode;
	}

	//퍼펙트!!
	if (_root->data->x == _x && _root->data->y == _y)
	{
		return _root;
	}

	else
	{
		int diff = (_root->data->x - _x)*(_root->data->x - _x) + (_root->data->y - _y)*(_root->data->y - _y);

		if (_minDiff > diff)
		{
			_minDiff = diff;
			_minDiffNode = _root;
		}

		//짧은걸 계속 찾아주기 -> 다음 노드 찾아서
		struct kd_node *Way = WayToGo(_root, _x, _y, _axis);

		//다음 노드에서 짧은거 찾아주기!
		struct kd_node *NearestNode = realNearestSearch(Way, _x, _y, _minDiff, _minDiffNode, _axis + 1, _dimension);

		// 가장 짧은 것의 길이 
		int NN_diff = (NearestNode->data->x - _x)*(NearestNode->data->x - _x) + (NearestNode->data->y - _y)*(NearestNode->data->y - _y);

		// 그것이 경계선을 넘어 가는가?
		if (_axis == 0)//x
		{
			if (NN_diff > (_root->data->x - _x)*(NearestNode->data->x - _x))
			{
				// 반대 방향 봐주기 !
				return realNearestSearch(WayNotToGo(_root, _x, _y, _axis), _x, _y, _minDiff, _minDiffNode, _axis + 1, _dimension);
			}
			else
			{
				return NearestNode;
			}
		}
		else if (_axis == 1)//y
		{
			if (NN_diff > (_root->data->y - _y)*(NearestNode->data->y - _y))
			{
				// 반대 방향 봐주기 !
				return realNearestSearch(WayNotToGo(_root, _x, _y, _axis), _x, _y, _minDiff, _minDiffNode, _axis + 1, _dimension);
			}
			else
			{
				return NearestNode;
			}
		}
	}

}
int main()
{
	addToSLL(7, 2);
	addToSLL(5, 4);
	addToSLL(9, 6);
	addToSLL(2, 3);
	addToSLL(4, 7);
	addToSLL(8, 1);

	//printf("%d\n", howmanynodes(head));
	struct kd_node *kd_root = Buildkdtree(head,0,2);
	struct kd_node *kd_nearest = realNearestSearch(kd_root, 5, 3, INT_MAX, 0, 0, 2);
	
	printf("%d, %d\n", kd_nearest->data->x, kd_nearest->data->y);
	return 0;

}