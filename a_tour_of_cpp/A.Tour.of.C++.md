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
- [ch4. Classes](#ch4-classes)
    - [4.2 Concrete Types 具象类（非抽象类）](#42-concrete-types-具象类非抽象类)
    - [4.2.1 const 修饰符的另一种理解](#421-const-修饰符的另一种理解)
    - [4.2.3 initializer_list\<T\> & static_cast](#423-initializer_list\t\--static_cast)
    - [4.3 Abstract Types 抽象类](#43-abstract-types-抽象类)
    - [4.4 虚函数表 virtual function table (vtbl)](#44-虚函数表-virtual-function-table-vtbl)
    - [4.5.2 类的层次结构（继承，派生）的好处](#452-类的层次结构继承派生的好处)
    - [4.5.3 dynamic_cast 待理解](#453-dynamic_cast-待理解)
    - [4.5.4 使用 unique_ptr 避免资源泄露](#454-使用-unique_ptr-避免资源泄露)
    - [4.6.2 move constructor](#462-move-constructor)
    - [4.6.3 类中都需要定义哪些成员函数](#463-类中都需要定义哪些成员函数)
    - [4.6.3 when an object is copied or moved](#463-when-an-object-is-copied-or-moved)
    - [4.6.4 C++ 中使用 RAII 的地方 (pervasice 普遍的)](#464-c-中使用-raii-的地方-pervasice-普遍的)
    - [4.6.7 继承体系中不要使用默认的拷贝或移动操作 (delete)](#467-继承体系中不要使用默认的拷贝或移动操作-delete)
    - [4.7 总结（重要！）](#47-总结重要)
- [ch5. Templates](#ch5-templates)
    - [5.2 模板是编译期机制，没有运行期损耗](#52-模板是编译期机制没有运行期损耗)
    - [5.2 模板的 value arguments](#52-模板的-value-arguments)
    - [5.3 一个简单的计算 Container 的 sum 模板](#53-一个简单的计算-container-的-sum-模板)
    - [5.5 函数对象模板 和 lambda](#55-函数对象模板-和-lambda)
    - [5.6 可变参数模板（占坑）](#56-可变参数模板占坑)
    - [5.8 Template Compilation Model （占坑）](#58-template-compilation-model-占坑)
    - [5.9 总结](#59-总结)
- [ch7. Strings and Regular Expressions](#ch7-strings-and-regular-expressions)
    - [7.2.1 basic_string<char>](#721-basic_stringchar)
    - [7.3 正则表达式（占坑）](#73-正则表达式占坑)
- [ch8. I/O Streams](#ch8-io-streams)
    - [8.1 istream & ostream](#81-istream--ostream)
    - [8.5 读入 "{ "name", number }" 类型的数据示例](#85-读入--name-number--类型的数据示例)
    - [8.6 cout 各种格式化方式](#86-cout-各种格式化方式)
- [ch9. Containers](#ch9-containers)
    - [9.2 vector 的成员](#92-vector-的成员)
    - [9.2 capacity & size 的含义](#92-capacity--size-的含义)
    - [9.2 继承 std::vector<T>](#92-继承-stdvectort)
    - [9.3 list 的特性和使用情况](#93-list-的特性和使用情况)
    - [9.4 map 的底层结构](#94-map-的底层结构)
    - [9.5 unordered_map](#95-unordered_map)
    - [9.6 多用 vector 而不是 list](#96-多用-vector-而不是-list)
    - [9.6 forward_list （?）](#96-forward_list-)
    - [9.7 传递 container 的引用，返回 container 的值](#97-传递-container-的引用返回-container-的值)
- [ch10. Algorithms](#ch10-algorithms)
    - [10.2 find_all（C++ 标准库没有 find_all 方法噢）](#102-find_allc-标准库没有-find_all-方法噢)
    - [10.3 iterator 的实现](#103-iterator-的实现)
    - [10.4 Stream Iterators （示例代码很精简）](#104-stream-iterators-示例代码很精简)
- [ch11. Utilities](#ch11-utilities)
    - [11.2 RAII](#112-raii)
    - [11.2.1 使用可变参数模板实现的 make_unique](#1121-使用可变参数模板实现的-make_unique)
    - [11.3 特定容器（占坑）](#113-特定容器占坑)
    - [11.3.1 array 的性质](#1131-array-的性质)
    - [11.3.2 bitset（占坑）](#1132-bitset占坑)
    - [11.3.3 make_pair](#1133-make_pair)
    - [11.3.3 创建 tuple 并获得 tuple 的元素](#1133-创建-tuple-并获得-tuple-的元素)
    - [11.4 std::chrono & time](#114-stdchrono--time)
    - [11.5 函数参数绑定 (bind, mem_fn)](#115-函数参数绑定-bind-mem_fn)
    - [11.6 类型函数 type functions](#116-类型函数-type-functions)
    - [11.6.1 iterator_traits（占坑）](#1161-iterator_traits占坑)
    - [11.6.2 type predicates 类型谓词](#1162-type-predicates-类型谓词)
- [ch12. Numerics](#ch12-numerics)
    - [12.2 cmath 中的数学函数](#122-cmath-中的数学函数)
    - [12.5 随机数生成](#125-随机数生成)
    - [12.6 支持算术运算的 vector —— valarray](#126-支持算术运算的-vector--valarray)
- [ch13. Concurrency](#ch13-concurrency)
    - [13.2 task & threads](#132-task--threads)
    - [13.3 传递给 thread 参数](#133-传递给-thread-参数)
    - [13.4 传递给 thread 参数来获得返回结果](#134-传递给-thread-参数来获得返回结果)
    - [13.5 使用 mutex 来访问共享数据](#135-使用-mutex-来访问共享数据)
    - [13.5 手动 lock() 操作获取多个锁](#135-手动-lock-操作获取多个锁)
    - [13.6 condition_variable](#136-condition_variable)
    - [13.7 task 通信机制](#137-task-通信机制)
    - [13.7.1 future & promise](#1371-future--promise)
    - [13.7.2 packaged_task 将 future & promise 和 task 相关联](#1372-packaged_task-将-future--promise-和-task-相关联)
    - [13.8 async()](#138-async)

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

## ch4. Classes

### 4.2 Concrete Types 具象类（非抽象类）

Concrete Types (和 abstract types 相对) 的几个特点：

- 可以放在 stack 上，静态分配的内存中，或者其他对象中

- 不需要用指针或者引用来指向某个对象，直接代表某个对象

- 使用构造函数立即并完全初始化对象

- 可以拷贝对象

对一个 Concrete Types 来说，它的 representation 可以是私有的（即类的实现作为私有成员）。如果这样的话，如果 **类的 representation 改变**，那么用户必须 **重新编译**。

为了提升灵活性 (flexibility)，一个 Concrete Types 可以把它的实现放在 **heap (动态分配的内存中)**，通过类内部的 handles 来访问它。(pimpl idiom)

### 4.2.1 const 修饰符的另一种理解

在如下类中：

```cpp
class complex {
private:
    double re, im;
public:
    void real() const { return re; }
    void imag() const { return im; }
};
```

- 函数添加 const 修饰符之后可以作用于 const 类对象。

- const 修饰符也表示了 **函数不会修改调用它的对象 (do not modify the objects for which they are called)**

### 4.2.3 initializer_list\<T\> & static_cast

对于一个 Vector 类，构造函数接受一个 initializer_list\<T> 参数来初始化成员：

```cpp
class Vector {
public:
    Vector(std::initializer_list<double>);
private:
    double *elem;
    int sz;
};
```

构造函数的定义为：

```cpp
Vector::Vector(std::initializer_list<double> lst)
    : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} 
{
    copy(lst.begin(), lst.end(), elem);
}
```

`sz` 的初始化使用了 static_cast 的原因是 lst 初始化列表的长度可能大于 int 的最大值。

**`static_cast` 不检查它正在转换的值，它相信编程者会正确的使用这个函数。最好避免显式的转换，而是使用哪些设计好的库来避免 unchecked cast。**

### 4.3 Abstract Types 抽象类

- 我们不知道抽象类的 representation（size 也不知道）。

- 必须在 heap 上分配对象所占的内存。

- 只能通过指针或者引用来访问对象。

- 抽象类不含有构造函数。

- 抽象类的析构函数为虚函数。

**拥有纯虚函数的类是抽象类**

例如一个 Container 类：

```cpp
class Container {
public:
    virtual double &operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};
```

一个 Container 的派生类 List：

```cpp
class List_container : public Container {
private:
    std::list<double> ld;
public:
    List_container() {}

    List_container(std::initializer_list<double> il) : ld{il} {}

    ~List_container() {}

    double &operator[](int i);
    int size() const { return ld.size(); }
};

double &List_container::operator[](int i) {
    for (auto &x : ld) {
        if (i == 0) return x;
        --i;
    }
    throw out_of_range("List container");
}
```

如下的 use 函数可以使用 Container 的派生类：

```cpp
void use(Container &c) {
    const int sz = c.size();
    
    for (int i=0; i!=sz; ++i) {
        cout << c[i] << '\n';
    }
}
```

提供上述 `size()` 和 `operator[](int)` 接口的类型叫做 **多态类型 (polymorphic type)**

### 4.4 虚函数表 virtual function table (vtbl)

上述的 Container 类必须在运行期间知道自己要调用的函数。最常规的实现方法是：编译器将虚函数的名字转换为虚函数表中的索引，这个表中包含了指针，指针指向要调用的函数。

<img src="https://csozqa.dm.files.1drv.com/y4mU45hVYmfkhQE35Eat1OcTnS14fzKHl-TGDbrnRGac5MHy0Gk3kPyB8txWPxEVW_UtbUc_47U-FkSPPu2eUwmigxXH8bllSPRZ_Ru5HXjXw8oAHNewCSW0L0lj77YtFXVMiMIDJqW0iZJBESpFpfoIEnqfCqgpBaoHxcs9zAWmbt4Pukxga55jyTf1hfwMNwtVpYBeLBC9pfeK1RcFVtRRQ?width=1359&height=612&cropmode=none" width="600" height="300" />

虚函数表中的函数让对象被正确的使用，即使 caller 不知道对象的大小，不了解数据的 layout。

caller 的实现方只需要知道 **指向 vtbl 的指针的位置** 和 **每个虚函数的 index**。

每个含有虚函数的类都会拥有 **一个额外的指针** 和 **一个 vtbl**。

### 4.5.2 类的层次结构（继承，派生）的好处

- 接口继承：一个派生类对象总是可以当作一个基类对象被使用。

- 实现继承：一个基类会提供函数和数据成员给派生类使用，简化了派生类的实现。

### 4.5.3 dynamic_cast 待理解

### 4.5.4 使用 unique_ptr 避免资源泄露

上文中的 read_shape 方法的实现为：

```cpp
enum class Kind { circle, triangle, smiley };

Shape *read_shape(istream &is) {
    // ...

    switch(k) {
        case Kind::circle:
            return new Circle{p, r};
        case Kind::triangle:
            return new Triangle{p1, p2, p3};
        case ...
    }
}
```

该方法可能会导致资源泄露：read_shape 函数返回的指针没有被 delete。

可以使用 unique_ptr 替换内置指针：

```cpp
unique_ptr<Shape> read_shape(istream &is) {
    // ...
    
    switch(k) {
        case Kind::circle:
            return unique_ptr<Shape>{new Circle{p, r}};
        case ...
    }
}
```

### 4.6.2 move constructor

```cpp
Vector::Vector(Vector &&a)
    : elem{a.elem}, sz{s.sz}  // why not use std::move?
{
    a.elem = nullptr;
    a.sz = 0;
} 
```

发生 move 的地方：

```cpp
Vector f() {
    Vector x(1000);
    Vector y(1000);
    Vector z(1000);
    z = x;             // copy
    y = std::move(x);  // move
    return z;          // move
}
```

### 4.6.3 类中都需要定义哪些成员函数

如果一个类定义了带有某些操作的析构函数 (nontrivial task)，则这个类最好提供所有的成员函数：

```cpp
class X {
public:
    X(sometype);
    X();

    X(const X &);
    X &operator=(const X &);

    X(X &&);
    X &operator=(X &&);

    ~X();
};
```

当一个类含有 **指针或者引用成员** 的时候，最好显式地写出 **拷贝和移动** 操作。

### 4.6.3 when an object is copied or moved

- 作为赋值中的 source

- 作为对象的 initializer

- 作为函数参数

- 作为函数的返回值

- 作为一个异常 (as an exception)

### 4.6.4 C++ 中使用 RAII 的地方 (pervasice 普遍的)

- memory: string, vector, mep. unordered_map

- files: ifstream, ofstream

- threads: thread

- locks: lock_guard, unique_lock

- general objects: unique_ptr, shared_ptr

### 4.6.7 继承体系中不要使用默认的拷贝或移动操作 (delete)

给定一个基类的指针指向派生类，但是不知道派生类有哪些成员，所以我们不知道如何拷贝这些成员。

所以最好的解决方式是：让基类的拷贝和移动操作都为 delete 的。

```cpp
class Shape {
public:
    Shape(const Shape &) = delete;
    Shape &operator=(const Shape &) = delete;

    Shape(Shape &&) = delete;
    Shape &operator=(Shape &&) = delete;

    ~Shape();
};
```

此时如果想拷贝某个对象，写一个 virtual clone function。（？）

忘记将拷贝或者移动操作定义为 delete 的也没关系。**在一个定义了析构函数的类中，移动操作不会隐式生成。**

### 4.7 总结（重要！）

28. 如果一个类有析构函数，那么它的拷贝和移动操作要么是 用户定义的 (user-defined)，要么是 删除的 (deleted)。

32. 默认的，将单参数的构造函数声明为 explicit 的。

33. 如果一个类有指针或者引用成员，那么这个类需要一个析构函数和用户定义的拷贝操作。

35. 如果某个类是一个 resource handle，那么这个类需要构造函数，析构函数，用户定义的(non-default) 的拷贝操作。

## ch5. Templates

### 5.2 模板是编译期机制，没有运行期损耗

Templates are compile-time mechanism. Their use incurs no run-time overhead compared to hand-crafted code. (手搓的函数)

### 5.2 模板的 value arguments

```cpp
template<typename T, int N>
struct Buffer {
    using value_type = T;
    constexpr int size() { return N; }
    T[N];
    // ...
};
```

上述的 N 为模板的 value arguments，它让用户可以创建不同参数的 buffers 而 **不需要在运行期间动态分配内存 (dynamic memory)。**

- 模板的 value arguments 必须是 **常量表达式 (constant expression)**

例如：

```cpp
Buffer<char, 1024> glob;  // statically allocated

void func() {
    Buffer<int, 10> buf;  // on the stack
}
```

### 5.3 一个简单的计算 Container 的 sum 模板

```cpp
template<typename Container, typanem Value>
Value sum(const Container &c, Value v) {
    for (auto x : c) {
        v += x;
    }
    return v;
}
```

对该函数模板的使用：

```cpp
void user(Vector<int> &vi, std::list<double> &ld, std::vector<complex<double>> &vc) {
    double d = sum(vi, 0.0);  // sum of a vector of ints, 使用 double 的原因是 int 和 int 相加可能会产生超过最大 int 的整数

    double dd = sum(ld, 0.0);

    auto z = sum(vc, complex<double>{});
}
```

### 5.5 函数对象模板 和 lambda

定义一个比较大小的函数对象模板

```cpp
template<typename T>
class Less_than {
private:
    const T val;
public:
    Less_than(const T &v) : val(v) {}

    bool operator()(const T &x) const { return x < val; }
};
```

可以根据该模板定义一些函数对象用来比较参数和类内给定值：

```cpp
Less_than<int> lti {42};  // lti(i) compare i to 42 using <
Less_than<string> lts {"Backus"};  // lts(s) compare s to "Backus" using <
```

函数对象模板通常用作算法的参数,例如对于一个统计计数的函数，其中 P 可以传入 **函数对象**，或者 **lambda**：

```cpp
template<typename C, typename P>
int count(const C &c, P pred) {
    int cnt = 0;
    for (const auto &x : c) {
        if (pred(x)) {
            ++cnt;
        }
    }
    return cnt;
}

// call of this func
void f(const Vector<int> &vec, const list<string> &lst, int x, const string &s) {
    count(vec, Less_than<int>{x});
    count(lst, Less_than<string>{s});
}

void f1(const Vector<int> &vec, const list<string> &lst, int x, const string &s) {
    count(vec, [&](int a){ return a < x; });
    count(lst, [&](const string &str){ return str < s; });
}
```

### 5.6 可变参数模板（占坑）

### 5.8 Template Compilation Model （占坑）

### 5.9 总结

6. Templates are type-safe, but checking happeds too late.(?)

11. Use concepts as a design tool.(?)

14. A virtual function member cannot be a template member function.

17. Donot use variadic templates for homogeneous argument lists(prefer initializer list)(?)

18. To use a template, make sure its definition (not just its declaration) is in scope.

## ch7. Strings and Regular Expressions

### 7.2.1 basic_string<char>

我们平时使用的 string 是：`basic_string<char>`：

```cpp
template<typename Char>
class basic_string {
    // ...
};

using string = basic_string<char>;
```

### 7.3 正则表达式（占坑）

## ch8. I/O Streams

### 8.1 istream & ostream

- ostream 将类型对象 (typed objects) 转换为字节流：

<img src="https://ccozqa.dm.files.1drv.com/y4mrhRyjV_L_WKVfNaatabLaPJU8lujrNcL4QwPIJAR607i8s5m-_gt_y1KY-ML7hbhrV7kFZJQQ-9zBC9buVWeUFS4qtGYsGHge6naBppfxKAH34PAH4A-2XkcNEi9-w-4nJQMHy9QrgJiD79dSyEd1p6xB9O6i7XlM6AAkuszozOO9xXEdadnXootKgPTHSEpWEIlvYBg_btcwO5IQkIWKg?width=660&height=167&cropmode=none" width="660" height="167" />

- istream 将字节流转换为类型对象：

<img src="https://byozqa.dm.files.1drv.com/y4muHB54SRUZE5hmAIQ1_62catc4g2lpwMvraTOZkdIr7aPH1xCkXZGdChCi73-E38SwtgBv05skAojcZVe52AvQNS1zCeD2W4wHPjhSczIkb_jvy1NoF25dyf3zRYoS1tteXLqCsAezfFBbNOFSouhwQ8VqRvtgj5BO4U9vYJNdW8QQ4dTDBL1Ns7tHVjVU9zaaiwyzsMsHAXnMfKXjZgKdw?width=660&height=161&cropmode=none" width="660" height="161" />

### 8.5 读入 "{ "name", number }" 类型的数据示例

```cpp
// read data like { "name", number } into e
istream &operator>>(istream &is, Entry &e) {
    char c, c2;
    if (is >> c && c == '{' && is >> c2 && c2 == '"') {
        string name;
        while (is.get(c) && c != '"')
            name += c;
        
        if (is >> c && c == ',') {
            int number = 0;
            if (is >> number >> c && c == '}') {
                e = { name, number };
                return is;
            }
        }
    }
    is.setstate(ios_base::failbit);
    return is;
}
```

### 8.6 cout 各种格式化方式

```cpp
// 1234, 4d2, 2322
cout << 1234 << " " << hex << 1234 << " " << oct << 1234 << endl;
```

上述分别为 十进制，十六进制，八进制。

```cpp
constexpr double d = 123.456;

cout << d;  // default format
cout << scientific << d; // 1.1234560e+002 科学计数法
cout << hexfloat << d;   // 十六进制
cout << fixed << d;      // 123.456000
cout << defaultfloat << d; // default format
```

- defaultfloat: style that best preserves the value in the space avaliable. 精度 (precision) 指定为最大位数。

- scientific: one digit before a decimal point and an exponent. 精度指定为小数点后的最大位数。

- fixed: an integer part followed by a decimal point and a fractional (小数的) part. 精度指定为小数点后的最大位数

`cout.precision(n)` 设置了精度。精度不会影响整形的输出：

```cpp
cout.precision(8);
cout << 1234.56789 << " " << 123456;
// 1234.5679 123456

cout.precision(4);
cout << 1234.56789 << " " << 123456;
// 1235 123456
```

## ch9. Containers

### 9.2 vector 的成员

- elem: pointers to the first element

- space: one past the last element

- last: one past the last allocated space

- alloc: allocator，vector 从这里为它的 element 申请内存

### 9.2 capacity & size 的含义

- capacity: 在不重新分配内存空间的情况下，最多保存的元素个数。

- size: 已经保存的元素数目。

### 9.2 继承 std::vector<T>

```cpp
template<typename T>
class Vec: public std::vector<T> {
public:
    using std::vector<T>::vector;  // use the constructor from std::vector<T>

    T &operator[](int i) { return std::vector<T>::at(i); }

    const T &operator[](int i) const { return std::vector<T>::at(i); }
};
```

上述定义的 Vec 和 std::vector 相比带有越界检测：

```cpp
Vec<int> v {1, 2, 3, 4, 5};
cout << v[1] << endl;
cout << v[2] << endl;

try {
    cout << v[5] << endl;
} catch (std::out_of_range) {
    cout << "access vector[5] out_of_range. " << endl;
}

/*

2
3
access vector[5] out_of_range. 

*/
```

### 9.3 list 的特性和使用情况

- list 是双向链表。

- list.insert(p, elem) 表示在 p 的前方插入 elem。

- 除非有使用 list 的明确理由，否则使用 vector。因为 vector 在遍历上做的更好 (find & count 方法)，在排序和搜索上做得更好 (sort & binary_search)。

### 9.4 map 的底层结构

map 是一棵搜索树（红黑树，平衡二叉树）：如果有 n 个元素，那么查找一个元素的时间复杂度为 O(log(n))

<img src="https://40oqba.dm.files.1drv.com/y4m_LPlvlMLgK1ETrmPGZHaRwkH2x6dqUdflfhybMAForu19K7DBo3qsuh6YxyPD5smDYuheTvDaXEHtX9SkFuZSIgDcDDpTVdG1lp5Fulk_FHHqKgqAEMIUjaqJIuwd3oL3vTy3qmUhi-FRUC63EdAz_OA6vaW_IujxAeMd8pDNtZQLItyK49GObfrABF6lAmJRMa2bS_mtSyg6_vhv494VQ?width=655&height=374&cropmode=none"  />

### 9.5 unordered_map

unordered_map 使用 **哈希值来进行搜索** 而不是使用 **比较函数 (comparation using an ordering function such as '<')**

标准库为 string 和其他内置类型提供了默认的哈希函数。用户也可以使用自己的哈希函数，通常以**函数对象提供 (function object)** 

例如一个用户定义了哈希函数的 set：

```cpp
struct Record {
    string name;
    int product_code;
};

struct Rhash {
    size_t operator()(const Record &r) const {
        return hash<string>()(r.name) ^ hash<int>()(r.product_code);
    }
}

unordered_set<Record, Rhash> my_set;
```

### 9.6 多用 vector 而不是 list

vector 通常比 list 更有效率，即使是 erase 和 insert 操作。 (vector is usually more efficient than a list for short sequences of small elems).

除非有明确的理由，否则使用 vector。

### 9.6 forward_list （?）

forward_list 是单向链表，是一个为 empty sequence 特别优化过的容器（只占用一个字的空间）。这种序列的元素数目为 0 或者非常少，实际中它很有用。

即：对通常为空的序列，使用 forward_list

### 9.7 传递 container 的引用，返回 container 的值

19. Pass a container by reference and return a container by value.

## ch10. Algorithms

### 10.2 find_all（C++ 标准库没有 find_all 方法噢）

例如在一个 string 中搜索所有出现字符 c 的位置：

```cpp
vector<string::iterator> find_all(string &s, char c) {
    vector<string::iterator> res;
    for (auto p=s.begin(); p!=s.end(); ++p) {
        if (*p == c) res.push_back(p);
    }

    return res;
}
```

可以将该函数模板化：

```cpp
template<typename C, typename V>
vector<typename C::iterator> find_all(C &c, V v) {
    vector<typename C::iterator> res;
    for (auto p=c.begin(); p!=c.end(); ++p) {
        if (*p == v) res.push_back(p);
    }
    return res;
}
```

再优化，可以用类型别名简化模板的写法：

```cpp
template<typename T>
using Iterator = typename T::iterator;

template<typename C, typename V>
vector<Iterator<C>> find_all(C &c, V v) {
    vector<Iterator<C>> res;
    for (auto p=c.begin(); p!=c.end(); ++p) {
        if (*p == v) res.push_back(p);
    }
    return res;
}
```

### 10.3 iterator 的实现

不同容器的迭代器可以有不同的实现。

对 vector 来说，迭代器可以直接是一个指针，指向 vector 内的某个元素：

<img src="https://4koqba.dm.files.1drv.com/y4msBYkMsPat5ZkXmukvIAXXu7Mg_PfikGdRi2u7MHhUd00opO7SfQpSPoBwyDC8S6BLwaQCdqpq8tfVmCIoDTs8GLMehTl0UkJ2G_wIalDzYCu2A2m9rQigVeK5nP1ZgBXXvMJ-uCfkxHKwJdyFwzTRIRRbferEOUCvfnBEoB9-ljAZ9wWtla42JB5rlDwpvRVmEeveYpup9Roy8KzFJTQug?width=823&height=131&cropmode=none" />

也可以是指向 vector 的指针加一个 index，这样的迭代器可以进行范围检查：

<img src="https://4uoqba.dm.files.1drv.com/y4mybK9T8e0eBpaJV7t8cTX_wHaV_46a8edUq43NzviFgqROFHn4c26GZB5pTL2XE_ljGSgHd7pFBimFERYKQk3t2FkEAHwkZTVT8OI8yfUMunXMZdGb_Hmt5AWL0LvK4VjOko-jTFAALwksrRIpxluLEUQhkvJwJ36l97m8-lohNGQn4hUDZgourA7JpwOWXlFthBs1ZIeuVadPfVL36lHhQ?width=905&height=122&cropmode=none" />

一个 list 的 iterator 必须指向一个 link 而不能是直接指向某个元素，因为要使用 link 来获得下一个 link 的位置：

<img src="https://4eoqba.dm.files.1drv.com/y4mR-mwBhmliVWox64nEPZK9bqvvLGOAvJYY-8sBqzEhqPKjBAycMdA0Su4oIvObcOCTgL65ThoeyDhLfgYQwF4EDXYHu8b7m7bUE9ex45Iat4gT3jnpCnhUSgWH-XGx0Nrg4fzG340_0dQi4ShpYpSAP0FCt6w4qQxOGa6OdHzgxYp1BhxD24LIxXiTp19oVWS8uvaXoLtEM2caNZ6NaHAiA?width=967&height=266&cropmode=none" />

### 10.4 Stream Iterators （示例代码很精简）

使用 istream_iterator & ostream_iterator 从一个文件读取内容，写入另一个文件：

```cpp
int main()
{
    string from, to;
    cin >> from >> to;    // source and target file names

    ifstream is {from};
    istream_iterator<string> ii {is};    // input iterator
    istream_iterator<string> eof {};     // input eof

    ofstream os {to};
    ostream_iterator<string> oi {os, "\n"};

    vector<string> b{ii, eof};    // read strings from istream_iterator
    sort(b.begin(), b.end());

    unique_copy(b.begin(), b.end(), oo);    // copy buffer to output_stream after discard replicated values 

    return !is.eof() || !os;
}
```

可以再简化一下：

```cpp
int main()
{
    string from, to;
    cin >> from >> to;

    ifstream is {from};
    ofstream os {to};

    vector<string> b{istream_iterator<string>{is}, istream_iterator<string>{}};
    sort(b.begin(), b.end());

    copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"});

    return !is.eof() || !os;
}
```

简化版本降低了代码量，可读性也有一定程度的降低。

## ch11. Utilities

### 11.2 RAII

```cpp
mutex m;

void f() {
    unique_lock<mutex> lck {m};
    // ... manipulate shared data
} // leave the scope and release mutex
```

### 11.2.1 使用可变参数模板实现的 make_unique

```cpp
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T> {new T{std::forward<Args>(args)...}};
}
```

### 11.3 特定容器（占坑）

很多特定的容器有特定的功能，占个坑。

### 11.3.1 array 的性质

- a **fixed-size** sequence of elements

- number of elements is specified **at compile time**

- array 和内置数组很像，大小固定，但是不会像内置数组一样转换成指针类型。

- 和内置数组相比，使用 array 没有额外的时间或者空间消耗。

- array 提供了一些便捷的函数。

- array 不像其他 STL 容器一样充当着 handle to elements。array 直接包含元素。

array 可以用在 C 风格的接口和 C++ 风格的接口上：

```cpp
void f(int *p, int sz);    // C-style interface

void g() {
    array<int, 10> a;

    f(a, a.size());        // error
    f(&a[0], a.size());    // true
    f(a.data(), a.size()); // true

    auto p = find(a.begin(), a.end(), 777);    // C++-style useage
}
```

### 11.3.2 bitset（占坑）

### 11.3.3 make_pair

make_pair 函数可以创建一个 pair 而不用显式指出类型:

```cpp
void f(vector<string> &v) {
    auto pp = make_pair(v.begin(), 2);
}
```

### 11.3.3 创建 tuple 并获得 tuple 的元素

```cpp
tuple<string, int, double> t2{"Slid", 123, 3.14};

auto t = make_tuple(string{"hello"}, 10, 3.14);

string s = get<0>(t);
int x = get<1>(t);
```

### 11.4 std::chrono & time

C++ 中测量时间：

```cpp
#include <chrono>

using namespace std::chrono;

auto t0 = high_resolution_clock::now();

do_something();

auto t1 = high_resolution_clock::now();

cout << duration_cast<milliseconds>(t1-t0).count() << "msec\n";  // convert a duration into a known unit
```

### 11.5 函数参数绑定 (bind, mem_fn)

标准库提供了 `bind()` 和 `mem_fn()` 适配器来进行函数的参数绑定。

现在可以更多的使用 lambda 来代替函数参数绑定。

- bind() 函数

使用示例

```cpp
using namespace placeholders;

void f(int, const string &);
auto g = bind(f, 2, _1);

f(2, "hello");  // equals to g("hello")
g("hello");
```

- mem_fn() 函数

mem_fn 函数生成一个函数对象，使得用户可以像调用非成员函数一样调用这个对象。某些算法需要它的操作以非成员函数的方式使用，mem_fn 通常用在这些算法中。

```cpp
void draw_all(vector<Shape*> &v) {
    for_each(v.begin(), v.end(), mem_fn(&Shape::draw));
}
```

可以使用 lambda 替代：

```cpp
void draw_all(vector<Shape*> &v) {
    for_each(v.begin(), v.end(), [](Shape *p){ p->draw(); });
}
```

### 11.6 类型函数 type functions

类型函数是在编译期间进行求值的函数，接受一个类型作为参数或者返回一个类型作为结果。通常用于 metaprogramming 或者 template metaprogramming

例如：`<limits>` 的 `numeric_limits` 函数：

```cpp
constexpr float min = numeric_limits<float>::min();
```

sizeof 函数：

```cpp
constexpr int sz = sizeof(int);
```

### 11.6.1 iterator_traits（占坑）

标准库 sort 接受一对迭代器，这对迭代器表示序列的双端，且两个迭代器必须提供对序列的随机访问 (random-access iterator).

forward_list 是单链表，只提供前向迭代器 (forward iterator).

标准库提供的 iterator_traits 可以检查当前容器支持的迭代器。

### 11.6.2 type predicates 类型谓词

例如：

```cpp
bool b1 = Is_arithmetic<int>();    // yes
bool b2 = Is_arithmetic<string>(); // no
```

## ch12. Numerics

### 12.2 cmath 中的数学函数

函数 | 功能
--- | ---
abs(x) | x 的绝对值
ceil(x) | 大于 x 的最小整数
floor(x) | 小于 x 的最大整数
sin, cos, tan, acos, asin, atan, sinh, cosh, tanh | 三角函数
exp(x) | e 的 x 次方
log(x), log10(x) | 自然对数，以10为底的对数

### 12.5 随机数生成

随机数生成器包含两部分：

1. 用来生成一系列随机或者伪随机数的 **engine**

2. 将生成的随机数映射到数学上某个范围的 **distribution** （例如：uniform_int_distribution, normal_distribution, exponential_distribution）

```cpp
#include <random>
#include <iostream>
#include <functional>

int main()
{
    using my_engine = std::default_random_engine;    // type of engine
    using my_distribution = std::uniform_int_distribution<>;    // type of distribution

    my_engine re {};    // defaulr engine
    my_distribution one2six {1, 6};    // uniform_int_distribution maps to 1..6
    auto die = std::bind(one2six, re);   // die() equals one2six(re)

    std::cout << die() << " " << die() << " " << die() << std::endl;
    std::cout << one2six(re) << std::endl;
}
```

上述代码，对 `die()` 的调用相当于调用 `one2six(re)`. 简化代码可以写成：

```cpp
auto die = std::bind(std::uniform_int_distribution<>{1, 6}, std::default_random_engine{});
```

也可以通过一个类来简化随机数的生成，例如定义一个 Rand_int 类：

```cpp
class Randint {
private:
    std::default_random_engine re;
    std::uniform_int_distribution<> dist;
public:
    Randint(int low, int high) : dist{low, high} {}
    int operator()() { return dist(re); }
};
```

则在使用的时候只需要：`Randint rnd{1, 10}; int x = rnd();`

### 12.6 支持算术运算的 vector —— valarray

例子：

```cpp
#include <valarray>

void f(valarray<double> &a1, valarray<double> &a2) {
    valarray<double> a = a1*3.14 + a2/a1;
    a2 += a1*3.14;
    a = abs(a);
    double d = a2[7];
}
```

## ch13. Concurrency

### 13.2 task & threads

- task：和其他任务并行执行的计算称为任务。task 通常是一个 **函数或者函数对象**。

- threads 线程：task 在程序中的 system-level 表示。

例如：

```cpp
#include <thread>

void f();

struct F {
    void operator()();
};

void user() {
    std::thread t1 {f};
    std::thread t2 {F()};

    t1.join();
    t2.join();
}
```

- `join` 保证了直到线程结束才退出 user 函数。

- 一个程序的 threads 分享同一块地址空间。所以 threads 和 processes 不同，processes 不会直接分享数据。

### 13.3 传递给 thread 参数

```cpp
void f(vector<double> &v);

struct F {
    vector<double> &v;
    F(const vector<double> &vv) : v{vv} {}
    void operator()();
};

void user() {
    vector<double> v1{1, 2, 3};
    vector<double> v2{2, 3, 4};

    std::thread t1 {f, ref(v1)};
    std::thread t2 {F{v2}};

    t1.join();
    t2.join();
}
```

对于函数 f ，使用了 `<functional>` 头文件中的 `std::ref` 方法来传递引用。若函数参数为 const，则使用 `std::cref` 函数。

### 13.4 传递给 thread 参数来获得返回结果

```cpp
void f(const vector<double> &v, double *res);

class F {
public:
    vector<double> &v;
    F(const vector<double> &vv, double *p) : v{vv}, res{p} {}
    void operator()();
private:
    const vector<double> &v;
    double *res;
};

void user() {
    vector<double> v1{1, 2, 3};
    vector<double> v2{2, 3, 4};

    double t1res;
    double t2res;

    std::thread t1 {f, cref(v1), &t1res};
    std::thread t2 {F{v2, &t2res}};

    t1.join();
    t2.join();
}
```

### 13.5 使用 mutex 来访问共享数据

mutex：mutual exclusion object 互斥对象。

一个线程会通过 lock() 操作来获取 mutex：

```cpp
mutex m;
int shared_data;

void f() {
    unique_lock(mutex) lck {m};
    sh += 7;
}
```

上述代码使用了 `unique_lock` 的构造函数来获取 mutex（通过 m.lock() 操作）。一旦线程完成了对共享数据的访问，`unique_lock` 会释放 mutex（通过 m.unlock()） 操作。

使用 mutex 的重点是必须知道哪个 mutex 对应的是哪个 shared_data。

### 13.5 手动 lock() 操作获取多个锁

手动的 lock() 直到获取所有的 mutex 参数才会执行，当持有任意一个 mutex 时并不会阻塞。

```cpp
void f() {
    // defer_lock 表示之后再获取 mutex
    unique_lock<mutex> lck1{m1, defer_lock};
    unique_lock<mutex> lck2{m2, defer_lock};
    unique_lock<mutex> lck3{m3, defer_lock};

    // 获取所有 mutex
    lock(lck1, lck2, lck3);  
}
```

### 13.6 condition_variable

- condition_variable 允许一个 thread 等待另一个进程。

示例代码：

```cpp
#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <queue>
#include <string>

class Message {
public:
    Message(const std::string &s) : msg{s} {}

    std::string get() const {
        return msg;
    }

private:
    std::string msg;
};

std::queue<Message> mqueue;
std::condition_variable mcond;
std::mutex mmutex;

// consumer read and process Messages
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lck{mmutex};
        mcond.wait(lck);   // release lock and wait notify
                           // acquire lock again
        auto m = mqueue.front();
        mqueue.pop();
        lck.unlock();

        std::cout << m.get() << std::endl;
    }
}

void producer() {
    while (true) {
        Message m{"something just like that"};

        std::unique_lock<std::mutex> lck{mmutex};
        mqueue.push(m);
        mcond.notify_one();
    }
}

int main() 
{
    std::thread csum{consumer};
    std::thread pdcr{producer};

    csum.join();
    pdcr.join();
}
```

### 13.7 task 通信机制

C++ 标准库提供了一系列的设施让程序员在抽象的任务层进行 concurrency 操作，而不是使用底层的 threads & locks。

- future & promise：用来从一个独立的线程上创建出任务的返回值。

- packaged_task：启动 task 和连接返回值的机制。

- async()：以类似函数调用的方法启动一个 task。

上述全部在 `<future>` 头文件中。

### 13.7.1 future & promise

future 和 promise 允许在两个 task 之间直接传输数据，而不用操作 lock。

当一个 task 想把一个值传递给另一个的时候，它把这个值放入到 promise。

通常 task 的 launcher （或者其他 task）会通过 future 来获得 promise 传递的值，如果值还没到，那么线程就会阻塞直到值到达。

<img src="https://50mr4q.dm.files.1drv.com/y4mm1gVtJb0sbdKbjybaF_6OFrxFvHakRE4IAF13R3jj2vQBJ_5Rt9uJDgK6Cu1DYNSpSleyTTJKUajRSsEiuKmNjryYfCLmZ99Pet9WCygMal4jqYik4c_85WXCwsVigITfdyOp2DtaPbAqYN8It0ZErEZOw8_4shPl4Y4HNs3rN8SZKDcmoEdh5QHMnfDHtc7SFDPnR_s1yJ4gVEeGIrvXg?width=1143&height=352&cropmode=none" />

示例代码：

```cpp
// ------ promose put value ------//
void f(promise<X> &px) {
    try {
        X res;
        px.set_value(res);
    } catch (...) {
        px.set_exception(current_exception());
    }
}

// ------ future get value ------//
void g(future<X> &fx) {
    try {
        X v = fx.get();
    } catch(...) {
        // ... handle error
    }

}
```

### 13.7.2 packaged_task 将 future & promise 和 task 相关联

标准库 packaged_task 提供了一层 wrapper，将某个任务的返回值和异常放到 promise 中。如果调用 get_future 向一个 packaged_task 发送请求，则会返回对应 primise 的 future。

packaged_task 不能被拷贝，因为它是一个 resource handle：它拥有它的 promise 和 它任务所拥有的任何资源。

例如，使用两个 task 分别计算一个 vector 的前半部分和后半部分的和，最后返回累加的结果：

```cpp
double accum(double *beg, double *end, double init) {
    return accumulate(beg, end, init);
}

double comp2(vector<double> &v) {
    using Task_type = double(double *, double *, double);

    packaged_task<Task_type> pt0 {accum};
    packaged_task<Task_type> pt1 {accum};

    future<double> f0 {pt0.get_future()};
    future<double> f1 {pt1.get_future()};

    double *first = &v[0];
    // use move(pt0) because of packaged_task cannot be copied
    thread t1{move(pt0), first, first+v.size()/2, 0.0};
    thread t2{move(pt1), first+v.size()/2, first+v.size(), 0.0};

    return f0.get() + f1.get();
}
```

### 13.8 async()

async 的思路是：treat task as a function that may happed to run concurrently with other tasks

例如将一个 vector 的元素拆分为四个部分计算和：

```cpp
double accum(double *beg, double *end, double init) {
    return accumulate(beg, end, init);
}

double comp4(vector<double> &v) {
    auto v0 = &v[0];
    auto sz = v.size();

    auto f0 = async(accum, v0, v0+sz/4, 0.0);
    auto f1 = async(accum, v0+sz/4, v0+sz/2, 0.0);
    auto f2 = async(accum, v0+sz/2, v0+sz*3/4, 0.0);
    auto f3 = async(accum, v0+sz*3/4, v0+sz, 0.0);

    return f0.get() + f1.get() + f2.get() + f3.get();
}
```

- 不要对使用共享资源和 lock 的任务使用 async。

- 使用 async 并不知道创建了多少个线程，这是根据系统可用的资源量来确定的。
