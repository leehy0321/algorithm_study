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

int howmanynodes(struct node *sll)
{
	struct node *cur = sll;
	int count = 0;
	while (cur != 0)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

void bubble_sort(struct node **_array, int _axis, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size-1-i; j++)
		{
			if (_axis == 0)//x
			{
				if (_array[j]->x > _array[j + 1]->x)
				{
					struct node *forcopy = _array[j];
					_array[j] = _array[j + 1];
					_array[j + 1] = forcopy;
				}
			}
			else if (_axis == 1)
			{
				if (_array[j]->y > _array[j + 1]->y)
				{
					struct node *forcopy = _array[j];
					_array[j] = _array[j + 1];
					_array[j + 1] = forcopy;
				}
			}
		}
	}
}


struct node *rebuildsll(struct node **_array, int from, int to)
{
	if(from > to)
	{
		return 0;
	}

	struct node *start = _array[from];
	start->next = 0;

	struct node *cur = start;
	for (int i = from+1; i <= to; i++)
	{
		cur->next = _array[i];
		cur->next->next = 0;
		cur = cur->next;
	}
	return start;
}
kd_node* build_kdtree(struct node* sll, int depth, int dimension)
{
	struct node *cur = sll;
	int size = howmanynodes(sll);

	struct node **arraynodes = (struct node**)malloc(sizeof(struct node*) * size);

	if (sll == 0)
	{
		return 0;
	}

	for (int i = 0; i < size; i++)
	{
		arraynodes[i] = cur;
		cur = cur->next;
	}

	/*for (int i = 0; i < 6; i++)
	{	
		printf(" %d -> ", arraynodes[i]->x);
		
	}
	printf("%\n");*/

	int axis = depth % dimension; // 0 : x / 1 : y

	bubble_sort(arraynodes, axis, size);

	int mid = size / 2;

	struct kd_node *curforkdtree = (struct kd_node *)malloc(sizeof(struct kd_node));
	curforkdtree->data = arraynodes[mid];

	curforkdtree ->left = build_kdtree(rebuildsll(arraynodes, 0, mid - 1), depth + 1, dimension);
	curforkdtree->right = build_kdtree(rebuildsll(arraynodes, mid + 1, size - 1), depth + 1, dimension);

	free(arraynodes);

	return curforkdtree;
}

kd_node *whichWayToGo(struct kd_node *_root, int _x, int _y, int _axis)
{
	if (_axis == 0)
	{
		if (_root->data->x < _x)
		{
			return _root->right;
		}
		else
		{
			return _root->left;
		}
	}
	else if (_axis == 1)
	{
		if (_root->data->y < _y)
		{
			return _root->right;
		}
		else
		{
			return _root->left;
		}
	}
}

kd_node *whichWayNotToGo(struct kd_node *_root, int _x, int _y, int _axis)
{
	if (_axis == 0)
	{
		if (_root->data->x > _x)
		{
			return _root->right;
		}
		else
		{
			return _root->left;
		}
	}
	else if (_axis == 1)
	{
		if (_root->data->y > _y)
		{
			return _root->right;
		}
		else
		{
			return _root->left;
		}
	}
}

struct kdtree_node *FindMinDiffNode(struct kdtree_node *_root, int _x, int _y) {

	struct kdtree_node *minDiffNode = 0;
	int minDiff = INT_MAX;
	struct kdtree_node *cur = _root;
	int axis = 0; // 처음에 x축

	while (1) {
		//탈출 조건
		if (cur == 0) {
			return minDiffNode;
		}
		else {
			int dist = (cur->data->x - _x)*(cur->data->x - _x) + (cur->data->y - _y)*(cur->data->y - _y);
			if (dist < minDiff) {
				minDiff = dist;
				minDiffNode = cur;
			}
			cur = whichWayToGo(cur, _x, _y, axis);
			axis = (axis + 1) % 2;
		}
	}
}

struct kdtree_node *FindMinDiffNode(struct kdtree_node *_root, int _x, int _y) {

	struct kdtree_node *minDiffNode = 0;
	int minDiff = INT_MAX;
	struct kdtree_node *cur = _root;
	int axis = 0; // 처음에 x축

	while (1) {
		//탈출 조건
		if (cur == 0) {
			return minDiffNode;
		}
		else {
			int dist = (cur->data->x - _x)*(cur->data->x - _x) + (cur->data->y - _y)*(cur->data->y - _y);
			if (dist < minDiff) {
				minDiff = dist;
				minDiffNode = cur;
			}
			cur = whichWayToGo(cur, _x, _y, axis);
			axis = (axis + 1) % 2;
		}
	}
}

