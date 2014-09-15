#include <iostream>

#include <kq/range.h>

using namespace std;

int main()
{
	for(auto x : kq::range(10,27)){
		cout << x << ", ";
	}
	cout << endl;

	return 0;
}

