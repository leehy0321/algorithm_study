#include<iostream>

using namespace std;

int balloon[10000];
int howmanyzeros;

void make_balloon(int _from, int _whichslot, int _howmanyballoons)
{
	int index = 0, ballon_index=0;

	ballon_index =  _from;
	
	while (ballon_index <= _howmanyballoons)
	{
		cout << _whichslot << " :: " << ballon_index << endl;
		if (balloon[index*_whichslot]==0)
		{
			howmanyzeros++;
			balloon[index*_whichslot] = 1;
		}

		ballon_index = ballon_index + _whichslot;
	}
}
int main()
{
	int howmanyballons, howmanycases;
	int from, whichslot;

	cin >> howmanyballons >> howmanycases;// ��� ǳ���ΰ�? / �� ���� ����� ���� �����ϴ°�?

	for (int i = 0; i < howmanycases; i++)//����� �� ��ŭ
	{
		cin >> from >> whichslot; // from ���� �������� // whichslot ��ĭ���� �Ѱ���?

		make_balloon(from, whichslot, howmanyballons);
	}
	
	cout <<howmanyballons - howmanyzeros<<endl;

	return 0;
}