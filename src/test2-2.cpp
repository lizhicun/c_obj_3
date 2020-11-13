/*************************************************************************
    > File Name: test2.cpp
    > Author: zhicun.li
    > Mail: lizhicun95@163.com 
    > Created Time: 2020年11月13日 星期五 11时42分34秒
 ************************************************************************/

#include<iostream>
#include<chrono>
using namespace std;

# define TIMEIT(cmd) do { \
	auto start_time = std::chrono::steady_clock::now(); \
	cmd; \
	auto end_time = std::chrono::steady_clock::now(); \
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time); \
	cout << #cmd << ": " << duration.count() * 1e3 << "ms" << endl; \
} while(0)

void func2() {
	struct Point {
		float x;
		float y;
		float z;
	};
	Point pA = {1.325, 0.875, 0.478};
	Point pB = {0.415, 0.317, 0.038};
	for (int iter = 0; iter < 10000000; iter++) {
		pB.x = pA.x - pB.z;
		pB.y = pA.y - pB.x;
		pB.z = pA.z + pB.y;
	}
	return;
}

int main() {
	// TIMEIT(func1);
	TIMEIT(func2);
	// TIMEIT(func3);
	return 0;
}
