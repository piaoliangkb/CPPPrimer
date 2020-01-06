<!-- TOC -->

- [ch1. The Basics](#ch1-the-basics)
    - [1.2 从源文件到可执行文件](#12-从源文件到可执行文件)
    - [1.3 main 函数的返回值](#13-main-函数的返回值)
    - [1.5 {} 初始化](#15--初始化)
    - [1.5 使用 auto 的场景](#15-使用-auto-的场景)
    - [1.6 不同的 scope](#16-不同的-scope)
    - [1.7 constexpr & const](#17-constexpr--const)
    - [1.8 range-for 范围 for 循环](#18-range-for-范围-for-循环)
- [ch2. User-Defined Types](#ch2-user-defined-types)
    - [2.4 Union](#24-union)
    - [2.5 带 class 的枚举和不带 class 的枚举](#25-带-class-的枚举和不带-class-的枚举)
- [ch3. Modularity](#ch3-modularity)
    - [3.4.1 noexcept](#341-noexcept)
    - [3.4.2 Invariants (不变式)](#342-invariants-不变式)
    - [3.4.3 Static Assertions](#343-static-assertions)

<!-- /TOC -->

## ch1. The Basics

### 1.2 从源文件到可执行文件

源文件编译为目标文件 (source_file -> compile -> object_file)

目标文件链接为可执行文件 (object_file -> link -> executable_file)

### 1.3 main 函数的返回值

程序会将 main 函数的返回值传递给系统。

- 如果 main 函数没有返回值，系统会收到一个返回值，表示已经成功执行完程序。

- 非零的返回值表示错误。

- Linux/Unix 系统通常会使用返回值，Windows 系统通常不会使用返回值。

### 1.5 {} 初始化

C++ 可以使用 {} (curly-brace0delimited initializer lists) 进行初始化，其中 `=` 是可选的（从 C
 语言继承而来）：

```cpp
double d1 = 2.3;
double d2 {2.3};
double d3 = {2.3}; // '=' is optional
vector<int> v {1, 2, 3, 4, 5};
```

- 最好选择 {} 来初始化变量，可以避免转换过程中的信息损失，比如 float 到 int 的转换损失了精度。例如：

```cpp
int i1 = 7.2;  // i1 becomes 7
int i2 {7.2};  // error, floting-point to integer conversion
int i3 = {7.2}; // error
```

类的初始化列表也可以使用 {}

```cpp
class Vector {
public:
    Vector(int s) : elem{new double[s]}, sz{s} {}
private:
    double *elem;
    int sz;
}
```

### 1.5 使用 auto 的场景

尽可能地使用 auto 来进行类型推导（尤其在泛型编程中来表达某个对象的类型）：

```cpp
auto b = true;
auto ch = 'x';
auto i = 123;
auto d = 1.2;  // double
auto z = sqrt(y);
```

1. 变量定义在一个很长的 scope 中，为了让类型表示的更清晰，不要使用 auto。

2. 想要明确一个变量的范围或者精度（例如，区分 double 和 float）。

### 1.6 不同的 scope

- local scope：定义在函数内，lambda 内的变量在 local scope 中（包括函数的参数）。

- class scope：在类内，并且在任何函数，lambda，或者枚举类之外的变量名在 class scope 中。

- namespace scope：在一个 namespace 之内，并且在任何函数，lambda，或者枚举类之外的变量在 namespace space 中。

- 没有定义在上述任何 scope 内的变量称为全局变量 (global)，且处于 global namespace。

```cpp
vector<int> vec;  // vec is global

struct Record {
    string name;  // name is a class member, in class scope 
};

void func(int args) { // func is global, args is local
    string motto {"Who dares win"};  // motto is local
}
```

### 1.7 constexpr & const

- const: 用户的保证 “我保证不会修改此变量”，编译器使用 const 来强制施行这个保证

- constexpr: 在编译期间评估某个对象（对性能比较友好），某个函数的返回值是否为常量。并将他们存储在只读内存中。

```cpp
const int dmv = 17;
int var = 17;

constexpr double max1 = 1.4 * square(dmv);    // true, square(17) is a constant expression
constexpr double max2 = 1.4 * square(var);    // error, var is not constant expression
const double max3 = 1.4 * square(var);        // true, evaluated at runtime

double sum(const vector<double> &);
vector<double> v {1.2, 3.4, 4.5};
const double s1 = sum(v);      // true, evaluated at runtime
constexpr double s2 = sum(v);  // error, sum(v) is not constant expression
```

上述 `constexpr double s2 = sum(v);` 为错误的语句。因为 `sum(v)` 并不是 constant expression。

- 若要定义一个函数为 constexpr，函数的要求为：

只有一个 return 语句（该语句可以计算一个值），即：唯一的可以执行语句是返回语句。

```cpp
constexpr double square(double x) { return x * x; }
constexpr int new_size() { return 42; }
constexpr int foo = new_size();  // true
```

若 constexpr 函数的参数不为 constexpr，则此时函数返回的结果也不为 constexpr。此做法是为了保证不需要为普通的变量重新定义一个类似的函数。

### 1.8 range-for 范围 for 循环

```cpp
int v[] = {0, 1, 2, 3, 4, 5, 6};
for (auto x : v) {
    cout << x << endl;
}

for (auto x : {10, 11, 12, 13}) {
    cout << x << endl;
}
```

## ch2. User-Defined Types

### 2.4 Union 

[cppreference union](https://zh.cppreference.com/w/cpp/language/union)

union 是一个结构体，该结构体所有的成员都被分配在同一个地址上。union 占用的地址为 union 中占用地址最大的成员 的地址。由于这些限制，union 一次只能表示一个成员。

使用 union 的场景：

```cpp
enum Type { str, num };

struct Entry {
    char *name;
    Type t;
    char *s;
    int i;
};
```

上述结构体中，当 t == str 的时候，使用 s；当 t == num 的时候，使用 i。

s 和 i 不可能同时被使用，浪费了空间。所以可以把 s 和 i 放到一个 union 的内部。

```cpp
union Value {
    char *s;
    int i;
};
```

此时的 struct 为：

```cpp
struct Entry {
    char *name;
    Type t;
    Value v;
};
```

使用方法为：

```cpp
void f(Entry *p) {
    if (p->t == str) cout << p->v.s;
    if (p->t == num) cout << p->v.i;
}
```

### 2.5 带 class 的枚举和不带 class 的枚举

建议使用 class enums

- 带 class 的枚举，例如：

```cpp
enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };
```

枚举中的各项都在各自的 scope 内。

如下的转换是不可发生的：

```cpp
int i = Color::red;    // error
```

可以进行运算符重载：

```cpp
Traffic_light &operator++(Traffic_light &t) {
    switch(t) {
        case Traffic_light::green : return t = Traffic_light::yellow;
        case Traffic_light::yellow : return t = Traffic_light::red;
        case Traffic_light::red : return t = Traffic_light::green;
    }
}
```

- 不带 class 的枚举：

如果不显式地限定枚举名字，并且想让枚举值为 int，可以删去 enum 后的 class。

不带 class 的枚举都在同一个 scope 内：

```cpp
enum Color { red, green, blue };
enum Traffic_color { red, yellow, green };

/*
tempCodeRunnerFile.cpp:4:22: error: redefinition of enumerator 'red'
enum Traffic_color { red, yellow, green };
                     ^
tempCodeRunnerFile.cpp:3:14: note: previous definition is here
enum Color { red, green, blue };
             ^
tempCodeRunnerFile.cpp:4:35: error: redefinition of enumerator 'green'
enum Traffic_color { red, yellow, green };
                                  ^
tempCodeRunnerFile.cpp:3:19: note: previous definition is here
enum Color { red, green, blue };
*/
```

可以转换为 int：

```cpp
enum Color { red, green, blue };
int col = green;  // col = 1, red = 0, blue = 2
```

## ch3. Modularity

### 3.4.1 noexcept

不应该抛出异常的函数应该声明为 noexcept：

```cpp
void user(int sz) noexcept {
    Vector v(sz);
    iota(&v[0], &v[sz], 1);
}
```

上述的 user 函数如果仍然抛出异常，则会调用标准库函数 `terminate()` 来中断程序。

### 3.4.2 Invariants (不变式)

>In OOP, an invariant is a set of assertions that must always hold true during the life of an object for the program to be valid. It should hold true from the end of the constructor to the start of the destructor whenever the object is not currently executing a method that changes its state.
>
>https://softwareengineering.stackexchange.com/questions/32727/what-are-invariants-how-can-they-be-used-and-have-you-ever-used-it-in-your-pro

对于一个 Vector 类的 operator[](int) 运算符，我们需要在运算符重载函数中检测给出的参数是否越界。

对于 Vector 类的构造函数，我们能够检查的只有给定 size 参数是否为负：

```cpp
Vector v(-27);  // error
```

在用户代码中，需要这么处理异常：

```cpp
// Vector 构造函数
Vector::Vector(int s) {
    if (s < 0) throw std::length_error{};
    elem = new double[s];
    sz = s;
}

void test() {
    try {
        Vector v(-27);
    }
    catch (std::length_error) {
        // .. handle this exception
        throw;  // need to rethrow
    }
    catch (std::bad_alloc) {
        // .. handle memory exhaustion
        std::terminate();  // terminate the program
    }
}
```

不变式的概念对类的设计至关重要，前置条件对函数的设计也至关重要。

不变式：

- 帮助准确理解我们想要什么

- 强制我们对类做一些特化——从而让我们的代码更准确

### 3.4.3 Static Assertions

exceptions 在运行期间被抛出。

`static_assert` 可以在编译期间抛出错误，例如：

```cpp
static_assert(4<=sizeof(int), "integers are too small");
```

如果 sizeof(int) >= 4 不成立，则会抛出错误。

- static_assert 语法：

>https://zh.cppreference.com/w/cpp/language/static_assert

`static_assert(bool_constexpr, message)` 前一个参数必须是 constexpr，后一个参数必须是字符串常量 (string literal)，不能是任何其他动态信息。

当 bool_constexpr 不为真时，打印 message。

```cpp
constexpr double C = 29999.99;

void f(double speed) {
    const double local_max = 160.0 / (60.0 * 60.0);
    static_assert(speed<C, "cannot go that fast");          // error, speed must be a constant
    static_assert(speed<local_max, "cannot go that fast");  // true
}
```