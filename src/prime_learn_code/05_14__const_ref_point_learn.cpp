// Example program
#include <iostream>
#include <string>
using namespace std;
extern int q;

int main()
{
	int i = 0, &ri = i;
	float f = 1.0, &rf = f;
	ri = 1.0;
	ri = f;
	rf = 0;
	rf = i;
}
