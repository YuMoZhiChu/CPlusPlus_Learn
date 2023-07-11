#include <iostream>
#include <string.h>
#include "vector"

using namespace std;

#define UABCCLASS()
#define ABCGENERATE_BODY()

class UBaseObject;

class FBaseClass
{
public:
	vector<int> params;
	// vector<int(int)> funcs;

	virtual UBaseObject* CreateObject()
	{
		return nullptr;
	}
};

template<class T>
class FBaseClassA : public FBaseClass
{
	virtual UBaseObject* CreateObject()
	{
		UBaseObject* newObject = new T();
		// 在这里 newObject 会对 params, 和 funcs 的函数进行注册, 其实就是把我的函数指针给过去
		return newObject;
	}
};

class UBaseObject
{
};

// 业务代码
UABCCLASS()
class USimpleControlABC : public UBaseObject
{
	ABCGENERATE_BODY()
//-->
public:
	static FBaseClass* StaticClass()
	{
		FBaseClassA<USimpleControlABC>* U = new FBaseClassA<USimpleControlABC>();
		return U;
	}

public:
	int Hello(int) {};
};

template<class T>
T* NewBaseObject(FBaseClass* InClass)
{
	return static_cast<T*>(InClass->CreateObject());
}

FBaseClass* temp = nullptr; 
int main()
{
	// 业务逻辑的注册
	temp = USimpleControlABC::StaticClass();
	USimpleControlABC* result = NewBaseObject<USimpleControlABC>(temp);

	int bk = 1;
}