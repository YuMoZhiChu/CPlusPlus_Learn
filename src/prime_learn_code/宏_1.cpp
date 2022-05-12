#include <stdio.h>    
#define trace(x, format) printf(#x " = %" #format "\n", x)    
#define trace2(i) trace(x##i, d)   

#define ABCD "WineProjectPrefix"
#define ABCDE ABCD##ABCDE

#define JOIN_FOUR_PARAMS(A,B,C,D) A##B##C##D
#define JOIN_FOUR_PARAMS_CHARPTR(A,B,C,D) JOIN_FOUR_PARAMS(#A, #B, #C, #D)

void char_fun(char* char_string)
{
	int bk = 1;
	++bk;
}

int main()
{
	int i = 1;
	char* s = "three";
	float x = 2.0;

	trace(i, d);                // 相当于 printf("i = %d\n", i)  
	trace(x, f);                // 相当于 printf("x = %f\n", x)  
	trace(s, s);                // 相当于 printf("s = %s\n", s)  

	int x1 = 1, x2 = 2, x3 = 3;
	trace2(1);                  // 相当于 trace(x1, d)  
	trace2(2);                  // 相当于 trace(x2, d)  
	trace2(3);                  // 相当于 trace(x3, d)  

	//char_fun(ABCDE);

	const char* a = "a1";
	const char* b = "b2";
	const char* c = "c3";
	const char* d = "d4";

	int JOIN_FOUR_PARAMS(a, b, c, d) = 1234;

	int test_x_num = 123;

	int test_y_num = !!test_x_num;

	int test_z_num = 123;
	test_z_num += !!test_z_num;

	int test_z2_num = 987654;
	test_z2_num += !!test_z2_num;

	return 0;
}