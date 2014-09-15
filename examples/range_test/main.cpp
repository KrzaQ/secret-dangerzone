#include <iostream>

#include <kq/range.h>

using namespace std;

int main()
{
	for(auto x : kq::range(10,27)){
		cout << x << ", ";
	}
	cout << endl;

	using namespace kq::human_readable_range;
	for(auto x : 28-42_range){
		cout << x << ", ";
	}
	cout << endl;

	for(auto x : 50-42_range){
		cout << x << ", ";
	}
	cout << endl;


	return 0;
}

