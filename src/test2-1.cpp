/*************************************************************************
    > File Name: test2-1.cpp
    > Author: zhicun.li
    > Mail: lizhicun95@163.com 
    > Created Time: 2020年11月13日 星期五 12时15分19秒
 ************************************************************************/

#include<iostream>
using namespace std;

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


void func1() {
    float pA_x = 1.125, pA_y = 0.875, pA_z = 0.478;
    float pB_x = 0.215, pB_y = 0.317, pB_z = 0.838;
    for (int iter = 0; iter < 10000000; iter++) {
	    pB_x = pA_x - pB_z;
	    pB_y = pA_y + pB_x;
	    pB_z = pA_z + pB_y;
	}
	return ;
}

int main() {
	TIMEIT(func1);
	// TIMEIT(func2);
	// TIMEIT(func3);
	return 0;
}

