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
        - [7.3.2 返回 *this 的成员函数](#732-返回-this-的成员函数)
            - [从 const 成员函数返回 *this](#从-const-成员函数返回-this)
            - [基于 const 的重载](#基于-const-的重载)
            - [练习7.30 显式地使用 this 指针的优缺点](#练习730-显式地使用-this-指针的优缺点)
        - [7.3.3 类类型](#733-类类型)
            - [类的声明](#类的声明)
        - [7.3.4 友元再探](#734-友元再探)
            - [类之间的友元关系](#类之间的友元关系)
            - [令成员函数成为友元](#令成员函数成为友元)
            - [重载函数和友元](#重载函数和友元)
            - [友元声明和作用域](#友元声明和作用域)
    - [7.4 类的作用域](#74-类的作用域)
        - [作用域和定义在类外部的成员](#作用域和定义在类外部的成员)
        - [7.4.1 名字查找与类的作用域](#741-名字查找与类的作用域)
            - [类型名要特殊处理](#类型名要特殊处理)
            - [成员定义中普通块作用域的名字查找](#成员定义中普通块作用域的名字查找)
            - [类作用域外地全局作用域](#类作用域外地全局作用域)
            - [文件中名字的出现处对其进行解析（有点拗口？）](#文件中名字的出现处对其进行解析有点拗口)
    - [7.5 构造函数再探](#75-构造函数再探)
        - [7.5.1 构造函数初始值列表](#751-构造函数初始值列表)
            - [构造函数的初始值有时必不可少](#构造函数的初始值有时必不可少)
            - [成员初始化顺序](#成员初始化顺序)
            - [默认实参和构造函数](#默认实参和构造函数)
        - [7.5.2 委托构造函数](#752-委托构造函数)
        - [7.5.3 默认构造函数的作用（待理解）](#753-默认构造函数的作用待理解)
            - [使用默认构造函数](#使用默认构造函数)
        - [7.5.4 隐式的类类型转换](#754-隐式的类类型转换)
            - [只允许一步类类型转换](#只允许一步类类型转换)
            - [抑制构造函数定义的隐式转换](#抑制构造函数定义的隐式转换)
            - [explicit 构造函数只能用于直接初始化](#explicit-构造函数只能用于直接初始化)
            - [为转换显示地使用构造函数](#为转换显示地使用构造函数)
            - [标准库中含有显式构造函数的类](#标准库中含有显式构造函数的类)
            - [练习7.49](#练习749)
            - [练习7.51](#练习751)
        - [7.5.5 聚合类](#755-聚合类)
        - [7.5.6 字面值常量类(Literal Class)](#756-字面值常量类literal-class)
            - [什么是字面值常量类](#什么是字面值常量类)
            - [constexpr 构造函数](#constexpr-构造函数)
    - [7.6 类的静态成员](#76-类的静态成员)
        - [声明静态成员](#声明静态成员)
        - [使用类的静态成员](#使用类的静态成员)
        - [定义静态成员](#定义静态成员)
        - [初始化静态成员](#初始化静态成员)
            - [类外初始化](#类外初始化)
            - [静态成员的类内初始化](#静态成员的类内初始化)
            - [特殊场景下的静态成员](#特殊场景下的静态成员)

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

### 7.3.2 返回 *this 的成员函数

返回引用的函数是左值的，意味着这些函数返回的是对象本身而非对象的副本。

```cpp
class Screen {
    public:
    Screen &set(char);
    Screen &set(pos, pos, char);
};

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos row, pos col, char c)
{
    contents[row*width + col] = c;
    return *this;
}
```

#### 从 const 成员函数返回 *this

一个 const 成员函数如果以引用的形式返回 *this，那么它的返回类型将是常量引用。

（const 成员函数中，this是指向常量对象的指针，不能修改调用该函数的对象）

#### 基于 const 的重载

通过区分成员函数是否是 const 的，我们可以对其进行重载。

- 非常量版本的函数对常量成员是不可用的。

- 非常量可以调用常量版本的函数，但是非常量版本的函数是更好的匹配。

```cpp
class Screen {
public:
    // 根据调用对象是否为const，重载了display函数，const成员函数返回 const Screen 类型
    Screen &display(std::ostream &os) { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const { do_display(os); return *this; }
private:
    void do_display(std::ostream &os) const { os << contents; }
};
```

上述重载使得：

- 常量Screen成员调用display函数之后返回常量成员的引用

- 普通Screen成员调用display函数之后返回普通成员的引用

若只有一个const成员函数，则非常量Screen成员调用display函数之后只能返回常量引用。

对于上述定义了 do_display() 函数：

- 对于公共代码使用私有功能函数，避免多处使用相同代码

- 拓展时只需要修改私有成员

- 我们在类的内部定义了 do_display() 函数，被隐式地声明为内联函数，不会有额外的运行时开销

#### 练习7.30 显式地使用 this 指针的优缺点

优点，例如：`void setAddr(const std::string &addr) { this->addr = addr; }`

- 更明确

- 成员函数参数名称可以和类的成员相同

缺点，例如：`std::string getAddr() const { return this->addr; }`

- 冗余

- 阅读起来较繁琐

### 7.3.3 类类型

我们可以把类名作为类型的名字使用，或者把类名跟在关键字 class 或者 struct 后面：

```cpp
Sales_data item1;
class Sales_data item2;
struct Sales_data item3;
```

其中第二种方式从C语言继承而来，无论定义类的时候使用class或者struct，声明时候struct和class都可以使用。

#### 类的声明

类的声明和定义可以分开：

```cpp
class Screen;
```

上述声明称为 **前向声明(forward declaration)**。对于类 Screen 来说，它在声明后定义之前是一个 **不完全类型(incomplete type)**：

- 可以定义指向这种类型的指针或者引用（链表）

- 可以声明以不完全类型作为参数或者返回类型的函数

直到类被定义之后，数据成员才能被声明成这种类类型，所以一个类的成员类型不能是该类自己，但是可以是指向自身类型的引用或者指针。

### 7.3.4 友元再探

普通的非成员函数，类，类的成员函数都可以定义成友元。

友元函数可以定义在类的内部，这样的函数是隐式内联的。

#### 类之间的友元关系

定义一个 Window_mgr 类，可以访问 Screen 内部的数据：

```cpp
class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
}

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}
```

若要让 clear() 函数工作，需要将 Window_mgr 类声明为 Screen 类的友元：

```cpp
class Screen {
    friend class Window_mgr;
}
```

#### 令成员函数成为友元

Screen 类还可以只为函数 clear() 提供访问权限，此时定义为：

```cpp
class Screen {
    friend void Window_mgr::clear(ScreenIndex);
}
```

#### 重载函数和友元

一个类若要把一组重载函数声明成它的友元，则需要对每一个重载函数分别声明。

#### 友元声明和作用域

友元声明和普通的声明作用不同，友元声明只影响访问权限。

## 7.4 类的作用域

### 作用域和定义在类外部的成员

一个类就是一个作用域。

对于 clear() 函数来说，编译器在处理参数列表之前已经明确了我们当前正位于 Window_mgr 类的作用域中，所以不必再专门说明 ScreenIndex 是 Window_mgr 类定义的。

```cpp
void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}
```

此外，返回类型必须出现在函数名称之前，且需要指明返回类型是哪个类的成员。例如对于 addScreen() 函数：

```cpp
class Window_mgr {
public:
    ScreenIndex addScreen(const Screen&);
    using ScreenIndex = std::vector<Screen>::size_type;
};

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
```

### 7.4.1 名字查找与类的作用域

类的定义分为两部处理：

1. 编译成员的声明

2. 类全部可见之后编译函数体

因为成员函数体直到整个类可见之后才会被处理，所以它能使用类中定义的任何名字。

#### 类型名要特殊处理

在类中，如果成员使用了外层作用域中的某个名字，而且该名字代表一种类型，那么类不能在之后重新定义该名字。

类型名的定义通常出现在类的开始，这样确保所有使用该类型的成员出现在类型名的定义之后。

#### 成员定义中普通块作用域的名字查找

若类中函数声明了和类成员相同名称的变量，则会隐藏同名的类成员。

然而我们仍然可以通过加上类的名字或者显式地使用 this 指针来强制访问成员。

#### 类作用域外地全局作用域

```cpp
int height = 10;
class Screen {
private:
    int height = 0;
}

void Screen::dummy_func(pos height)
{
    cursor = width * ::height;
}
```

上述使用了作用域运算符访问全局的 height 对象。

#### 文件中名字的出现处对其进行解析（有点拗口？）

名字查找（name lookup）的过程：

1. 名字所在的块中

2. 外层作用域

3. 如果没有匹配的声明，则程序报错

## 7.5 构造函数再探

### 7.5.1 构造函数初始值列表

建议使用构造函数初始值。

很多类中，初始化和赋值的区别事关底层效率：前者直接初始化成员，后者先初始化再赋值。

例如：

```cpp
Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c) {}

// rather than

Screen(pos ht, pos wd, char c) {
    height = ht;
    width = wd;
    contents = (ht*wd, c);
}
```

#### 构造函数的初始值有时必不可少

如果成员是 const 或者 引用 的话，必须将这个成员初始化。

#### 成员初始化顺序

成员初始化顺序与他们在类定义中出现的顺序一致，与初始值列表无关。

最好令构造函数初始值顺序与成员生命顺序保持一致，尽量避免使用某些成员初始化其他成员。

#### 默认实参和构造函数

如果一个构造函数为所有参数都提供了默认实参，则它实际上也定义了默认构造函数。例如：

```cpp
class Sales_data {
public:
    Sales_data(std::string s = "") : bookNo(s) {}
}
```

上述构造函数为默认构造函数，若此处仍有`Sales_data() = default;`，则会产生二义性。

### 7.5.2 委托构造函数

C++11 新标准定义了 **委托构造函数(delegating constructor)**. 

一个委托构造函数使用它所属类的其他构造函数执行他自己的初始化过程，或者说它把自己的一些或者全部职责委托给了其他构造函数。

```cpp
class Sales_data {
public:
    // 非委托构造函数
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(price*cnt) {}
    // 委托构造函数
    Sales_data(): Sales_data("", 0, 0) {}
    Sales_data(std::string s): Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is): Sales_data() { read(is, *this); }
};
```

受委托构造函数的初始值列表和函数体被依次执行。

### 7.5.3 默认构造函数的作用（待理解）

当对象被默认初始化或值初始化时自动执行默认构造函数。

默认初始化发生的情况：

1. 在块作用域内不使用任何初始值定义一个非静态变量或者数组。

2. 一个类本身含有类类型的成员，且使用合成的默认构造函数。

3. 类类型的成员没有在构造函数初始值列表中显式地初始化。

值初始化发生的情况：

1. 数组初始化过程中提供的初始值数量小于数组大小。

2. 不适用初始值定义一个局部静态变量。

3. 显式地请求值初始化，例如vector只提供大小。

#### 使用默认构造函数

```cpp
Sales_data obj();  // 声明了一个返回值为 Sales_data 的函数
Sales_data obj;    // obj是一个默认初始化的对象
```

### 7.5.4 隐式的类类型转换

如果构造函数只接受一个实参，那么实际上定义了转换为此类类型的隐式转换机制，有时我们把这种构造函数称作 **转换构造函数(converting constructor)**.

即：能通过一个实参调用的构造函数，定义了一条从构造函数的参数类型向类类型隐式转换的规则。

例如：

```cpp
string numm_book = "999999";
item.combine(null_book);
```

这里使用了一个 string 实参调用 Sales_data 的 combine 成员。编译器用给定的 string 创建了一个 Sales_data 对象，新生成的临时 Sales_data 对象被传递给 combine。

#### 只允许一步类类型转换

编译器只会自动地执行一步类型转换，例如下面代码执行了两步，错误：

```cpp
// 首先将 “999999” 转换成 string
// 其次将 string 转换成 Sales_data
// error
item.combine("999999");
```

可以显式地转换：

```cpp
item.combine(string("99999"));
// or
item.combine(Sales_data("999999"));
```

从 istream 到 Sales_data 的转换：

```cpp
item.combine(std::cin);
```

这段代码把 std::cin 隐式地转换成 Sales_data.

#### 抑制构造函数定义的隐式转换

将构造函数声明为 `explicit` 来阻止隐式转换机制。

```cpp
class Sales_data {
public:    
    Sales_data() = default;
    explicit Sales_data(const std::string &s): bookNo(s) {}
    explicit Sales_data(std::istream&);
}
```

此时没有构造函数用于隐式创建 Sales_data 对象。

- `explicit` 只对一个实参的构造函数有效，需要多个实参的构造函数不能用于执行隐式转换。

- 只能在类内声明构造函数的时候使用 explicit 关键字，类外定义不应该重复。

#### explicit 构造函数只能用于直接初始化

发生隐式转换的一种情况是当我们执行拷贝形式初始化时(=)。

```cpp
Sales_data item = null_book; // error，不能拷贝初始化
Sales_data item(null_book);  // true，可以直接初始化
```

#### 为转换显示地使用构造函数

编译器不会将 explicit 地构造函数用于隐式转换过程，但是我们可以显示的强制进行转换：

```cpp
item.combine(static_cast<Sales_data>(cin));
```

#### 标准库中含有显式构造函数的类

- 接受一个单参数 `const char*` 的 string 构造函数不是 explicit 的。

- 接受一个容量参数的 vector 构造函数是 explicit 的。

#### 练习7.49 

C++ 中的临时量是 const 的，不能作为非 const 的引用参数。

#### 练习7.51

对于函数 `int getSize(const std::vector<int> &)` 来说，如果传入一个参数

```cpp
getSize(34);
```

我们无法理解这是什么。

而对于 `std::string` 来说，可以使用 `std::string` 来替换 `const char*`

### 7.5.5 聚合类

**聚合类(aggregate class)**：

- 所有成员都是 public 的

- 没有定义任何构造函数

- 没有类内初始值

- 没有基类，也没有 virtual 函数

例如：

```cpp
struct Data {
    int val;
    string s;
};
```

可以使用花括号括起来的成员初始值列表，初始化聚合类的数据成员：

```cpp
Data val1 = {0, "haha"};
```

- 初始值的顺序必须与类中成员声明顺序一致。

- 如果初始值列表中的元素个数少于类的成员数量，则靠后的成员被值初始化。

### 7.5.6 字面值常量类(Literal Class)

某些类也可以是字面值类型；字面值类型的类可能含有 constexpr 函数成员（参数和返回值必须是字面值类型），它们是隐式 const 的。

#### 什么是字面值常量类

1. 数据成员都是字面值类型的聚合类是字面值常量类

2. 如果一个类不是聚合类但是复合如下要求，那么它也是一个字面值常量类：

- 数据成员都是字面值类型(The data members all must have literal type)

- 类必须含有至少一个 constexpr 构造函数

- 如果数据成员有类内初始值，那么内置类型数据成员的初始值必须是常量表达式；若成员是类类型，则初始值必须使用成员自己的 constexpr 构造函数

- 类必须使用析构函数的默认定义(default definition of its destructor)

#### constexpr 构造函数

尽管构造函数不能是 const 的，但是字面值常量类的构造函数可以是 constexpr 函数。

constexpr 函数可以声明成 `=default` 的形式或者是删除函数的形式，否则 constexpr 函数就必须符合构造函数的要求：

- 不能包含返回语句

也需要符合 constexpr 函数的要求：

- 拥有的唯一可执行语句是返回语句

综上可知，构造函数体一般为空。

```cpp
class Debug {
public:
    constexpr Debug(bool b = true): hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o): hw(h), io(i), other(o) {}
    constexor bool any() { return hw || io || other; }
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { hw = b; }
private:
    bool hw;
    bool io;
    bool oother;
}
```

constexpr 构造函数必须初始化所有数据成员。初始值必须是一个 constexpr 构造函数，或者必须是一个常量表达式。

constexpr 构造函数用于生成 constexpr 对象：

```cpp
constexpr Debug debug(false, true, false);
constexpr Debug error(false);
```

## 7.6 类的静态成员

类的静态成员与类本身相关，而不是与类的对象相关。

### 声明静态成员

- 在声明之前加上 static 关键字。

- 静态成员可以是 public 的或者 private 的。

- 静态成员可以是常量，引用，指针，类类型。

- 类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。

```cpp
class Account {
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
};
```

### 使用类的静态成员

1. 可以使用域运算符直接访问静态成员：

```cpp
double r;
r = Account::rate();
```

2. 虽然静态成员不属于类的对象，但是可以使用类的对象，引用，指针来访问静态成员：

```cpp
Account ac1;
Account *ac2 = &ac1;
double r;
r = ac1.rate();
r = ac2->rate();
```

3. 类的成员函数不通过作用域运算符就可以直接使用静态成员：

```cpp
void calculate() { amount += amount * interestRate; }
```

### 定义静态成员

在类的外部定义静态成员时，不能重复 static 关键字，static 关键字只能出现在类内部的声明语句：

```cpp
void Account::rate(double newRate)
{
    interestRate = newRate;
}
```

### 初始化静态成员

#### 类外初始化

静态成员不属于类的任何一个对象，所以他们不是在创建类的对象时被定义的。必须在类的外部定义和初始化每个静态成员，一个静态成员只能定义一次。

类似于全局变量，静态数据成员定义在任何函数之外，一旦被定义，就存在程序的整个生命周期中。

```cpp
// 定义并初始化一个静态成员
double Account::interestRate = initRate();
```

从类名开始，作用域就位于类内了，所以 `initRate()` 函数不需要加域运算符。

- 要想确保对象只定义一次，最好的办法是把静态数据成员的定义与其他非内联函数的定义放在同一个文件中。

#### 静态成员的类内初始化

若要在类内初始化静态成员，需要满足两条要求：

1. 静态成员必须是字面值 **常量** 类型的常量表达式

- 字面值常量类型就是 const 型的算术类型，引用，指针等。

- constexpr是常量表达式，指值不会改变并且在编译过程中就能得到计算结果的表达式。C++11规定允许将变量声明为 constexpr 类型，以便由编译器来检查变量是否为常量表达式。

2. 给静态成员提供的初始值必须是常量表达式




通常，静态成员不应该在类的内部初始化。然而我们可以为 const 整数类型的成员提供类内初始化程序，不过要求静态成员必须是字面值常量类型的常量表达式constexpr。

初始值必须是常量表达式，成员本身也需要是常量表达式。

```cpp
class Account {
private:
    static constexpr int period = 30; // or static const int period = 30;
    double d[period];
};
```

在上述例子中，如果变量 period 的唯一用途就是定义数组的维度，那么不需要在类外专门定义。

如果在类的内部提供了一个初始值，则成员的定义不能再指定一个初始值了。即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下该成员。

```cpp
constexpr int Account::period;
```

若不定义也没问题：

```cpp
class Account {
public:
    double get() { return sizeof(d); }
private:
    static constexpr int period = 30;
    double d[period];
};

int main()
{
    Account a;
    cout << a.get() << endl; // output is 240
}
```

>ref: https://www.cnblogs.com/wanyuanchun/p/4041080.html

#### 特殊场景下的静态成员

1. 静态数据成员可以是不完全类型

```cpp
class Bar {
public:
    // ...
private:
    static Bar mem1;  // 静态成员可以是不完全类型
    Bar *mem2;        // 非静态成员可以是指针或者引用
    Bar mem3;         // 非静态成员不能是不完全类型
};
```

2. 可以使用静态成员作为默认实参

```cpp
class Screen {
public:
    Screen& clear(char = background);
private:
    static constexpr char background; // or static const char background;
};
```
