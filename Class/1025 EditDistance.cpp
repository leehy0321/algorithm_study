#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//s1 --------------> s2
//char s1[4] = "cash";
//char s2[3] = "cat";

enum OPERATION
{
	COPY = 0,
	INSERT, //1
	DELETE, //2
	SUBSTITUDE, // 3
	NON
};
char s1[7] = "kat";
char s2[6] = "cat";

//
//create 2d array dynamically
//returns the allocated space address
//
int **createTable(int num_row, int num_col) // return : 2차원 배열이니까 
{
	int **rows = (int **)malloc(sizeof(int *)*num_row); // 먼저 세로부터 생성
	for (int i = 0; i < num_row; i++) // 세로 각 칸에 가로갯수만큼 생성 
	{
		rows[i] = (int *)malloc(sizeof(int)*num_col);
	}

	return rows;
}

//returns the minimum among _a, _b, _c
int findMininum(int _a, int _b, int _c) // 작은애찾기!
{
	return (_a < _b) ? ((_a < _c) ? _a : _c) : ((_b < _c) ? _b : _c);
	
	/*if (_a < _b)
	{
		if (_a < _c)
		{
			return _a;
		}
		else
		{
			return _c;
		}
	}
	else
	{
		if (_b < _c)
		{
			return _b;
		}
		else
		{
			return _c;
		}
	}*/
}

void populateTabel(int **_table, char *_s1, char *_s2, int _num_row, int _num_col)
{
	for (int i = 0; i < _num_col; i++)
	{
		_table[0][i] = i;
	}

	for (int i = 0; i < _num_row; i++)
	{
		_table[i][0] = i;
	}

	for (int r = 1; r < _num_row; r++)
	{
		for (int c = 1; c < _num_col; c++)
		{
			//마지막글자에 따라 칸을 채워준다.//
			//같으면 -> 대각선의 값
			//다르면 -> 주위값 중 작은것 + 1

			if (_s1[r - 1] == _s2[c - 1]) // 마지막글자가 서로 같으면 -> 대각선이랑 같은 값
			{
				_table[r][c] = _table[r - 1][c - 1];
			}
			else//마지막 글자가 서로 같으면 -> 주위 값 중 제일 작은것 +1
			{
				_table[r][c] = findMininum(//작은 것 찾기
									_table[r - 1][c],  // 주위의 것 넣어 보기 
									_table[r][c - 1], 
									_table[r - 1][c - 1]) + 1;
			}
		}
	}
}

enum OPERATION *stack = 0;
int stack_top = -1;

void createStack(int _num_row, int _num_col)
{
	stack = (enum OPERATION *)malloc(sizeof(enum OPERATION)*(_num_row + _num_col - 2));
	stack_top = -1;
}

void push(enum OPERATION _operation)
{
	//예외조건 ( 넘칠경우 )을 처리하지 않아도 된다->딱맞는 사이즈만큼만 진행될 것이기 때문
	stack_top += 1;
	stack[stack_top] = _operation;
}

enum OPERATION pop(void)
{
	// 빼는것은 다 빼서 없을 경우에도 뺄 수가 있으니 예외 조건을 처리해준다.
	if (stack_top == -1)
	{
		return NON;
	}
	
	enum OPERATION result = stack[stack_top];
	stack_top -= 1;
	return result;
}

enum OPERATION findSmallestNeighbor(int **_table, int _r, int _c)
{
	//주변의 값들을 비교해주기위한 변수 선언
	int up;//위
	int left;//왼쪽
	int diag;//대각선

	if (_r - 1 >= 0)
	{
		up = _table[_r-1][_c];
	}
	else
	{
		up = INT_MAX;
	}

	if (_c - 1 >= 0)
	{
		left = _table[_r][_c - 1];
	}
	else
	{
		left = INT_MAX;
	}

	if (_r - 1 >= 0 && _c - 1 >= 0)
	{
		diag = _table[_r - 1][_c - 1];
	}
	else
	{
		diag = INT_MAX;
	}

	// up is the smallet neighbor -> UP
	if (up <= left && up <= diag)
	{
		return DELETE;
	}

	if (left <= up && left <= diag)
	{
		return INSERT;
	}
	if (diag <= up && diag <= left)
	{
		if (_table[_r][_c] == diag)
		{
			return COPY;
		}
		else
		{
			return SUBSTITUDE;
		}
	}
}

void showOperationSequence(int **_table, int _num_row, int _num_col)
{
	createStack(_num_row, _num_col); // 스택을 생성시켜준다.

	int cur_r = _num_row - 1;
	int cur_c = _num_col - 1;

	while (1)
	{
		if (cur_r == 0 && cur_c == 0) // 0,0까지 실행해준다.
		{
			break;
		}

		//find the smallest neighbor

		//push operation

		//update cur_r, cur_c
		enum OPERATION result = findSmallestNeighbor(_table, cur_r, cur_c);

		switch (result)
		{
		case COPY:
			push(COPY);
			cur_r -= 1;
			cur_c -= 1;
			break;
		case INSERT:
			push(INSERT);
			cur_c -= 1;
			break;
		case DELETE:
			push(DELETE);
			cur_r -= 1;
			break;
		case SUBSTITUDE:
			push(SUBSTITUDE);
			cur_r -= 1;
			cur_c -= 1;
			break;
		case NON:
			break;
		default:
			break;
		}
	}

	//pop % print untill the stack becomes empty
	while (1)
	{
		enum OPERATION res = pop();
		if (res == NON)//끝
		{
			break;
		}

	
		printf("operation %d\n", res);// 끝이 아니라면 출력
	}
}

int main()
{
	int num_row = strlen(s1) + 1;
	int num_col = strlen(s2) + 1;

	int **table = createTable(num_row, num_col); // 테이블 생성

	populateTabel(table, s1, s2, num_row, num_col);//이것으로 테이블을 채워주기

	printf("Edit distanve between < %s > and < %s > is %d\n",
								   s1,   s2,    table[num_row-1][num_col-1]);
	
	//
	//show what operation sequence changes s1 to s2
	//
	showOperationSequence(table, num_row, num_col);
	return 0;

}