#include "SkipList.h"

using namespace std;

int main()
{
	SkipList<int, int, 10>  t;
	int num[1000];
	std::random_device rd;
	//insert
	for (int i = 0; i < 1000; i++)
	{
		num[i] = rd() % 10000;
		t.insert(num[i], num[i]);
	}
	//search
	for (int i = 0; i < 1000; i++)
	{
		int res;
		t.search(rd() % 10000, res);
	}
	//remove
	for (int i = 0; i < 1000; i++)
	{
		int res;
		t.remove(num[i], res);
	}
}