#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

struct node {
	int number;

	struct node *left;// 나보다 작은 애는 왼쪽으로
	struct node *right; // 나보다 큰 애는 오른쪽으로
};

struct node *root = 0; // 맨 위에 있는 애

void addToBST(int n) // n이라는 숫자를 받아와서 n을 갖는 node를 만들고 기존에 있는 것에 넣는다.
{
	// node를 만든다.
	struct node *new_one = (struct node*)malloc(sizeof(struct node));
	//숫자를 넣는다.
	new_one->number = n;
	//오른팔과 왼팔을 null 값으로
	new_one->left = new_one->right = 0;

	//BST에 아무것도 없는 경우 -> root = 0
	if (root == 0) // no bst
	{
		root = new_one;
		return;
	}
	else // BST에 무언가 있을 경우
	{
		struct node *temp = root;
		while (temp != 0)
		{
			if (temp->number > n) // 왼쪽에 넣어야 함. 
			{
				if (temp->left == 0) // 아무것도 없으면 -> 그 자리는 new_one의 것
				{
					temp->left = new_one;
					return;
				}
				else // 무언가 있으면 -> 타고 내려가기
					temp = temp->left;

			}
			else // 오른쪽에 넣어야 함.
			{
				if (temp->right == 0) // 아무것도 없으면 -> 그 자리는 new_one의 것
				{
					temp->right = new_one;
					return;
				}
				else // 무언가 있으면 -> 타고 내려가기
					temp = temp->right;
			}
		}
		temp = new_one;
	}
}

//recurive
void inorderTraversal(struct node *_node) // 무조건 오름차순으로 나온다.
{
	// recursive 하려면 탈출 조건이 필요 ** -> 받아온 node 가 null인 경우
	if (_node == 0)
	{
		return;
	}

	inorderTraversal(_node->left);
	printf("%d \n", _node->number);
	inorderTraversal(_node->right);
}

struct node *findNearestNeighbor(int v, struct node *where, int minDiff, struct node *nn)
{

	if (where == NULL)
	{
		return nn;
	}
	if (where->number == v) // lucky!! 바로 찾았을 경우
	{
		return where;
	}

	int distance = abs(where->number - v); // 그 차이를 구한다 -> why 절대값? 가까우면 되니까 상관없어!
	
	if (distance < minDiff) // 나랑 제일 가까운 애의 값 , 노드를 저장하고 있어야지!
	{
		minDiff = distance;
		nn = where;
	}

	//내려가는 것
	if (where->number > v) 
	{
		//왼쪽으로
		//반복하면 되니까 recursive 를 쓰면 된다.
		return findNearestNeighbor(v, where->left, minDiff, nn);
	}
	else 
	{
		//오른쪽으로
		return findNearestNeighbor(v, where->right, minDiff, nn);
	}
}
int main(void)
{
	//tree build
	addToBST(100);
	addToBST(50);
	addToBST(150);
	addToBST(25);
	addToBST(75);

	// 함수를 다 짰으니까 잘 되었는지 확인하기

	//printf("%d\n", root->number);// 100이 나와야한다.
	//printf("%d\n", root->left->left->number); // 25
	// -> 잘 만든것 확인!

	// BST 가 제일 좋은 것인가? -> 아니다!! 왜냐하면 숫자의 들어오는 순서의 영향을 많이 받는다.
	// 그래서 어떻게 해야 좋은 tree 인가?

	//traversal
	//inorderTraversal(root); // inorder의 경우 : 왼쪽 자신 오른쪽 출력 -> 오름차순으로 출력 가능


	//=======>>주어진 값과 가장 비슷한 값 찾기<<=========//
	/* 
	>> 알고리즘 정리
	root 에서 시작 -> 
	1) root== null =>끝! (탈출 조건)
	2) 내가 찾고자 하는 애를 있으면 -> 끝! 
	3) 절대값 비교 -> 내가 찾고자 하는 값과 나 or 내가 찾고자 하는 값과 다음 값
	4) 크기 비교해서 다음으로 넘어갈 곳 정함 -> recursive
	*/
	//findNearestNeighbor(V, 시작노드n , 지금 까지 중에 제일 가까운 값, 그 값을 가진 노드
	// -> (int v, struct node *where, int minDiff, struct node *nn)
	struct node *nn = findNearestNeighbor(76, root, INT_MAX, NULL); 
	printf("%d \n", nn->number);
	return 0;
}