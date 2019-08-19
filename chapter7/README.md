<!-- TOC -->

- [第七章 类](#第七章-类)
    - [7.1 定义抽象数据类型](#71-定义抽象数据类型)
        - [7.1.2 定义改进的 Sales_data 类](#712-定义改进的-sales_data-类)
            - [定义成员函数](#定义成员函数)
            - [this](#this)
            - [const 成员函数](#const-成员函数)
            - [类作用域](#类作用域)
            - [类外部定义成员函数](#类外部定义成员函数)
            - [返回 this 对象的函数](#返回-this-对象的函数)
        - [7.1.3 类相关的非成员函数](#713-类相关的非成员函数)
            - [read 和 print 函数](#read-和-print-函数)
        - [7.1.4 构造函数](#714-构造函数)
            - [默认构造函数(default constructor)](#默认构造函数default-constructor)
            - [某些类不能依赖合成的默认构造函数](#某些类不能依赖合成的默认构造函数)
            - [定义Sales_data的构造函数](#定义sales_data的构造函数)
                - [=default](#default)
                - [构造函数初始值列表](#构造函数初始值列表)
                - [在类的外部定义构造函数](#在类的外部定义构造函数)
        - [7.1.5 拷贝，赋值，析构](#715-拷贝赋值析构)
            - [某些类不能依赖于合成的版本](#某些类不能依赖于合成的版本)
    - [7.2 访问控制与封装](#72-访问控制与封装)
        - [struct 和 class](#struct-和-class)
        - [7.2.1 友元(friend)](#721-友元friend)
    - [7.3 类的其他特性](#73-类的其他特性)
        - [7.3.1 类成员再探](#731-类成员再探)
            - [定义一个类型成员](#定义一个类型成员)
            - [可变数据成员](#可变数据成员)
            - [类数据成员的初始值](#类数据成员的初始值)

<!-- /TOC -->

# 第七章 类

类的基本思想是 **数据抽象(data abstraction)** 和 **封装(emcapsulation)**

- 数据抽象：依赖于接口和实现的分离编程技术

- 封装：封装实现了类的接口和实现的分离(separation of interface and implementation)

## 7.1 定义抽象数据类型

### 7.1.2 定义改进的 Sales_data 类

定义在类内部的函数是隐式的 inline 函数。

#### 定义成员函数

所有成员必须在类的内部声明，但是成员函数体可以定义在类内也可以定义在类外。

#### this

成员函数通过一个名为 this 的额外隐式参数来访问调用它的对象，它的本质是一个常量指针（指针的值不被修改，即指向地址不变）

例如：如果调用

```cpp
total.isbn();
```

则编译器负责把 total 的地址传递给 isbn 的隐式形参 this，即相当于调用了

```cpp
Sales_data::isbn(&total);
```

任何自定义名为 this 的参数或者变量行为都是非法的，我们可以在成员函数体内部使用 this：

```cpp
std::string isbn() const { return this->bookNo; }
```

#### const 成员函数

使用 const 的成员函数被称作 **常量成员函数(const member function)**，若函数不加 const ，对于常量类类型，无法调用非常量成员函数。

如上所示 `std::string isbn() const { return this->bookNo; }`，isbn() 函数叫做 const 成员函数。

const 的作用是修改隐式 this 指针的类型。

- 默认类型：指向类类型非常量版本的常量指针，`Sales_data *const`类型。此时我们无法把 this 指针绑定到常量对象上。

- const 成员函数：this 指针类型为 `const Sales_data *const`，指向类类型为常量的常量指针。

#### 类作用域

类本身就是一个作用域。

编译器分两部处理类：

- 首先编译成员声明

- 其次编译成员函数体

由上可知成员函数体可以随意使用类中的其他成员，而无需在意这些成员出现的次序。

#### 类外部定义成员函数

当我们在类的外部定义成员函数时，返回类型，参数列表，函数名都需要与类内部的声明保持一致。

此外需要在函数名前加上作用域运算符，例如：

```cpp
double Sales_data::avg_price() const {
    return revenue / units_sold;
}
```

#### 返回 this 对象的函数

在 Sales_data 类中，combine 函数是返回 this 对象的函数。

```cpp
Sales_data& Sales_data::combine(const Sales_data &rhs) // rhs:right hand side
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```

在此处，combien 函数返回引用类型，是左值。

### 7.1.3 类相关的非成员函数

如果非成员函数是类接口的组成部分，则这些函数的声明应该与类在同一个头文件内。

#### read 和 print 函数

```cpp
istream &read(istream &is, Sales_data &item)
{
    is >> item.bookNo >> item.units_sold >> item.revenue;
    return is;
}

ostream &print(ostream &os, const Sales_data &item)
{
    os << item.bookNo << item.units_sold << item.revenue;
    return os;
}
```

上述代码段的几个关键点：

1. read 和 print 函数分别接受IO类型的引用作为参数，因为IO类不能被拷贝，只能通过引用传递。

2. print 函数不负责换行。执行输出任务的函数应该尽量减少对格式的控制。

### 7.1.4 构造函数

类通过一个或者几个特殊的成员函数来控制其对象的初始化过程，这些函数叫做构造函数(constructor)。

- 构造函数的任务是初始化类对象的数据成员。

- 构造函数的名字和类名相同。

- 构造函数没有返回类型。

- 构造函数有一个可能为空的函数列表和一个可能为空的函数体。

- 与重载函数类似，类可以包含多个构造函数。

注：构造函数不能被声明为 const 的，因为狗在函数完成初始化过程才能获得 const 属性。构造函数在 const 对象的构造过程中可以向其写值。

#### 默认构造函数(default constructor)

类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫做默认构造函数(default constructor)，默认构造函数无须任何实参。

如果类没有显式地定义构造函数，那么编译器就会为我们隐式地定义一个默认构造函数，被称为 合成的默认构造函数(synthesized default constructor)：

- 如果存在类内初始值，用它来初始化成员

- 否则，默认初始化成员

#### 某些类不能依赖合成的默认构造函数

合成的默认构造函数只适合非常简单的类，对于一个普通的类来说必须定义它自己的默认构造函数。

原因：

1. 只有当类没有声明任何构造函数时，编译器才会自动的生成默认构造函数。

2. 定义在块中的内置类型或者复合类型（数组和指针）的对象被默认初始化，则他们的值是未定义的。

3. 如果类中包含其他类类型的成员，且这个成员类型没有默认构造函数，那么编译器无法初始化该成员。

#### 定义Sales_data的构造函数

##### =default

默认构造函数：

```cpp
Sales_data() = default;
```

C++11 中可以在参数列表后面写上 `= default` 来要求编译器生成默认构造函数。

`= default` 既可以和声明一起出现在类的内部（内联的），也可以作为定义出现在类的外部。

##### 构造函数初始值列表

```cpp
Sales_data(const std::string &s) : bookNo(s) {}

Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_solds(n), revenue(p) {}
```

上述定义冒号，冒号和花括号之间的部分，我们称为 **构造函数初始值列表(constructor initialize list)**

当某个数据成员被构造函数初始值列表忽略时，它将以与合成默认构造函数相同的方式隐式初始化。

##### 在类的外部定义构造函数

在类的外部定义构造函数的时候，必须指明该构造函数是哪个类的成员。

```cpp
Sales_data::Sales_data(std::istream &is)
{
    read(is, *this);
}
```

### 7.1.5 拷贝，赋值，析构

除了定义类的对象如何初始化之外，类还需要控制拷贝，赋值，销毁对象时发生的行为。

#### 某些类不能依赖于合成的版本

尽管编译器能替我们合成拷贝，赋值，销毁的操作，但是对于某些类来说合成的版本无法正常工作。特别是当类需要分配类对象之外的资源时。

不过，很多需要动态内存的类，应该能使用 vector 对象，或者 string 对象来管理必要的内存空间，从而避免分配和释放内存带来的复杂性。即，如果类包含 vector 或者 string 成员，则其拷贝，赋值，销毁的合成版本能够正常工作。

## 7.2 访问控制与封装

我们使用访问说明符(access specifiers)加强类的封装性：

- public 说明符之后的成员在整个程序内可被访问，即定义类的接口。

- privete 说明符之后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，即封装了类的实现细节。

### struct 和 class

struct 和 class 的默认访问权限不太一样。

- struct: 第一个访问说明符之前的成员是public的。

- class: 第一个访问说明符之前的成员是private的。

即我们希望类的所有成员是 public 的，使用 struct。如果希望成员是 private 的，使用 class。

### 7.2.1 友元(friend)

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。

友元声明只能出现在类定义的内部，而且仅仅指定了访问权限，而非通常意义上的函数声明。

如果我们希望类的用户能够调用某个友元函数，那么必须在友元声明之外在专门对函数进行一次声明。因为为了使友元对类的用户可见，我们通常把友元的声明与类本身放置在同一个头文件中。

## 7.3 类的其他特性

### 7.3.1 类成员再探

#### 定义一个类型成员

```cpp
class Screen {
public:
    using pos = std::string::size_type; // or typedef std::string::size_type pos;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};
```

定义类型的成员必须先定义后使用，类型成员通常出现在类开始的地方。

#### 可变数据成员

mutable 用来修饰类的 const 实例中的部分可变数据成员的。即 const 成员函数可以修改这个变量。

>mutable意思是“这个成员变量不算对象内部状态”。  
>比如，你搞了个变量，用来统计某个对象的访问次数（比如供debug用）。  
>它变成什么显然并不影响对象功用，但编译器并不知道：它仍然会阻止一个声明为const的函数修改这个变量。  
>把这个计数变量声明为mutable，编译器就明白了：这个变量不算对象内部状态，修改它并不影响const语义，所以就不需要禁止const函数修改它了。

例如，我们追踪Screen的成员函数调用了多少次：

```cpp
class Screen {
    public:
        void some_func() const;
    private:
        mutable size_t access_time;
        // .... other members
}

void Screen::somefunc() const {
    ++access_time;
    // .... other operations
}
```

上述类统计了函数 `some_func()` 的调用次数，尽管他是一个 const 成员函数，但是仍然能够改变 `access_time` 的值。该成员是一个可变成员，因此任何成员函数，包括 const 函数在内都能改变它的值。

#### 类数据成员的初始值

C++11 新标准中，最好将某个变量的默认值声明成一个类内初始值。

类内初始值必须使用 = 的初始化形式，或者花括号括起来的直接初始化形式。

```cpp
struct Person {
private:
    std::string name = "ali";
    std::string addr{"california"};
}
```