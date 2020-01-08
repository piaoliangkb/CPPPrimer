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