/*
struct kdtree_node *NearestNode(struct kdtree_node *_root, int _x, int _y,
	struct kdtree_node *_minDiffNode,
	int _axis) {

	// 탈출조건
	if (_root == 0) {
		return _minDiffNode;
	}

	int minDiff = (_minDiffNode->data->x - _x)*(_minDiffNode->data->x - _x)
		+ (_minDiffNode->data->y - _y)*(_minDiffNode->data->y - _y);

	int dist_to_root = (_root->data->x - _x)*(_root->data->x - _x)
		+ (_root->data->y - _y)*(_root->data->y - _y);
	if (dist_to_root < minDiff) {
		_minDiffNode = _root;
	}

	// root부터 아래까지 타고 내려가기
	struct kdtree_node *cur = _root;

	if (_axis == 0) { // x비교
		int dist = (_root->data->x - _x)*(_root->data->x - _x);
		if (dist < minDiff) {
			// 반대편도 확인해주기
			_minDiffNode = NearestNode(whichWayNotToGo(_root, _x, _y, _axis), _x, _y, _minDiffNode, (_axis + 1) % 2);
		}
		// 반대편 제외시키고 원래 방향으로만 내려가면됨
		_minDiffNode = NearestNode(whichWayToGo(_root, _x, _y, _axis), _x, _y, _minDiffNode, (_axis + 1) % 2);

	}
	else {  //y비교
		int dist = (_root->data->y - _y)*(_root->data->y - _y);
		if (dist < minDiff) {
			_minDiffNode = NearestNode(whichWayNotToGo(_root, _x, _y, _axis), _x, _y, _minDiffNode, (_axis + 1) % 2);
		}
		else {
			_minDiffNode = NearestNode(whichWayToGo(_root, _x, _y, _axis), _x, _y, _minDiffNode, (_axis + 1) % 2);
		}
	}
}*/
kd_node *RealnearesSearch(kd_node *_root, int _x, int _y, int minDiff, kd_node *minDiffNode, int _axis, int _dimension)
{
	_axis %= _dimension;

	if (_root == 0)
	{
		return minDiffNode;
	}

	if (_root->data->x == _x && _root->data->y == _y)
	{
		return _root;
	}
	else
	{
		int dist = (_root->data->x - _x) * (_root->data->x - _x) + (_root->data->y - _y)*(_root->data->y - _y);

		if (dist < minDiff)
		{
			minDiff = dist;
			minDiffNode = _root;
		}

		struct kd_node *NextWay = whichWayToGo(_root, _x, _y, _axis);

		//가장 짧은거 찾고
		struct kd_node *NearestNode = RealnearesSearch(NextWay, _x, _y, minDiff, minDiffNode, _axis + 1, _dimension);
		int dist_NearestNode = (NearestNode->data->x - _x)*(NearestNode->data->x - _x) + (NearestNode->data->y - _y)*(NearestNode->data->y - _y);
		
		if (_axis == 0)//x
		{
			if (dist_NearestNode > (_root->data->x - _x)*(_root->data->x - _x))
			{
				return RealnearesSearch(whichWayNotToGo(_root, _x, _y, _axis), _x, _y, minDiff, minDiffNode, _axis + 1, _dimension);
			}
			else
			{
				return NearestNode;
			}
		}
		else if (_axis == 1) //y
		{
			if (dist_NearestNode > (_root->data->y - _y)*(_root->data->y - _y))
			{
				return RealnearesSearch(whichWayNotToGo(_root, _x, _y, _axis), _x, _y, minDiff, minDiffNode, _axis + 1, _dimension);
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
	/*addToSLL(7, 2);
	addToSLL(5, 4);
	addToSLL(9, 6);
	addToSLL(2, 3);
	addToSLL(4, 7);
	addToSLL(8, 1);*/

	addToSLL(5, 1);
	addToSLL(6, 9);
	addToSLL(1, 1);
	addToSLL(2, 3);
	addToSLL(1, 5);
	addToSLL(4, 6);
	addToSLL(7, 10);
	addToSLL(3, 7);

	struct kd_node *kd_root = build_kdtree(head, 0, 2);
	struct kd_node *kd_nearest = RealnearesSearch(kd_root, 5, 3, INT_MAX, 0, 0, 2);
	printf("%d, %d\n", kd_nearest->data->x, kd_nearest->data->y);
	//printf("%d\n", howmanynodes());


	return 0;
}