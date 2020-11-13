/*************************************************************************
    > File Name: test0.cpp
    > Author: zhicun.li
    > Mail: lizhicun95@163.com 
    > Created Time: 2020年11月13日 星期五 11时06分08秒
 ************************************************************************/

#include<iostream>
using namespace std;
extern int x;
 
class A
{
public:
    //对于函数本体的分析将延迟，直至class申明的}出现时才开始。
    float X() const { return x; }
    float x;
};

int main() {
	A a;
	a.x = 1.111;
	cout << a.X();
	return 0;
}
