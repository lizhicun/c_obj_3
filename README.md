# c_obj_3
这章大概是讲class中成员变量的布局和存取

3.1 Data Member 的绑定（The Binding of a Data Member）
“member rewriting rule”规则，大意是“一个 inline 函数实体，在整个 class 未被完全看见之前，是不会被评估求值（evaluated）的”
举了个例子
```
hahaha
```
然而，对于 member function 的 argument list 并不是这样，Argument list 中的名词还是会在第一次遇到时就被决议（resolved）完成
又举了个例子
```
dadada
```
所以对于 nested type（typedef）的声明，还是应该放在 class 的起始处。

3.2 Data Member 的布局（Data Member Layout）
Nonstatic data member 在 class object 中的排列顺序和其被声明的顺序一样
static data member 都不会放进对象布局中。static data member 放在程序的 data segment 中。
同一个 access section 中，member 的排列只需符合“较晚出现的 member 在 class object 中有较高的地址”即可，而 member 并不一定要连续排列（alignment 可能就需要安插在当中）。
编译器可能合成一些内部使用的 data member，比如 vptr，vptr 传统上放在所有明确声明的 member 之后，不过也有一些编译器把 vptr 放在 class object 的最前端（放在中间都是可以的）。
各个 access section 中的 data member 也可自由排列，不必在乎顺序，但目前各家编译器都是把一个以上 access sections 按照声明的次序放在一起的。section 的数量不会有额外的负担。

3.3 Data Member 的存取
```
Point3d origin, *pt = &origin;

origin.x = 0.0;
pt->x = 0.0;
```
通过 origin 存取和通过 pt 存取，有什么重大差异吗？

Static Data Members
```
// origin.chunkSize = 250;
Point3d::chunkSize = 250;
// pt->chunkSize = 250;
Point3d::chunkSize = 250;
```
Static data member 被编译器提出于 class 之外，并被视为 global 变量（但只在 class 的范围内可见），其存取效率不会受 class object 的影响，不会有任何空间或时间上的额外负担。

Nonstatic Data Members
要想对 nonstatic data member 进行存取，编译器需要把 class object 的起始地址加上一个 data member 的偏移量（offset）：
```
origin._y = 0.0;
```
那么地址 &origin._y 就等于：
```
&origin + (&Point3d::_y - 1);
```

3.4 继承与DataMenber
有如下两个抽象数据类型：
```
// supporting abstract data types
class Point2d {
 public:
  // constructor(s)
  // operations
  // access functions
 private:
  float x, y;
};

class Point3d {
 public:
  // constructor(s)
  // operations
  // access functions
 private:
  float x, y, z;
};
```
下图就是 Point2d 和 Point3d 的对象布局，在没有 virtual function 的情况下，它们和 C struct 完全一样：
[图]
下面讨论 Point 的“单一继承且不含 virtual function”、“单一继承含 virtual function”、“多重继承”、“虚拟继承”等四种情况。
1. 只要继承不要多态（Inheritance without Polymorphism）
```
class Point2d {
 public:
  Point2d(float x = 0.0, float y = 0.0) : _x(x), _y(y){};
  float x() {
    return _x;
  }
  float y() {
    return _y;
  }
  void x(float newX) {
    _x = newX;
  }
  void y(float newY) {
    _y = newY;
  }
  void operator+=(const Point2d& rhs) {
    _x += rhs.x();
    _y += rhs.y();
  }
  // ... more members
 protected:
  float _x, _y;
};

// inheritance from concrete class
class Point3d : public Point2d {
 public:
  Point3d(float x = 0.0, float y = 0.0, float z = 0.0) : Point2d(x, y), _z(z){};
  float z() {
    return _z;
  }
  void z(float newZ) {
    _z = newZ;
  }
  void operator+=(const Point3d& rhs) {
    Point2d::operator+=(rhs);
    _z += rhs.z();
  }
  // ... more members
 protected:
  float _z;
};
```
Point2d 和 Point3d 的继承关系如下图所示
[图]
有个容易犯的错误是把一个 class 分解为两次或更多层，这样可能会导致所需空间的膨胀。
C++ 语言保证“出现在 derived class 中的 base class subobject 有其完整原样性”，结合以下代码理解。
```
class Concrete {
 public:
  // ...
 private:
  int  val;
  char c1;
  char c2;
  char c3;
};
```
其内存布局如下，共占用 8 bytes：
[图]

