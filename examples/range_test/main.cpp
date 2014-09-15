#include <iostream>

#include <kq/range.h>

using namespace std;

int main()
{

	// prints "10, 11, 12, 13, 14"
	for(auto x : kq::range(10,15)){
		cout << x << ", ";
	}
	cout << endl;

	using namespace kq::human_readable_range;
	// prints "35, 36, 37, 38, 39, 40, 41"
	for(auto x : 35-42_range){
		cout << x << ", ";
	}
	cout << endl;

	// prints "50, 49, 48, 47, 46, 45, 44, 43"
	for(auto x : 50-42_range){
		cout << x << ", ";
	}
	cout << endl;


	return 0;
}

