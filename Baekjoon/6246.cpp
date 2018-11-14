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

	cin >> howmanyballons >> howmanycases;// 몇개의 풍선인가? / 몇 개의 경우의 수가 존재하는가?

	for (int i = 0; i < howmanycases; i++)//경우의 수 만큼
	{
		cin >> from >> whichslot; // from 부터 시작으로 // whichslot 몇칸마다 한개씩?

		make_balloon(from, whichslot, howmanyballons);
	}
	
	cout <<howmanyballons - howmanyzeros<<endl;

	return 0;
}