现在，将 concrete 分裂成三层结构：
```
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
```
现在，Concrete3 object 的大小是 16 bytes！下面是内存布局图：
[图]

为什么要这样，让我们声明以下一组指针：
```
Concrete2 *pc2;
Concrete1 *pc1_1, *pc1_2;
```
如下赋值操作：
```
*pc1_2 = *pc1_1;
```
应该执行 memberwise 复制操作，那么，如果把 pc1_1 指向一个 Concrete2 object，则上述操作会将 Concrete2 的内容复制给 Concrete1 subobject：
```
pc1_1 = pc2;
*pc1_2 = *pc1_1;
```
[图]
也就是说，把一个 Concrete1 复制给 Concrete2 时，Concrete2 原本的 bit2 的值被修改了。

加上多态（Adding Polymorphism）
简单讲了
加上多态带来了以下负担：
导入一个和 Point2d 有关的 virtual table，这个 table 的元素数目一般而言是 virtual function 的数目在加上 1 或 2 个 slots（用来支持 runtime time identification）。
在每个 class object 中导入 vptr，提供执行期的链接。
加强 constructor，用来为 vptr 设定初值。
加强 destructor， 用来消除 vptr。
具体的在4.4中讨论

多重继承（Multiple Inheritance）
考虑如下图所示的继承体系
[图]
其中，Point2d 与 Point3d 和 Vertex 都有 virtual function 接口。它们的数据布局如下图所示：
[图]
多重继承的问题主要发生于 derived class object 和其第二或后继的 base class object 之间的转换，对一个多重派生对象，将其地址指定给“最左端（也就是第一个）base class 的指针”，情况和单一继承一样，因为它们有相同的地址。而第二或后继的 base class 起始的地址，则与 derived class 不同（可以在上图中看出，Vertex 在 Point3d 后面）。所以如下操作：
```
Vertex3d v3d;
Vertex *pv;
Point3d *p2d;
Point3d *p3d;

// 如下指定操作：
pv = &v3d;
```
会被转换为：
```
// 伪码
pv = (Vertex*)(((char*)&v3d) + sizeof(Point3d));
```
而下面的指定操作：
```
p2d = &v3d;
p3d = &v3d;
```
只需见到拷贝其地址即可。


对象成员的效率（Object Member Efficiency）
```
hahhahahah
```
直接看表吧：
[图]
[图]

指向 Data Members 的指针（Pointer to Data Members）
```
class Point3d {
 public:
  virtual ~Point3d();
  // ...
 protected:
  static Point3d origin;
  float          x, y, z;
};
```
那么，取某个坐标成员的地址：
```
&Point3d::z;
```
实际上得到的是 z 坐标在 class object 中的偏移量（offset）。其最小值是 x 和 y 的大小总和，因为 C++ 要求同一个 access level 中的 member 的排列次序应该和其声明次序相同。
如果 vptr 在对象的尾端，则三个坐标值的 offset 分别是 0，4，8。如果 vptr 在对象起头，则三个坐标值的 offset 分别是 4，8，12。然而若去取 data member 的地址，传回值总是多 1，也就是 1，6，9 或 5，9，13。这是为了区分一个“没有指向任何 data member”的指针和一个指向“第一个 data member” 的指。
现在，可以很容易知道下面两者的区别：
```
&Point3d::z;
&origin.z;
```

“指向 Members 的指针”的效率问题
直接看结果吧：
[图]\[图]
由于虚拟继承引入的间接性，每次存取 Point::x （pB 是一个虚基类）：
```
pB.*bx
```
会被转化为（这里的虚拟继承采用了前面说的第一种策略：直接安插一个指针指示 base class）：
```
&pB->__vbcPoint + (bx - 1);
```
而不是最直接的（单一继承）：
```
&pB + (bx - 1);
```
