//#include <stdio.h>    
//#define trace(x, format) printf(#x " = %" #format "\n", x)    
//#define trace2(i) trace(x##i, d)   
//
//int main()
//{
//	int i = 1;
//	char* s = "three";
//	float x = 2.0;
//
//	trace(i, d);                // 相当于 printf("i = %d\n", i)  
//	trace(x, f);                // 相当于 printf("x = %f\n", x)  
//	trace(s, s);                // 相当于 printf("s = %s\n", s)  
//
//	int x1 = 1, x2 = 2, x3 = 3;
//	trace2(1);                  // 相当于 trace(x1, d)  
//	trace2(2);                  // 相当于 trace(x2, d)  
//	trace2(3);                  // 相当于 trace(x3, d)  
//
//	return 0;
//}