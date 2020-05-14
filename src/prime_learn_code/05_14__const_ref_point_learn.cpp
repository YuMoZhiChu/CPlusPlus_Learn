// Example program
#include <iostream>
#include <string>

int main()
{

	int * p = new int(1);
	const int *const q = p;
	int* r = q;

	int k = 10;
	int & l = k;
	const int & j = l;
	int & m = j;

	const int a = 1;
	int b = a;

	*p = 2;
	std::cout << *q << std::endl;
}
