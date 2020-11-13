/*************************************************************************
    > File Name: test3.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年11月13日 星期五 14时03分57秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Concrete {
 public:
  // ...
 private:
  int  val;
  char c1;
  char c2;
  char c3;
};

class Concrete1 {
 public:
  // ...
 protected:
  int  val;
  char bit1;
};

class Concrete2 : public Concrete1 {
 public:
  // ...
 protected:
  char bit2;
};

class Concrete3 : public Concrete2 {
 public:
  // ...
 protected:
  char bit3;
};

int main(){
	Concrete c;
	cout << sizeof(c);

	Concrete3 c3;
	cout << sizeof(c3);

	// Concrete1 *pc1 = new Concrete1();
	// Concrete2 *pc2 = dynamic_cast<Concrete2*>(pc1);
	return 0;
}
