#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

struct node {
	int number;

	struct node *left;// ������ ���� �ִ� ��������
	struct node *right; // ������ ū �ִ� ����������
};

struct node *root = 0; // �� ���� �ִ� ��

void addToBST(int n) // n�̶�� ���ڸ� �޾ƿͼ� n�� ���� node�� ����� ������ �ִ� �Ϳ� �ִ´�.
{
	// node�� �����.
	struct node *new_one = (struct node*)malloc(sizeof(struct node));
	//���ڸ� �ִ´�.
	new_one->number = n;
	//�����Ȱ� ������ null ������
	new_one->left = new_one->right = 0;

	//BST�� �ƹ��͵� ���� ��� -> root = 0
	if (root == 0) // no bst
	{
		root = new_one;
		return;
	}
	else // BST�� ���� ���� ���
	{
		struct node *temp = root;
		while (temp != 0)
		{
			if (temp->number > n) // ���ʿ� �־�� ��. 
			{
				if (temp->left == 0) // �ƹ��͵� ������ -> �� �ڸ��� new_one�� ��
				{
					temp->left = new_one;
					return;
				}
				else // ���� ������ -> Ÿ�� ��������
					temp = temp->left;

			}
			else // �����ʿ� �־�� ��.
			{
				if (temp->right == 0) // �ƹ��͵� ������ -> �� �ڸ��� new_one�� ��
				{
					temp->right = new_one;
					return;
				}
				else // ���� ������ -> Ÿ�� ��������
					temp = temp->right;
			}
		}
		temp = new_one;
	}
}

//recurive
void inorderTraversal(struct node *_node) // ������ ������������ ���´�.
{
	// recursive �Ϸ��� Ż�� ������ �ʿ� ** -> �޾ƿ� node �� null�� ���
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
	if (where->number == v) // lucky!! �ٷ� ã���� ���
	{
		return where;
	}

	int distance = abs(where->number - v); // �� ���̸� ���Ѵ� -> why ���밪? ������ �Ǵϱ� �������!
	
	if (distance < minDiff) // ���� ���� ����� ���� �� , ��带 �����ϰ� �־����!
	{
		minDiff = distance;
		nn = where;
	}

	//�������� ��
	if (where->number > v) 
	{
		//��������
		//�ݺ��ϸ� �Ǵϱ� recursive �� ���� �ȴ�.
		return findNearestNeighbor(v, where->left, minDiff, nn);
	}
	else 
	{
		//����������
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

	// �Լ��� �� ®���ϱ� �� �Ǿ����� Ȯ���ϱ�

	//printf("%d\n", root->number);// 100�� ���;��Ѵ�.
	//printf("%d\n", root->left->left->number); // 25
	// -> �� ����� Ȯ��!

	// BST �� ���� ���� ���ΰ�? -> �ƴϴ�!! �ֳ��ϸ� ������ ������ ������ ������ ���� �޴´�.
	// �׷��� ��� �ؾ� ���� tree �ΰ�?

	//traversal
	//inorderTraversal(root); // inorder�� ��� : ���� �ڽ� ������ ��� -> ������������ ��� ����


	//=======>>�־��� ���� ���� ����� �� ã��<<=========//
	/* 
	>> �˰��� ����
	root ���� ���� -> 
	1) root== null =>��! (Ż�� ����)
	2) ���� ã���� �ϴ� �ָ� ������ -> ��! 
	3) ���밪 �� -> ���� ã���� �ϴ� ���� �� or ���� ã���� �ϴ� ���� ���� ��
	4) ũ�� ���ؼ� �������� �Ѿ �� ���� -> recursive
	*/
	//findNearestNeighbor(V, ���۳��n , ���� ���� �߿� ���� ����� ��, �� ���� ���� ���
	// -> (int v, struct node *where, int minDiff, struct node *nn)
	struct node *nn = findNearestNeighbor(76, root, INT_MAX, NULL); 
	printf("%d \n", nn->number);
	return 0;
}