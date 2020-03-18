//#include<iostream>
//
//class B
//{
//public:
//	void pbB() {}
//	int pbA;
//protected:
//	void ptB() {}
//	int ptA;
//private:
//	void pvB() {}
//	int pvA;
//};
//
//class C : public B
//{
//	void f()
//	{
//		pbB();
//		ptB();
//		pvB();
//
//		pbA;
//		ptA;
//		pvA;
//	}
//};
//
//void g_C(C& temp)
//{
//	temp.pbB();
//	temp.ptB();
//	temp.pvB();
//}
//
//class D : protected B
//{
//	void f()
//	{
//		pbB();
//		ptB();
//		pvB();
//
//		pbA;
//		ptA;
//		pvA;
//	}
//};
//
//void g_D(D& temp)
//{
//	temp.pbB();
//	temp.ptB();
//	temp.pvB();
//}
//
//class E : private B
//{
//	void f()
//	{
//		pbB();
//		ptB();
//		pvB();
//
//		pbA;
//		ptA;
//		pvA;
//	}
//};
//
//void g_E(E& temp)
//{
//	temp.pbB();
//	temp.ptB();
//	temp.pvB();
//}
//
//int main()
//{
//	std::cout << "hello world" << std::endl;
//}
