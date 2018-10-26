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
	inorderTraversal(root); // inorder의 경우 : 왼쪽 자신 오른쪽 출력 -> 오름차순으로 출력 가능

	return 0;
}