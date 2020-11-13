/*************************************************************************
    > File Name: test1.cpp
    > Author: zhicun.li
    > Mail: lizhicun95@163.com 
    > Created Time: 2020年11月13日 星期五 10时57分48秒
 ************************************************************************/

#include<iostream>
using namespace std;

typedef int length;

class Point3d{
public:
	void f1(length l){ cout << l << endl; }
	typedef string length;
	void f2(length l){ cout << l << endl; }
};

int main() {
	Point3d p;
	p.f1(123);
	// p.f1("123");
	// p.f2(123);
	p.f2("123");
	return 0;
}
