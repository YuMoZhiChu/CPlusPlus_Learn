#include<iostream>
#include<vector>
using namespace std;

int main() {
	int *ip = new int(65);
	char *pc = reinterpret_cast<char*>(ip);
}