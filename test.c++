#include <deque>
#include <iostream>
#include <cmath>
#include <typeinfo>

using namespace std;

int main()
{

	deque<int> x;
	for(int i = 0; i < 30; ++i){
		x.push_back(i);
	}
	{
		deque<int>::iterator b = x.begin();
		while(b != x.end())
			cout<< *b++ << " ";
		cout << endl;
	}

	x.resize(15);
	deque<int>::iterator b = x.begin();
	while(b != x.end())
		cout << *b++ << " ";
	cout << endl;
	return 0;
}