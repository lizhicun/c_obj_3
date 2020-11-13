/*************************************************************************
    > File Name: test4.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年11月13日 星期五 14时35分02秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Point3d {
public:
	float x, y, z;
};

int main() {
	cout << &Point3d::x;
	cout << &Point3d::y;
	cout << &Point3d::z;
	
	Point3d origin;
	cout << &(origin.z);
	return 0;
}
