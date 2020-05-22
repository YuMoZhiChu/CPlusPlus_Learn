#include<iostream>
using namespace std;

int main() {
	int i;
	char c = 'a';
	char *pc = "hello";
	i = int(*pc);
	void *v;
	v = pc;
	char *v_c = static_cast<char*>(v);
}