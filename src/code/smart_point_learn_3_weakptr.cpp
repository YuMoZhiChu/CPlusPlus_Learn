//#include<iostream>
//using namespace std;
//
//weak_ptr<int> gw;
//
//void f()
//{
//	if (auto spt = gw.lock()) { // ʹ��֮ǰ���븴�Ƶ� shared_ptr
//		std::cout << *spt << "\n";
//	}
//	else {
//		std::cout << "gw is expired\n";
//	}
//}
//
//int main()
//{
//	{
//		auto sp = make_shared<int>(42);
//		gw = sp;
//
//		f();
//	}
//
//	f();
//}