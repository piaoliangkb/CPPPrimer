<!-- TOC -->

- [第十四章 重载运算和类型转换](#第十四章-重载运算和类型转换)
    - [14.1 基本概念](#141-基本概念)
        - [可以被重载的运算符和不能被重载的运算符](#可以被重载的运算符和不能被重载的运算符)
        - [直接调用重载的运算符函数](#直接调用重载的运算符函数)
        - [不该被重载的运算符](#不该被重载的运算符)
        - [赋值和复合赋值运算符](#赋值和复合赋值运算符)
        - [选择作为成员或者非成员](#选择作为成员或者非成员)
    - [14.2 输入和输出运算符](#142-输入和输出运算符)
        - [14.2.1 重载输出运算符 <<](#1421-重载输出运算符-)
            - [Sales_data 的输出运算符](#sales_data-的输出运算符)
            - [输出运算符尽量减少格式化操作](#输出运算符尽量减少格式化操作)
            - [输入输出运算符必须是非成员函数](#输入输出运算符必须是非成员函数)
        - [14.2.2 重载输入运算符 >>](#1422-重载输入运算符-)
            - [Sales_data 的输入运算符](#sales_data-的输入运算符)
            - [输入时的错误](#输入时的错误)
            - [标识错误](#标识错误)
    - [14.3 算数和关系运算符](#143-算数和关系运算符)
        - [14.3.1 相等运算符](#1431-相等运算符)
        - [14.3.2 关系运算符](#1432-关系运算符)
    - [14.4 赋值运算符](#144-赋值运算符)
        - [复合赋值运算符](#复合赋值运算符)
    - [14.5 下标运算符](#145-下标运算符)
    - [14.6 递增和递减运算符](#146-递增和递减运算符)
        - [前置版本](#前置版本)
        - [后置版本](#后置版本)
        - [显式地调用后置运算符](#显式地调用后置运算符)
    - [14.7 成员访问运算符](#147-成员访问运算符)
        - [对箭头运算符返回值的限定](#对箭头运算符返回值的限定)
    - [14.8 函数调用运算符](#148-函数调用运算符)
        - [含有状态的函数对象类](#含有状态的函数对象类)
        - [14.8.1 lambda 是函数对象](#1481-lambda-是函数对象)
            - [表示 lambda 及相应的捕获行为的类](#表示-lambda-及相应的捕获行为的类)
        - [14.8.2 标准库定义的函数对象](#1482-标准库定义的函数对象)
            - [在算法中使用标准库对象](#在算法中使用标准库对象)
        - [14.8.3 可调用对象与 function](#1483-可调用对象与-function)
            - [不同类型核能具有相同的调用形式](#不同类型核能具有相同的调用形式)
            - [标准库 function 类型](#标准库-function-类型)
            - [重载的函数与 function](#重载的函数与-function)
    - [14.9 重载，类型转换与运算符](#149-重载类型转换与运算符)
        - [14.9.1 类型转换运算符](#1491-类型转换运算符)
            - [显式的类型转换运算符](#显式的类型转换运算符)
            - [转换为 bool](#转换为-bool)
        - [14.9.2 避免有二义性的类型转换](#1492-避免有二义性的类型转换)
            - [实参匹配和相同的类型转换](#实参匹配和相同的类型转换)
            - [转换目标为内置类型的多重类型转换](#转换目标为内置类型的多重类型转换)
                - [类型转换的几个经验](#类型转换的几个经验)
            - [重载函数与转换构造函数](#重载函数与转换构造函数)
            - [重载函数与用户定义的类型转换](#重载函数与用户定义的类型转换)
        - [14.9.3 函数匹配与重载运算符](#1493-函数匹配与重载运算符)

<!-- /TOC -->

# 第十四章 重载运算和类型转换

## 14.1 基本概念

- 重载运算符是具有特殊名字的函数：由关键字 `operator` 和其后要定义的运算符号共同组成。

- 除了重载的函数调用运算符 `operator()` 之外，其他重载运算符不能含有默认实参。

- 如果一个运算符函数是成员函数，则它第一个运算对象绑定到隐式的 this 指针上。

- 当运算符作用于内置类型的运算对象时，我们不能改变它们的含义。例如：`int operator+(int, int);` 是错误的。

- 四个符号(+, -, *, &) 既是一元(unary)运算符也是二元(binary)运算符，所有这些运算符都能被重载，从参数数量可以推断：

```cpp
a + b; // binary
+(-1); // unary

a - b; // binary
-(-1); // unary

a * b; // binary
*p;    // unary

a & b; // binary
&b;    // unary
```

- 重载运算符的优先级和结合律与对应的内置运算符保持一致：

```cpp
x == y + z; 

// equivalent to 
x == (y + z); 
```

### 可以被重载的运算符和不能被重载的运算符

![image.png](https://ws1.sinaimg.cn/mw690/7e197809ly1g8wbn9ppj6j20lb07cwfp.jpg)

### 直接调用重载的运算符函数

```cpp
// 非成员函数；
auto res = data1 + data2;
res = operator+(data1, data2);

// 成员函数
data1 += data2;
data1.operator+=(data2);
```

### 不该被重载的运算符

逗号运算符，取地址，逻辑与，逻辑或。

- 逻辑与(&)，逻辑或(|)，逗号运算符(,)的运算对象求值顺序无法被保留。

- && 和 || 重载后无法保留内置运算符的短路求值规则。

- 逗号运算符和取地址运算符：C++已经定义了这两种运算符用于类类型对象的特殊含义。

### 赋值和复合赋值运算符

如果类含有算术运算符或者位运算符，则最好也提供对应的复合赋值运算符。

### 选择作为成员或者非成员

- 赋值(=)，下标([])，调用(())，成员访问箭头(->) 运算符必须是成员。

- 复合赋值运算符一般来说应该是成员，但并非必须。

- 改变对象状态的运算符（递增，递减，解引用）通常是成员。

- 具有对称性的运算符可能转换任意一端的运算对象（算数，相等性，关系，位运算符）他们应该是普通的非成员函数：

例如加法运算符是一个对称运算符，若定义为成员函数：

```cpp
string s = "world";
auto t = s + " "; // 正确
auto tt = "" + s; // 错误
```

## 14.2 输入和输出运算符

### 14.2.1 重载输出运算符 <<

输出运算符的第一个形参是一个 **非常量 ostream 对象的引用**：

- 非常量：向流写入内容会改变流的状态

- 引用：我们无法直接复制一个 ostream 对象

第二个形参是一个 **常量的引用**，是我们将要打印的类类型。

返回值为它的 `ostream` 形参。

#### Sales_data 的输出运算符

```cpp
ostream& operator<<(ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << ....;
    return os;
}
```

#### 输出运算符尽量减少格式化操作

通常输出运算符应该负责打印对象的内容而非控制格式，输出运算符不应该打印换行符。

#### 输入输出运算符必须是非成员函数

如果输入输出运算符是类的成员，则左侧运算对象是我们类的一个对象：

```cpp
Sales_data data;
data << cout;  // 即 data.operator<<(cout); 第一个参数必须是非常量 ostream 成员，即写成 data << cout;
```

>ref: https://www.zhihu.com/question/35970396

如果输入输出运算符是某个类的成员，则它们也必须是 `istream` 或者 `ostream` 的成员，然而这两个库是标准库，不能给标准库中的类添加成员。

**IO 运算符必须被定义成非成员函数，而且声明为类的友元。**

### 14.2.2 重载输入运算符 >>

通常，输入运算符的第一个形参是 **运算符将要读取的流的引用**，

第二个形参是 **要读入到的对象的引用**，

返回值是被给予的 `istream` 流。(a reference to its given stream)

#### Sales_data 的输入运算符

```cpp
istream& operator>>(istream& is, Sales_data& item) {
    is >> item.bookNo >> item.units_sold >> item.num;
    if (is) item.revenue = item.units_sold * item.num;
    else item = Sales_data();
    return is;
}
```

输入运算符必须处理输入可能失败的情况，输出运算符不需要。

#### 输入时的错误

- 输入流含有错误类型的数据时，读取操作可能失败。

- 读取操作到达文件末尾，或者遇到输入流的其他错误时也会失败。

#### 标识错误

输入运算符应该设置流的状态来标示出失败信息，通常情况下只设置 `failbit`。

此外，`eofbit` 表示文件耗尽，`badbit` 表示流被破坏。

## 14.3 算数和关系运算符

通常情况下，把算数和关系运算符定义成非成员函数，以允许对u综测或右侧的运算对象进行转换。

一般不需要改变运算对象的状态，所以形参都是常量的引用。

如果类同时定义了算术运算符和相关的复合赋值运算符，则通常情况下应该使用复合赋值来实现算术运算符。

算数运算符通常返回一个局部变量的副本作为其结果，例如：

```cpp
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}
```

复合赋值运算符(一般来说应该是类的成员，返回值是左侧对象的引用)：

```cpp
Sales_data& Sales_data::operator+=(const Sales_data& lhs) {
    units_sold += lhs.units_sold;
    revenue += lhs.revenue;
    return *this;
}
```

### 14.3.1 相等运算符

- 如果一个类有判断两个对象是否相等的操作，应该把函数定义成 `operator==` 而非一个普通的命名函数。

- 如果定义了 `operator==`，则该运算符应该能判断一组给定的对象中是否含有重复数据。

- 通常情况下，相等运算符应该具有传递性。

- 如果定义了 `operator==`，这个类也应该定义 `operator!=`。其中一个运算符调用另一个运算符的操作。

例如，Sales_data 类：

```cpp
bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.isbn() == rhs.isbn() &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
    return !(lhs == rhs);
}
```

### 14.3.2 关系运算符

通常情况下，关系运算符应该做到：

- 定义顺序关系，令其与关联容器对关键字的要求一致。

- 如果类同时含有 == 运算符的话，定义一种关系令其与 == 保持一致。特别是如果两个对象是 != 的，那么一个对象应该 < 另一个。

有些类不存在逻辑可靠的 < 定义。

## 14.4 赋值运算符

**赋值运算符必须定义为成员函数。**

例如标准库 vector 除了拷贝复制和移动赋值之外，定义了第三种赋值运算符：接受一个初始化列表的赋值运算符：

```cpp
vector<string> v;
v = {"a", "an", "the"};
```

若对 StrVec 类添加该运算：

```cpp
class StrVec {
public:
    StrVec &operator=(std::initializer_list<std::string>);
};

StrVec &StrVec::operator=(std::initializer_list<std::string> il) {
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = data.second;
    return *this;
}
```

该运算符无需检查自赋值，因为 `il` 和 `this` 确保指的不是相同的对象。

### 复合赋值运算符

**复合赋值运算符可以不是类的成员，但通常会定义成类的成员。**

```cpp
Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```

## 14.5 下标运算符

**下标运算符必须是成员函数。**

下标运算符的返回值：所访问元素的引用，这样下标可以出现在赋值运算符的任意一端。

最好定义下标运算符的常量版本和非常量版本：一个返回普通引用，另一个是类的常量成员返回常量引用。

例如，StrVec 的下标运算符：

```cpp
class StrVec {
public:
    std::string& operator[](std::size_t n) {
        return elements[n];
    } // 普通版本

    const std::string& operator[](std::size_t n) const {
        return elements[n];
    } // 常量版本，返回常量引用
private:
    std::string* elements;
};
```

## 14.6 递增和递减运算符

建议将递增和递减运算符设为成员函数，因为它们改变的是所操作对象的状态。

### 前置版本

前置运算符应该返回递增或者递减后对象的引用：

```cpp
class StrBlobPtr {
public:
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
};

StrBlobPtr& StrBlobPtr::operator++() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}
```

### 后置版本

后置版本接受一个额外的不被使用的 int 类型的形参。

使用后置运算符时，编译器为这个形参提供一个值为 0 的实参。

后置运算符返回对象原值，是一个值而非引用。所以在递增和递减对象之前首先要记录对象的状态。

我们的后置运算符使用各自的前置版本完成实际工作。

```cpp
class StrBlobPtr {
public:
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
};

StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}
```

### 显式地调用后置运算符

```cpp
StrBlobPtr p(a1);

p.operator++(0); // 后置版本
p.operator--();  // 前置版本
```

## 14.7 成员访问运算符

箭头运算符必须是类的成员，解引用运算符通常是类的成员。

StrBlobPtr 类地解引用运算符和箭头运算符：

```cpp
class StrBlobPtr {
public:
    std::string& operator*() const {
        auto p = check(curr, "deference past end");
        return (*p)[curr];
    }

    std::string* operator->() const {
        return & this->operator*();
    }
};
```

### 对箭头运算符返回值的限定

当我们重载箭头运算符时，可以改变的是箭头从哪个对象当中获取成员，而箭头获取成员这一事实不会改变。

对于一个表达式 `point->mem` 来说，根据 point 类型的不同，分别等价于：

```cpp
(*point).mem;  // point 是一个内置的指针类型
point.operator->()->mem;  // point 是定义了 operator-> 类的一个对象
```

- 重载的箭头运算符必须返回类的指针或者自定义了箭头运算符的某个类的对象。

>https://www.zhihu.com/question/42262890

## 14.8 函数调用运算符

函数调用运算符必须是成员函数。

一个类可以定义多个不同版本的调用运算符，相互之间应该在参数数量或者类型上有差别。

如果类重载了函数调用运算符，则可以像使用普通函数一样使用该类的对象。

相比普通函数，这样的类能存储状态。

如果类定义了调用运算符，则该类的对象称作函数对象(function object)。

例如，一个定义了函数调用运算符的类，用来返回参数的绝对值：

```cpp
struct absint {
    int operator() (int val) const {
        return val < 0 ? -val, val;
    }
}
```

调用方法，初始化一个 absint 的对象，然后使用函数调用运算符传入参数：

```cpp
int i = -42;
absint func;
auto res = func(i);
```

### 含有状态的函数对象类

例如，打印字符串，每个字符串之间用特殊的符号隔开：

```cpp
class PrintString {
public:
    PrintString(ostream& os, char c = ' ') : os(os), split(c) {}
    
    void operator()(const string& s) const { os << s << split; }
private:
    ostream &os;
    char split;
};

PrintString printer(std::cout, '-');
printer(s);

for_each(vec.begin(), vec.end(), PrintString(cout, '~'));
```

### 14.8.1 lambda 是函数对象

当我们编写了一个 lambda 之后，编译器将该表达式翻译成一个未命名类的未命名对象。

#### 表示 lambda 及相应的捕获行为的类

当一个 lambda 表达式通过引用捕获变量时，编译器可以直接使用该引用而无须在 lambda 产生的类中将其存储为数据成员。

通过值捕获的变量，产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数，令其使用捕获的变量的值来初始化数据成员。例如：

```cpp
auto wc = find_if(words.begin(), words.end(), 
                  [sz](const string& s) { return s.size() > sz; });
```

该 lambda 表达式产生的类形如：

```cpp
class SizeComp {
    SizeComp(size_t n) : sz(n) {}

    bool operator()(const string& s) {
        return s.size() > sz;
    }

private:
    size_t sz;
}
```

这个合成的类没有默认构造函数，所以要使用这个类必须提供一个实参：

```cpp
auto wc = find_if(words.begin(), words.end(), SizeComp(5));
```

### 14.8.2 标准库定义的函数对象

标准库定义了一组表示算术运算符，关系运算符，逻辑运算符的类，每个类分别定义了一个执行命名操作的调用运算符。它们都在头文件 `functional` 中。

例如：plus 类定义了一个函数调用运算符用于对一对运算对象执行 + 的操作。

这些类都被定义成模板的形式：

```cpp
plus<int> intadd;
auto sum = intadd(20, 30); // sum = 50

negate<int> intnegate;
auto res = intnegate(-40); // res = 40
```

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g8wldw91sej20nx07ndhg.jpg)

#### 在算法中使用标准库对象

表示运算符的函数对象常用来替换算法中的默认运算符.

例如，对一个 `vector<string>` 进行降序排序，传入参数 `greater<string>()`：

```cpp
sort(vec.begin(), vec.end(), greater<string>());
```

标准库规定其函数对象对于指针同样使用。由于比较两个无关的指针将产生未定义的行为，但是可以通过使用标准库函数对象来实现比较指针的内存地址进行排序：

```cpp
vector<string *> vec;

sort(vec.begin(), vec.end(), 
     [](string* a, string* b) { return a < b; });  // 错误，比较两个无关的指针是未定义的行为

sort(vec.begin(), vec.end(), less<string *>());    // 正确，标准库规定指针的 less 是定义良好的
```

### 14.8.3 可调用对象与 function

C++ 中几种可以调用的对象：函数、函数指针、lambda 表达式、bind 创建的对象、重载了函数调用运算符的类。

**调用形式(call signature)** 指明了调用返回的类型以及传递给调用的实参类型，例如 `int(int, int)` 表示两个实参为 int，返回值为 int。

#### 不同类型核能具有相同的调用形式

不同的调用对象类型各不相同，但是可以共享同一种调用形式，例如下面三个调用对象的调用形式都是 `int(int, int)`

```cpp
int add(int i, int j) { return i % j; }

auto mod = [](int i, int j) { return i % j; };

struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};
```

**函数表(function table)** 用来存储指向可调用对象的指针，当程序需要执行某个特定的操作时，从表中查找该调用的函数。可以使用 map 来实现。

```cpp
map<string, int(*)(int, int)> binops;

// 可以将 add 的指针添加到表中
binops.insert({"+", add});
```

我们可以将 add 的指针添加到表中，但是不能添加 mod 或者 divide。

因为他们是 lambda 表达式，每个 lambda 表达式有自己的类类型，与 map 的值类型不匹配。

#### 标准库 function 类型

可以使用一个名为 `function` 的新的标准库类型解决上述问题，它定义在头文件 `functional` 中。

`function` 是一个模板，需要提供 `function` 类型能够表示的对象的调用形式，例如：

```cpp
function<int(int, int)>;
```

这个声明的 `function` 类型表示它可以接受参数为两个 int，返回值为一个 int 的可调用对象。可以用这个新声明的类型表示上述函数：

```cpp
function<int(int, int)> f1 = add;
function<int(int, int)> f2 = divide();
function<int(int, int)> f3 = [](int i, int j) { return i % j; };
```

重新定义 map：

```cpp
map<string, function<int(int, int)>> binops;
```

现在就能把所有的可调用对象添加到这个 map 中：

```cpp
map<string, function<int(int, int)>> binops = {
    {"+", add},
    {"-", std::minus<int>()},
    {"*", [](int i, int j){ return i * j}; },
    {"/", divide()},
    {"%", mod}
};
```

function 类型重载了调用运算符，接受它自己的实参然后将其传递给存好的可调用对象：

```cpp
auto res = binops["+"](10, 5);
```

#### 重载的函数与 function

例如两个 add 函数：

```cpp
int add(int i, int j) { return i + j; }

Sales_data add(const Sales_data&, const Sales_data&);
```

若要存入重载的函数的某个版本，有两个方法：

1. 存储函数指针：

```cpp
int (*fp)(int, int) = add;
binops.insert({"+"， add});
```

2. 使用 lambda：

```cpp
binops.insert({"+", [](int a, int b) { return add(a, b);}});
```

## 14.9 重载，类型转换与运算符

转换构造函数和类型转换运算符共同定义了类类型转换 (class-type conversions)，这样的转换有时被称为：用户定义的类型转换 (user-defined conversions).

### 14.9.1 类型转换运算符

类型转换运算符(conversion operator) 是类的一种特殊成员函数，将一个类类型的值转换为其他类型，形式为：

```cpp
operator type() const;
```

类型转换运算符可以面向任意 void 之外的类型进行定义，只要该类型能够作为返回的返回类型。

所以可以转换成指针或引用，而不能转换成数组或者函数类型。

- 类型转换运算符没有显式的返回类型，也没有形参。

- 需要定义为类的成员函数。

- 类型转换运算符通常不应该改变被转换对象的内容，所以一般被定义为 const  成员。

例如：

```cpp
class SmallInt {
public:
    SmallInt(int i = 0) : val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }

    operator int() const { return val; }

private:
    int val;
}
```

```cpp
SmallInt si;
si = 4;
si + 3;
```
- 由于构造函数为非 explicit 的，所以 `si = 4;` 等号右侧被隐式地转换成了 SmallInt

- 由于定义了类型转换运算符，所以 `si + 3` 可以将 si 隐式地转换成 int

#### 显式的类型转换运算符

C++11 新标准引入了 **显式的类型转换运算符(explicit conversion operator)**:

```cpp
class SmallInt {
public:
    explicit operator int() const { return val; }
};
```

此时，编译器一般不会将一个显式的类型转换运算符用于隐式类型转换：

```cpp
SmallInt si = 3;
si + 3; // error
static_cast<int>(si) + 3; // true
```

必须显式的强制转换。

若表达式被用作条件，编译器会将显式的类型转换自动应用于它，即下列位置：

- if, while, do 的条件部分

- for 语句头的条件部分

- !, ||, && 的运算对象

- ?: 的条件表达式

#### 转换为 bool

C++11 中，IO 标准库定义了一个向 bool 的显式类型转换。

在任何条件中使用流对象，都会使用为 IO 定义的 `explicit operator bool()`。

### 14.9.2 避免有二义性的类型转换

#### 实参匹配和相同的类型转换

下面的例子定义了两种将 B 转换成 A 的方法：一种使用 B 的类型转换运算符，另一种使用 A 的以 B 为参数的构造函数：

```cpp
struct B;

struct A {
    A() = default;
    A(const B&);
};

struct B {
    operator A() const;
}

A func(const A&);

B b;
A a = func(b); // 会产生二义性错误，func(B::operator A()) 还是 f(A::A(const B&))
```
上述最后一行代码会会产生二义性错误，`func(B::operator A())` 还是 `f(A::A(const B&))`，解决方法是显式地调用类型转换运算符或者转换构造函数：

```cpp
A a1 = f(b.operator A());

A a2 = f(A(b));
```

#### 转换目标为内置类型的多重类型转换

类当中定义了多个参数都是算数类型的构造函数，或者转换目标都是算术类型的类型转换运算符：

```cpp
class A {
public:
    A(int);
    A(double);
    operator int() const;
    operator double() const;
};

void f2(long double);

A a;
f2(a);
```

最后一句 `f2(a)` 会产生二义性错误：`f(A::operator int())` 还是 `f(A::operator double())`.

```cpp
long num;
A a2(num);
```

最后一句 `A a2(num);` 会山城二义性错误：`A::A(int)` 还是 `A::A(double)`.

当使用用户定义的类型转换时，编译器会根据标准类型转换的级别决定选择最佳匹配：

```cpp
short s = 42;
A a3(s);
```

上述把 short 提升成 int 的操作优于把 short 转换成 double 的操作。

##### 类型转换的几个经验

- 不要令两个类执行相同的类型转换：如果 Foo 类有一个接受 Bar 类对象的构造函数，则不要在 Bar 类中定义转换目标是 Foo 类的类型转换运算符。

- 避免转换目标是内置算术类型的类型转换。

当已经定义了一个转换成算术类型的类型转换时，接下来不要再定义 **接受算术类型的重载运算符**；不要定义转换到多种算术类型的类型转换。

- 除了显式地向 bool 类型的转换之外，应该尽量避免定义类型转换函数并尽可能地限制那些非显式构造函数

#### 重载函数与转换构造函数

当几个重载函数地参数分属不同的类类型时，如果这些类恰好定义了同样的转换构造函数，会产生二义性：

```cpp
class C {
public:
    C(int);
};

class D {
public:
    D(int);
};

void manip(const C&);
void manip(const D&);

manip(10); 
```

最后一行 `manip(10);` 会产生二义性：`manip(C(10));` 还是 `manip(D(10));`

可以显式构造 `manip(C(10));` 来消除二义性

#### 重载函数与用户定义的类型转换

调用重载函数时，若有多种用户定义的类型转换，我们不会在这些转换用考虑可能出现的标准类型转换(例如从 int 转换成 double)，见例子：

```cpp
class C {
public:
    C(int);
};

class E {
public:
    E(double);
};

void manip(const C&);
void manip(const E&);

manip(10); 
```

最后一行 `manip(10);` 会产生二义性：`manip(C(10));` 还是 `manip(E(double(10)));`

### 14.9.3 函数匹配与重载运算符

表达式中运算符的候选函数集既应该包括成员函数，也应该包括非成员函数。

例如：

```cpp
class SmallInt {
public:
    friend SmallInt operator+(const SmallInt&, const SmallInt&);

    SmallInt(int);
    operator int() const { return val; }
private:
    int val;
};

SmallInt s1, s2;
SmallInt s3 = s1 + s2;
int i = s3 + 0;
```

最后一句 `int i = s3 + 0;` 会产生二义性：

- 可以把 0 转换成 SmallInt，使用 SmallInt 的 +

- 可以把 s3 转换成 int，使用 int 的 +