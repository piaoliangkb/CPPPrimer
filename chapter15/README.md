<!-- TOC -->

- [第十五章 面向对象程序设计](#第十五章-面向对象程序设计)
    - [15.1 OOP：概述](#151-oop概述)
        - [继承(inheritance)](#继承inheritance)
        - [动态绑定(dynamic binding) / 运行时绑定(run-time binding)](#动态绑定dynamic-binding--运行时绑定run-time-binding)
    - [15.2 定义基类和派生类](#152-定义基类和派生类)
        - [15.2.1 定义基类](#1521-定义基类)
            - [成员函数与继承](#成员函数与继承)
            - [访问控制与继承](#访问控制与继承)
        - [15.2.2 定义派生类](#1522-定义派生类)
            - [派生类中的虚函数](#派生类中的虚函数)
            - [派生类向基类的类型转换](#派生类向基类的类型转换)
            - [派生类构造函数](#派生类构造函数)
            - [派生类使用基类的成员](#派生类使用基类的成员)
            - [静态成员与继承](#静态成员与继承)
            - [派生类的声明](#派生类的声明)
            - [基类必须已经定义而非声明](#基类必须已经定义而非声明)
            - [final](#final)
        - [15.2.3 类型转换与继承](#1523-类型转换与继承)
            - [静态类型和动态类型](#静态类型和动态类型)
            - [不存在基类向派生类的隐式类型转换](#不存在基类向派生类的隐式类型转换)
            - [基类和派生类对象间不存在类型转换](#基类和派生类对象间不存在类型转换)
            - [存在继承关系的类型之间的转换规则](#存在继承关系的类型之间的转换规则)
            - [练习15.8 给出静态类型和动态类型的定义](#练习158-给出静态类型和动态类型的定义)
    - [15.3 虚函数](#153-虚函数)
        - [多态 (polymorphism)](#多态-polymorphism)
        - [派生类中的虚函数](#派生类中的虚函数-1)
        - [final 和 override 说明符](#final-和-override-说明符)
        - [虚函数与默认实参](#虚函数与默认实参)
        - [回避虚函数的机制](#回避虚函数的机制)
    - [15.4 抽象基类](#154-抽象基类)
        - [纯虚函数](#纯虚函数)
        - [派生类构造函数只初始化它的直接基类](#派生类构造函数只初始化它的直接基类)
        - [重构(refactoring)（？）](#重构refactoring)
    - [15.5 访问控制与继承](#155-访问控制与继承)
        - [受保护的成员 protected](#受保护的成员-protected)
        - [public, private, protected 继承](#public-private-protected-继承)
        - [派生类向基类转换的可访问性](#派生类向基类转换的可访问性)
        - [友元与继承](#友元与继承)
        - [改变个别成员的可访问性](#改变个别成员的可访问性)
        - [默认的继承保护级别](#默认的继承保护级别)
    - [15.6 继承中的类作用域](#156-继承中的类作用域)
        - [在编译时进行名字查找](#在编译时进行名字查找)
        - [名字冲突和继承](#名字冲突和继承)
        - [函数调用和名字查找的过程](#函数调用和名字查找的过程)
        - [虚函数与作用域](#虚函数与作用域)
        - [通过基类调用隐藏的虚函数](#通过基类调用隐藏的虚函数)
        - [覆盖重载的函数](#覆盖重载的函数)
    - [15.7 构造函数与拷贝控制](#157-构造函数与拷贝控制)
        - [15.7.1 虚析构函数](#1571-虚析构函数)
            - [虚析构函数将阻止合成移动操作](#虚析构函数将阻止合成移动操作)
        - [15.7.2 合成拷贝控制与继承](#1572-合成拷贝控制与继承)
            - [派生类中删除的拷贝控制与基类的关系](#派生类中删除的拷贝控制与基类的关系)
            - [移动操作与继承](#移动操作与继承)
        - [15.7.3 派生类的拷贝控制成员](#1573-派生类的拷贝控制成员)
            - [定义派生类的拷贝或移动构造函数](#定义派生类的拷贝或移动构造函数)
            - [派生类赋值运算符](#派生类赋值运算符)
            - [派生类析构函数](#派生类析构函数)
            - [构造函数和析构函数中调用虚函数](#构造函数和析构函数中调用虚函数)
        - [15.7.4 继承的构造函数](#1574-继承的构造函数)
            - [继承的构造函数的特点](#继承的构造函数的特点)
    - [15.8 容器和继承](#158-容器和继承)
        - [在容器中放置智能指针而非对象](#在容器中放置智能指针而非对象)
        - [15.8.1 编写 Basket 类](#1581-编写-basket-类)
            - [定义 Basket 的成员](#定义-basket-的成员)
            - [隐藏指针](#隐藏指针)
    - [15.9 文本查询程序](#159-文本查询程序)
        - [15.9.1 面向对象的解决方法](#1591-面向对象的解决方法)
            - [抽象基类](#抽象基类)
            - [将层次关系隐藏于接口类中](#将层次关系隐藏于接口类中)
        - [15.9.2 Query_base 和 Query 类](#1592-query_base-和-query-类)
            - [Query_base 类](#query_base-类)
            - [Query 类](#query-类)
            - [Query 类的输出运算符](#query-类的输出运算符)
            - [练习15.32 Query 类型的对象被拷贝移动赋值销毁发生什么](#练习1532-query-类型的对象被拷贝移动赋值销毁发生什么)
            - [练习15.33 Query_base 类的对象被拷贝移动赋值销毁发生什么](#练习1533-query_base-类的对象被拷贝移动赋值销毁发生什么)
        - [15.9.3 派生类](#1593-派生类)
            - [WordQuery 类](#wordquery-类)
            - [NotQuery 类和 ~ 运算符](#notquery-类和--运算符)
            - [BinaryQuery 类](#binaryquery-类)
            - [AndQuery OrQuery 类和相应的运算符](#andquery-orquery-类和相应的运算符)
            - [练习15.34](#练习1534)
        - [19.5.4 eval 函数](#1954-eval-函数)
            - [OrQuery::eval](#orqueryeval)
            - [AndQuery::eval](#andqueryeval)
            - [NotQuery::eval](#notqueryeval)

<!-- /TOC -->

# 第十五章 面向对象程序设计

OOP 的三个基本概念：数据抽象，继承，动态绑定。

## 15.1 OOP：概述

OOP（object-oriented programming）的核心思想是 **数据抽象，继承，动态绑定**。

- 数据抽象：可以将类的接口和实现分离。

- 继承(inheritance)：定义相似的类型并对相似关系建模。

- 动态绑定：在一定程度上忽略相似类型的区别，以统一的方式使用它们的对象。

### 继承(inheritance)

通过继承联系在一起的类，构成一种层次关系。

有一个基类(base class)，其他类直接或者间接的从基类继承而来，这些类称为派生类(derived class)。

- 虚函数(virtual function)：对于某些函数，基类希望它地派生类各自定义适合自身的版本，所以将这些函数声明为虚函数，在函数前加 `virtual`。

例如，Quote 类：

```cpp
class Quote {
public:
    std::string isbn() const;
    virtual double net_prive(std::size_t n) const;
};
```

- 类派生列表(class derivation list)：用来表示这个派生类从哪些基类继承而来。形式为：`冒号，以逗号分隔的基类列表，每个基类前面的访问说明符`。

例如： Bulk_quote 类继承了 Quote 类：

```cpp
class Bulk_quote : public Quote {
public:
    double net_price(std::size_t) const override;
};
```

1. Bulk_quote 在它的派生列表中使用了 public 关键字，可以把 Buld_quote 的对象当成 Quote 的对象来使用。

2. 派生类内部必须对所有重新定义的虚函数进行声明。可以在函数之前加上 `virtual` 但不是必须的。

3. C++11 新标准允许派生类显式地注明它使用哪个成员函数改写基类的虚函数，即在形参列表之后添加一个 `override` 关键字。

### 动态绑定(dynamic binding) / 运行时绑定(run-time binding)

通过使用动态绑定，可以用同一段代码分别处理 Quote 和 Bulk_quote 的对象。

例如：

```cpp
double print_total(ostream &os, const Quote &item, size_t n) {
    double res = item.net_prive(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n 
       << " total due: " << res << endl;
    return res;
}
```

1. print_total 的 item 类型形参是基类 Quote 的一个引用。

2. 实际传入 item 的对象类型决定执行函数的哪个版本。

上述过程中函数的运行版本由实参决定，所以动态绑定有时又被称为 **运行时绑定(run-time binding)**.

- 当我们使用基类的引用（或）指针调用一个虚函数时将发生动态绑定。

## 15.2 定义基类和派生类

### 15.2.1 定义基类

Quote 类：

```cpp
class Quote {
public:
    Quote() = default;

    Quote(const std::string &book, double sales_price)
        : bookNo(book), prive(sales_price) {}

    std::string isbn() const { return bookNo; }

    // 派生类负责不同的折扣计算方法
    virtual double net_price(std::size_t n) const { return n * privc; }

    // 虚构函数动态绑定
    virtual ~Quote() = default;  

private:
    std::string bookNo;
protected:
    double price = 0.0;  // 普通状态下不打折的价格
};
```

- 基类通常定义一个虚析构函数，即使该函数不执行任何实际操作。(effective c++: item07)

#### 成员函数与继承

1. 派生类可以继承基类的成员。遇到与类型相关的操作时，派生类需要对这些操作提供自己的新定义来覆盖从基类继承而来的旧定义。

2. C++ 中基类的两种成员函数：

- 基类希望其派生类覆盖的函数：基类通常将其定义为虚函数。

- 基类希望派生类直接继承的函数

3. 基类通过在其成员函数的声明语句之前加上关键字 virtual 使得该函数执行动态绑定。

4. 任何构造函数之外的非静态函数都可以是虚函数。

5. virtual 只能出现在类内部的声明语句之前而不能用于类外部的函数定义。

6. 如果基类把一个函数声明成虚函数，则该函数在派生类中隐式地也是虚函数。

7. 成员函数如果没被声明为虚函数，其解析过程发生在编译时而非运行时。

#### 访问控制与继承

1. 派生类能访问公有成员，而不能访问私有成员。

2. `protected` 访问运算符表示派生类有权访问成员，而其他用户无法访问。

### 15.2.2 定义派生类

- 派生类列表(class derivation list)：指出派生类从哪个基类继承而来。

- 派生类列表的形式：一个冒号，以逗号分隔的基类列表，每个基类前有访问说明符 `public`, `private`, `protected` 其一。

例如：

```cpp
class Quote {
public:
    Quote() = default;

    Quote(const std::string &book, double sales_price)
        : bookNo(book), prive(sales_price) {}

    std::string isbn() const { return bookNo; }

    // 派生类负责不同的折扣计算方法
    virtual double net_price(std::size_t n) const { return n * privc; }

    // 虚构函数动态绑定
    virtual ~Quote() = default;  

private:
    std::string bookNo;
protected:
    double price = 0.0;  // 普通状态下不打折的价格
};

class Bulk_quote : public Quote {
public:
    Buld_quote() = default;

    Buld_quote(const std::string &, double, std::size_t, double);

    double net_prive(std::size_t) const override;

private:
    std::size_t min_qty = 0;  // 适用于当前折扣的最低购买量
    double discount = 0.0;    // 折扣额
};
```

- 访问说明符的作用：控制派生类从基类继承而来的成员是否对派生类的用户可见。

如果派生是公有的，那么基类的公有成员都是派生类接口的组成部分。此外，**能将公有派生类型的对象绑定到基类的引用或指针上。**

#### 派生类中的虚函数

派生类可以在它覆盖的函数前使用 virtual，但是不必要（原因：p537——一旦某个函数被声明成虚函数，则在所有派生类中它都是虚函数）。

C++11 新标准允许派生类显式地注明它使用某个成员函数覆盖了它继承的虚函数：在形参后面，或者 const 成员函数的 const 关键字后面，或者在引用成员函数的引用限定符后面加上关键字 `const`。

#### 派生类向基类的类型转换

- 在一个对象中，继承自基类的部分和派生类自定义的部分不一定是连续存储的。

- 派生类的对象中，含有与基类对应的组成部分，所以我们能把派生类的对象当成基类的对象来使用，也能 **把基类的指针或引用绑定到派生类对象的基类部分上。**

派生类到基类的转换(derived-to-base)：编译器会隐式执行

```cpp
Quote item;
Bulk_quote bulk;

Quote *p = &item;
p = &bulk;   // true, p 指向 bulk 的 Quote 部分
Quote &r = bulk;  // true,r 绑定到 bulk 的 Quote 部分
```

#### 派生类构造函数

派生类必须使用基类的构造函数来初始化它的基类部分，即每个类控制它自己的成员初始化过程。

派生类构造函数通过构造函数初始化列表来将实参传递给基类构造函数：

```cpp
Bulk_quote(const std::string &book, double p, std::size_t qty, double disc)
    : Quote(book, p), min_qty(qty), discount(disc) {}
```

除非我们特别指出，否则派生类对象的基类部分会像数据成员一样执行默认初始化。

#### 派生类使用基类的成员

- 派生类可以访问基类的公有成员和受保护成员。

- 派生类的作用域嵌套在基类的作用域之内。

#### 静态成员与继承

如果基类定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义。

静态成员遵循访问控制规则，如果基类中的成员是 private 的，则派生类无权访问。

例如：

```cpp
class Base {
public:
    static void statmem();
};

class Derived : public Base {
    void f(const Derived&);
};
```

如果静态成员是可访问的，则我们既可以通过基类也可以通过派生类使用它：

```cpp
void Derived::f(const Derived &derived_obj) {
    Base::statmem();       // Base 定义了 statmem
    Derived::statmem();    // Derived 继承了 statmem
    derived_obj.statmem(); // 通过 Derived 对象访问
    statmem();  // 通过 this 对象访问
}
```

#### 派生类的声明

派生类的声明中包含类名，但是不包括它的派生列表：

```cpp
class Bulk_quote : public Quote;  // error，不能出现派生列表
class Bulk_quote;                 // true，正确声明派生类的方式
```

#### 基类必须已经定义而非声明

如果将某个类用作基类，则该类必须已经定义而非仅仅声明。因为派生类包含并且可以使用从基类继承而来的成员，必须知道基类有什么。

- 隐含意思：一个类不能派生它本身。

- 一个类可以是基类，同时也可以是一个派生类。

```cpp
class Base {};
class D1 : public Base {};
class D2 : public D1 {};
```

上述，Base 是 D1 的直接基类(direct base)，是 D2 的简介基类(indirect base)。

#### final

C++11 定义了在类名之后添加 `final` 使得此类不能作为基类。

```cpp
class NoDerived final {};
```

### 15.2.3 类型转换与继承

类型转换的两种情况：

1. 通常情况：指针或引用的类型应该与对象的类型一致，或者对象的类型含有一个可接受的 const 类型转换规则（p144——允许将指向非常量的指针或引用转换成指向相应常量的指针或引用）。

2. 存在继承关系的类：可以将基类的指针或引用绑定到派生类对象上。即：可以用 `Quote&` 指向一个 `Bulk_quote`，或者将一个 `Bulk_quote` 的地址赋值给一个 `Quote*`。

智能指针类也支持 **派生类向基类的类型转换**，意味着我们可以将一个派生类对象的指针存储在一个基类的智能指针中。

#### 静态类型和动态类型

静态类型(static type)：表达式的静态类型在编译时已知，是变量声明时的类型或者表达式生成的类型。

动态类型(dynamic type)：变量或者表达式表示的内存中的对象的类型，直到运行时才知道。

- 基类的指针或引用的动态类型可能与其动态类型不一致。

#### 不存在基类向派生类的隐式类型转换

一个基类的对象可能是派生类对象的一部分，也可能不是，所以不存在 **基类向派生类的自动类型转换**。

编译器在编译的时候无法确认某个特定的转换在运行时是否安全，因为编译器只能检查指针或引用的静态类型来推断转换是否合法。

- 如果基类中含有一个或多个虚函数，可以使用 `dynamic_cast` 请求类型转换，该转换的安全检查将在运行时执行。

- 如果已知某个基类向派生类的转换是安全的，则可以使用 `static_cast` 来强制覆盖掉编译器的检查工作。

#### 基类和派生类对象间不存在类型转换

- 派生类向基类的自动转换类型只对指针或引用类型有效。

构造函数，赋值运算符的参数都是 **类类型的 const 版本的引用**，所以派生类向基类的转换允许我们给基类的拷贝/移动操作传递一个派生类的对象。(confused)

```cpp
Bulk_quote bulk;
Quote item(bulk);  // 调用 Quote(const Quote&) 构造函数
item = bulk;       // 调用 operator=(const Quote&)
```

- 用一个派生类对象为一个基类对象初始化或赋值时，只有该派生类对象中的基类部分会被拷贝，移动，赋值。派生类部分将被忽略掉。

#### 存在继承关系的类型之间的转换规则

- 从派生类向基类的转换只对引用或指针类型有效。

- 基类向派生类不存在隐式类型转换。

- 派生类向基类的转换可能会由于访问受限而变得不可行。

#### 练习15.8 给出静态类型和动态类型的定义

- 静态类型：

变量声明时的类型或者表达式的类型。

静态类型在编译时是已知的。

- 动态类型：

变量或者表达式表示的内存中对象的类型。

引用或者指针所指对象的动态类型可能与该引用或者指针的动态类型不同。

基类的指针或引用可以指向一个派生类对象，这种情况下，静态类型是基类的引用或指针，动态类型是派生类的引用或指针。

动态类型在运行时才可知。

## 15.3 虚函数

- 当我们使用基类的指针或引用调用一个虚成员函数时会执行动态绑定。

- 所有虚函数都必须有定义，因为编译器无法确定会使用到哪个虚函数。

- 对虚函数的调用在运行时才被解析。

### 多态 (polymorphism)

- OOP 的核心思想是多态性。

- 我们把具有继承关系的多个类型称为多态形式，因为我们能使用这些类型的多种形式而无需在意他们的差异。

- C++ 支持多态的根本：引用或指针的静态类型与动态类型不同。

当且仅当通过基类的指针或者引用调用调用基类中定义的虚函数时，才会在运行时解析该调用。只有这种情况下对象的动态类型和静态类型才有可能不同。

### 派生类中的虚函数

一旦某个函数被声明成虚函数，则在所有的派生类中它都是虚函数。所以派生类可以使用 `virtual` 也可以不使用 `virtual`。

一个派生类的函数如果覆盖了基类继承而来的虚函数，则形参和返回类型必须与被他覆盖的基类函数匹配。

例外是：当类的虚函数返回类型是类本身的指针或引用时，上述规则无效。例如，D 由 B 派生得到，则基类的虚函数可以返回 B* 而派生类的对应函数可以返回 D*。这样的返回类型要求从 D 到 B 的类型转换是可访问的。见 [15.8 容器和继承——隐藏指针](#隐藏指针)

### final 和 override 说明符

- `overrride`

C++11 新标准中可以使用 `override` 关键字来说明派生类中的虚函数。这样做若我们的声明不匹配的时候，编译器会报错，否则我们会定义出一个新函数。

`override` 出现的位置：类内成员函数的声明后；类内定义的成员函数的声明后，函数体前。

>https://en.cppreference.com/w/cpp/language/override  
>1) In a member function declaration, override may appear in virt-specifier-seq immediately after the declarator, and before the pure-specifier, if used.  
>2) In a member function definition inside a class definition, override may appear in virt-specifier-seq immediately after the declarator and just before function-body.


- `final`

若把函数定义成 `final`，则它之后不可以被派生类覆盖。

`final` 出现的位置：类内成员函数的声明后；类内定义的成员函数的声明后，函数体前；类定义时的类名之后。

>https://zh.cppreference.com/w/cpp/language/final

- `final` 和 `override` 说明符出现在形参列表，const，引用修饰符，位置返回类型之后。

### 虚函数与默认实参

虚函数可以拥有默认实参，如果某次函数调用使用了默认实参，则 **实参值由本次调用的静态类型决定**。

即：如果使用基类的引用或指针调用函数，则使用基类中定义的默认实参。即使实际运行的是派生类中的函数。

- 如果虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致。

### 回避虚函数的机制

使用作用域运算符可以指定虚函数的特定版本。

```cpp
doble undisdounted = baseP->Quote::net_price(42);
```

上述强行调用基类中的 `net_price` 而不管 baseP 的动态类型是什么

- 通常情况下只有成员函数或者友元中的代码才需要使用作用域运算符来回避虚函数的机制。（？）

- 通常当一个派生类的虚函数调用它覆盖的基类的虚函数版本时，基类版本完成所有类型都要做的共同任务，而派生类版本完成自己的任务。

## 15.4 抽象基类

含有（或者未经覆盖直接继承）纯虚函数的类是抽象基类(abstract base class)。

不能直接创建抽象基类的对象，但是可以创建该抽象基类派生类的对象（需要这些派生类的对象覆盖纯虚函数）。

### 纯虚函数

一个纯虚(pure virtual)函数无需定义，通过在函数声明的分号之前写 `=0` 来将一个虚函数声明为纯虚函数。

- `=0` 只能出现在类内部的虚函数声明语句处。

- 我们可以为纯虚函数提供定义，不过函数体必须定义在类的外部。(纯虚析构函数必须提供定义。当析构一个派生类的时候，派生类的析构函数先调用，一层一层最后会调用抽象基类的纯虚析构函数，若不定义，链接器会发生错误。[effective c++ item07 : 抽象基类：提供纯虚析构函数，并提供定义](https://github.com/piaoliangkb/cppprimer/blob/master/effective_cpp/2.%20Constructors%2C%20Destructors%2C%20and%20Assignment%20Operations.md#%E6%8A%BD%E8%B1%A1%E5%9F%BA%E7%B1%BB%E5%A3%B0%E6%98%8E%E7%BA%AF%E8%99%9A%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0%E5%B9%B6%E6%8F%90%E4%BE%9B%E5%AE%9A%E4%B9%89))

例如：

我们要将 Disc_quote 作为其他折扣类的基类，但是该类的 `net_price` 函数没有意义，所以我们将其声明为纯虚函数。

```cpp
class Disc_quote : public Quote {
public:
    Disc_quote() = default;

    Disc_quote(const std::string &book, double price, std::size_t qty, double disc)
        : Quote(book, price), quantity(qty), discount(disc) {}
    
    double net_price(std::size_t n) const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};
```

### 派生类构造函数只初始化它的直接基类

重新定义 Bulk_quote 让它继承 Disc_quote，让 Bulk_quote 只初始化它的直接基类 Disc_quote。

```cpp
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;

    Bulk_quote(const std::string &bookNo, double p, std::size_t qty, double disc)
        : Disc_quote(bookNo, p, qty, disc) {}

    double net_price(std::size_t n) const override;

    void debug() const override;

protected:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
```

### 重构(refactoring)（？）

在 Quote 体系中添加 Disc_quote 是重构的一个典型示例。

重构负责重新设置类的体系以便将操作和数据从一个类移动到另一个类中。

(如何理解这里说的重构)

## 15.5 访问控制与继承

### 受保护的成员 protected

- 当前类的用户不可访问。

- 派生类的成员和友元可以访问。

- 派生类的成员或者友元只能 **通过派生类对象来访问** 基类的 `protected` 成员。

### public, private, protected 继承

某个类对其继承而来的成员的访问权限受到两个因素影响：**基类中该成员的访问说明符、派生类的派生列表的访问说明符**。

- 派生访问说明符：控制 **派生类用户** 对于基类成员的访问权限。

若使用 `public` 派生，则派生类用户可以访问基类中的成员。

若使用 `private` 派生，则派生类用户不可访问基类中的成员。

- **派生类的成员或友元** 访问基类的成员时：

1. 派生列表访问说明符为 `public` 时，可以访问 `protected` 成员，不能访问 `private` 成员。

2. 派生列表访问说明符为 `paivate` 不影响派生类的访问权限。

### 派生类向基类转换的可访问性

假定 `class D : B {};`

- 只有当 D 公有地继承 B 时，**用户代码** 才能使用派生类向基类的转换。

- 不管 D 如何继承 B，**D 的成员函数和友元** 都可以使用派生类向基类的转换。

- 如果 D 继承 B 的方式是公有的或者受保护的，则 D 的派生类的成员可以使用 D 向 B 的类型转换。

即：**如果基类的公有成员是可访问的，则派生类向基类的类型转换也是可访问的。**

### 友元与继承

友元关系不能继承。

每个类控制自己的成员的访问权限。

### 改变个别成员的可访问性

可以使用 using 声明来改变个别成员的可访问性。

```cpp
class Base {
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};

// 私有继承了 Base，默认情况下 Derived 的用户不能访问 Base 的成员
class Derived : private Base {  
public:
    using Base::size;  // 用户可以访问 Base::size();
protected:
    using Base::n;     // Derived 的派生类可以访问 Base::n;
}
```

### 默认的继承保护级别

- class 关键字定义的派生类默认是私有继承的。

- struct 关键字定义的派生类默认是公有继承的。

## 15.6 继承中的类作用域

派生类的作用域嵌套在基类的作用域之内。

### 在编译时进行名字查找

对象，指针或引用的静态类型决定了该对象的哪些成员时可见的。但是我们能使用哪些成员是由静态类型决定的。

### 名字冲突和继承

派生类能重用定义在其直接基类或者间接基类中的名字。此时内层作用域的名字隐藏外层作用域的名字。

可以使用作用域运算符来使用隐藏的成员。

- 除了覆盖继承而来的虚函数，派生类最好不要重用其它定义在基类中的名字。

### 函数调用和名字查找的过程

假如我们调用 `p->mem()` 或者 `obj.mem()`，依次执行下列步骤：

- 首先确认 p 的静态类型，因为调用的是一个成员，所以该类型必须是类类型。

- 在 p 的静态类型对应的类中查找 mem，如果找不到则依次在直接基类中不断查找直至到达继承链的顶端。如果找不到则编译器报错。

- 一旦找到 mem，则进行类型检查确认本次调用是否合法（转换，实参数量）。

- 如果调用合法，编译器会根据调用的是否是虚函数而产生不同的代码：

- 如果 mem 是虚函数而我们是通过指针或者引用进行的调用，则编译器产生的代码将在运行时确认到底运行虚函数的哪个版本。

- 如果 mem 不是虚函数或者我们没有通过至今或者引用对该成员进行调用，则编译器产生一个常规函数调用。

需要注意：**名字查找优先类型检查**。

### 虚函数与作用域

基类与派生类中的虚函数必须有相同的形参列表。

如果形参列表不同而函数名相同的话，则派生类的函数会隐藏基类的函数。

### 通过基类调用隐藏的虚函数

调用虚函数的时候，动态绑定。调用非虚函数的时候，实际调用的函数版本由指针的静态类型决定。

一个例子：

```cpp
class Base {
public:
    virtual int fcn();
};

class D1 : public Base {
public:
    virtual void f2();
};
```

其中 Base 的派生类 D1 定义了一个新的虚函数 f2.

数据成员的定义：

```cpp
D1 d1boj;
Base *bp = &d1obj;

bp->f2(); // error，Base 没有名为 f2 的成员。
```

若要使用动态绑定调用虚函数的时候，需要基类类型有对应的成员。

### 覆盖重载的函数

成员函数无论是否是虚函数都能被重载。派生类可以覆盖重载函数的0个或多个实例。

若派生类希望所有的重载版本对他来说都是可见的，那么它就需要覆盖所有的版本，或者一个也不覆盖。

可以使用 using 声明语句来避免覆盖基类中的每一个重载版本。using 声明指定一个名字而不指定形参列表，所以一条基类成员函数的 using 声明语句就可以把该函数的所有重载实例添加到派生类作用域中。派生类只需要定义其特有的函数。

## 15.7 构造函数与拷贝控制

### 15.7.1 虚析构函数

继承关系对基类拷贝控制最直接的影响是 **基类通常应该定义一个虚析构函数**，这样就能动态分配继承系统中的对象了。

例如：

```cpp
virtual ~Quote() = default;
```

当我们 `delete` 一个动态分配的对象的指针时，将执行析构函数。

>#### 什么时候调用析构函数 chapter13.1.1
>
>一个对象被销毁时调用：
>
>- 变量离开作用域
>
>- 一个对象被销毁，它的成员被销毁
>
>- 容器（标准库容器或者数组）被销毁时，它的元素被销毁
>
>- 动态分配的对象(dynamically allocated objects)，当指向它的指针使用了 delete 运算符时
>
>- 临时对象，当创建它的完整表达式结束时被销毁

如果指针指向继承体系中的某个类型，可能出现指针的静态类型与被删除对象的动态类型不符的情况。例如：我们 delete 了一个 `Quote*` 类型的指针，但是该指针可能实际指向 `Bulk_quote` 类型的对象。此时编译器需要知道它应该执行 `Bulk_quote` 的析构函数。

我们在基类中需要将析构函数定义成虚函数：

```cpp
class Quote {
public:
    virtual ~Quote() = default;
};

Quote *item = new Quote;
delete item;  // call Quote::~Quote()

item = new Bulk_quote;
delete item;  // call Bulk_quote::~Bulk_quote()
```

- 只要基类的析构函数是虚函数，就能确保我们的 delete 基类指针时运行正确的析构函数版本。

- 如果基类的析构函数不是虚函数，则 delete 一个指向派生类对象的基类指针将产生未定义的行为。

根据 [chapter13.4.1](https://github.com/piaoliangkb/cppprimer/tree/master/chapter13#%E9%9C%80%E8%A6%81%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0%E7%9A%84%E7%B1%BB%E5%90%8C%E6%97%B6%E4%B9%9F%E9%9C%80%E8%A6%81%E6%8B%B7%E8%B4%9D%E5%92%8C%E8%B5%8B%E5%80%BC%E6%93%8D%E4%BD%9C)，需要析构函数的类，同时也需要拷贝构造函数和赋值运算符。但是基类的虚构函数不遵从上述准则。

- 一个基类总是需要析构函数，它可以将虚构函数设定为虚函数，当虚构函数为虚函数的时候，该析构函数内容为空。我们无法推断该基类是否需要赋值运算符和拷贝构造函数。

#### 虚析构函数将阻止合成移动操作

如果一个类定义了析构函数，即使它通过 `=default` 的形式使用了合成的版本，编译器也不会为这个类合成移动操作。

### 15.7.2 合成拷贝控制与继承

基类或派生类的合成拷贝控制成员负责：

- 对类本身的成员依次初始化、赋值、销毁。

- 使用直接基类中对应的操作对一个对象的直接基类部分进行初始化、赋值和销毁。

对派生类的 **析构函数** 来说，它除了销毁派生类自己的成员外，还负责销毁派生类的直接基类。以此类推到继承链的顶端。

例如 Quote 定义了析构函数而没有合成的移动操作，所以我们移动 Quote 对象的时候实际使用的是合成的拷贝操作。Quote 没有移动操作意味着它的派生类也没有移动操作。

#### 派生类中删除的拷贝控制与基类的关系

- 如果基类中的默认构造函数、拷贝构造函数、拷贝赋值运算符、析构函数时删除的或者不可访问的，那么派生类中对应的成员是删除的，因为编译器不能使用基类成员来执行派生类对象基类部分的构造、赋值、销毁操作。

- 如果在基类中有一个不可访问或删除掉的析构函数，则派生类中合成的默认和拷贝构造函数将是删除的，因为编译器无法销毁派生类对象的基类部分。

- 如果基类的移动操作是删除掉的或者不可访问的，那么派生类中的移动操作是删除的，因为派生类对象的基类部分不可移动。

- 如果基类的析构函数是删除的或者不可访问的，则派生类的移动构造函数也将是被删除的。（？）

#### 移动操作与继承

大多基类都会定义一个虚析构函数，默认情况下基类通常不含有合成的移动操作，派生类中也没有合成的移动操作。

例如，我们在 Quote 中定义默认的移动操作（同时需要定义拷贝操作）:

```cpp
class Quote {
public:
    Quote() = default;
    Quote(const Quote&) = default;
    Quote(Quote&&) = default;
    Quote& operator=(const Quote&) = default;
    Quote& operator=(Quote&&) = default;
    virtual ~Quote() = default;
};
```

### 15.7.3 派生类的拷贝控制成员

派生类的拷贝和移动构造函数在拷贝和移动自有成员的同时，也要拷贝和移动基类部分的成员。类似的，派生类赋值运算符也必须为其基类部分的成员赋值。

**析构函数只负责销毁派生类自己分配的资源，派生类对象的基类部分是自动销毁的。**

#### 定义派生类的拷贝或移动构造函数

当定义派生类的拷贝或移动构造函数时，通常使用对应的基类构造函数初始化对象的基类部分：

```cpp
class Base {};

class D : public Base {
public:

    D(const D& d) : Base(d) ... {}

    D(D&& d) : Base(std::move(D)) ... {}

};
```

如果我们没有提供基类的初始值列表，即：

```cpp
D(const D& d) ... {}
```

那么讲会调用 Base 的默认构造函数初始化 D 对象的基类部分，派生类部分从 d 对象拷贝而来。

#### 派生类赋值运算符

派生类赋值运算符必须显式地为其基类部分赋值：

```cpp
D &D::operator=(const D &rhs) {
    Base::operator=(rhs);  // 为基类部分赋值，执行 Base 的拷贝赋值运算符
    
    // ... 为派生类的成员赋值

    return *this;
}
```

#### 派生类析构函数

析构函数的函数体执行完后，对象的成员会被隐式销毁，对象的基类部分也是隐式销毁的。

- 派生类析构函数只负责销毁由派生类自己分配的资源：

```cpp
class D : public Base {
public:
    ~D() { /* 用户定义销毁派生类成员的操作 */ }
}
```

- 派生类析构函数首先执行，然后是基类的析构函数。

#### 构造函数和析构函数中调用虚函数

>Effective C++ 条款9：不要在构造和析构过程中调用虚函数

>因为基类构造器是在派生类之前执行的，所以在基类构造器运行的时候派生类的数据成员还没有被初始化。如果在基类的构造过程中对虚函数的调用传递到了派生类，派生类对象当然可以参照引用局部的数据成员，但是这些数据成员其时尚未被初始化。这将会导致无休止的未定义行为和彻夜的代码调试。

当执行基类的构造函数时，如果用到的虚函数访问派生类的成员，派生类成员尚未初始化，程序可能会崩溃。

>https://www.zhihu.com/question/34640808
>
>假设一个派生类的对象进行析构，首先调用了派生类的析构，然后在调用基类的析构时，遇到了一个虚函数，这个时候有两种选择：Plan A是编译器调用这个虚函数的基类版本，那么虚函数则失去了运行时调用正确版本的意义；Plan B是编译器调用这个虚函数的派生类版本，但是此时对象的派生类部分已经完成析构，“数据成员就被视为未定义的值”，这个函数调用会导致未知行为。实际情况中编译器使用的是Plan A，如果虚函数的基类版本不是纯虚实现，不会有严重错误发生.

### 15.7.4 继承的构造函数

C++11 中，派生类能够重用其直接基类定义的构造函数。

一个类只能初始化它的直接基类，也只能“继承”其直接基类的构造函数。

类不能继承默认、拷贝和移动构造函数。

派生类继承基类构造函数的方式是提供了一条注明了基类名的 using 声明语句：

```cpp
class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote; // 继承 Disc_quote 的构造函数

    double net_price(std::size_t) const;
};
```

- 当 using 语句作用于构造函数时，using 声明语句将令编译器产生代码。对于基类的每个构造函数，编译器都生成一个与之对应的派生类构造函数。

- 即：对于基类的每个构造函数，编译器都在派生类中生成一个形参列表完全相同的构造函数：

```cpp
derived(params) : base(args) {}
```

#### 继承的构造函数的特点

- 一个构造函数的 using 声明不会改变该构造函数的访问级别。例如：基类的私有构造函数在派生类中还是一个私有构造函数。

- 如果基类的构造函数是 explicit 或者 constexpr，则继承的构造函数也拥有相同的属性。

- 一个基类的构造函数含有默认实参，实参不会被继承，派生类会获得多个继承的构造函数，每个构造函数分别省略一个实参。

- 派生类可以继承一部分构造函数，其他构造函数使用自己的版本（自己定义的参数列表和派生类的相同的话）。

- 默认、拷贝和移动构造函数不会被继承，这些构造函数按照正常规则被合成。

## 15.8 容器和继承

不能把具有继承关系的多种类型的对象直接存放在容器当中。当派生类对象被赋值给基类对象时，其中的派生类部分将被切掉。

例如：

```cpp
vector<Quote> basket;

basket.push_back(Quote("cppprimer", 50));  // 正常拷贝
basket.push_back(Bulk_quote("algorithms", 50, 10, 0.2)); // 只拷贝对象的 Quote 部分，切掉 Bulk_quote 的部分
```

### 在容器中放置智能指针而非对象

如果我们希望在容器中存放具有继承关系的对象时，需要存放基类的指针（智能指针）。这些指针所指对象的动态类型可能是积累类型，也可能是派生类类型。

```cpp
vector<shared_ptr<Quote>> basket;

basket.push_back(make_shared<Quote>("cppprimer", 50));
basket.push_back(make_shared<Bulk_quote>("algorithms", 50, 10, 0.2)); // 将派生类的智能指针转换成基类的智能指针

cout << basket.back()->net_price(15) << endl;
```

### 15.8.1 编写 Basket 类

```cpp
class Basket {
public:
    void add_item(const std::shared_ptr<Quote> &sale) {
        items.insert(sale);
    }

    // 打印每本书的总价和 Basket 中所有书的总价
    double total_receipt(std::ostream&) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
                            return lhs->isbn() < rhs->isbn();
                        }
    
    // 传递 compare 参数的时候不可使用花括号，
    // 否则 items 会被当成函数
    // std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items(compare); error
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};
```

- 使用 multiset 来存放交易信息，能够保存一本书的多条交易记录。

- 因为 multiset 的元素是 shared_ptr，我们为其定义小于运算符，用该小与运算符初始化 items。

#### 定义 Basket 的成员

定义 `total_receipt` 函数打印每本书的总价和所有书的总价：

```cpp
double Basket::total_receipt(std::ostream &os) const {
    double sum = 0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "total sale : " << sum << std::endl;

    return sum;
}
```

- for 循环中，执行完本次循环直接通过 `upper_bound` 方法跳到下一个 `isbn()` 与当前不同的位置。

- print_total 方法中，iter 为迭代器，*iter 为 shared_ptr 指针，**iter 为指针指向的对象。

#### 隐藏指针

当前 Basket 的 add_item 成员需要接受一个 shared_ptr 参数。

```cpp
void add_item(const std::shared_ptr<Quote> &sale) {
    items.insert(sale);
}
```

用户需要通过 `make_shared` 来传递参数：

```cpp
basket.add_item(make_shared<Quote>("cppprimer", 5));
basket.add_item(make_shared<Bulk_quote>("algorithms", 99.5, 10, 0.2));
```

若将 add_item 函数改写为如下的形式，则只需要接受 Quote 对象：

```cpp
void add_item(const Quote &sale);
void add_item(Quote &&sale);
```

由于绑定到 sale 的可能是 Quote 或者 Bulk_quote，需要让 add_item 知道分配的类型从而正常内存。

为了解决上述问题，给 Quote 类添加一个虚函数 `clone`，用来申请一份当前对象的拷贝：

```cpp
class Quote {
public:
    virtual Quote* clone() const & {
        return new Quote(*this);
    }

    virtual Quote* clone() && {
        return new Quote(std::move(*this));
    }
};
```

在 [Bulk_quote](https://github.com/piaoliangkb/cppprimer/blob/master/chapter15/Bulk_quote_derived_from_Quote.h#L53) 类中改写该虚函数：

```cpp
class Bulk_quote {
public:
    Bulk_quote* clone() const & override {
        return new Bulk_quote(*this);
    }

    Bulk_quote* clone() && override {
        return new Bulk_quote(std::move(*this));
    }
}
```

分别定义 `clone` 函数的左值和右值版本：

- const 左值引用成员将他自己拷贝给新分配的对象

- 右值引用将他自己移动到新数据中

所以新的 add_item 函数如下：

```cpp
class Basket {
public:
    void add_item(const Quote &sale) {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale) {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }
}
```

由于 clone 函数是一个虚函数，所以 sale 的动态类型决定了运行 Quote 的函数还是 Bulk_quote 的函数。

>虚函数 clone 的返回对象在基类和派生类中不一样，和 [派生类中的虚函数](#派生类中的虚函数) 所述相符。

## 15.9 文本查询程序

### 15.9.1 面向对象的解决方法

> 当我们令一个类公有地继承另一个类时，派生类应当反映与基类的 `is a` 关系。在设计良好的类中，公有派生类的对象应该可以用在任何需要基类对象的地方。

为了让文本查询程序支持不同的查询方式，定义如下的类：

- `WordQuery` 普通查询

- `NotQuery` ~查询

- `OrQuery` |查询

- `AndQuery` &查询

#### 抽象基类

上述提到的四种查询方式互为兄弟，不构成继承关系，所以需要定义一个抽象基类 `Query_base`.

- `WordQuery` `NotQuery` 可以直接继承于 `Query_base`.

- `OrQuery` `AndQuery` 是二元查询，所以我们定义一个名为 `BinaryQuery` 的抽象基类，让这两个类继承于 `BinaryQuery`.

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g94jpukvudj20jc0a73zi.jpg)

#### 将层次关系隐藏于接口类中

例如对于如下的查询表达式：

```cpp
Query q = Query("fiery") & Query("bird") | Query("wind");
```

用户通过 Query 对象的操作间接地创建并处理 Query_base 对象。需要定义 Query 对象的三个重载运算符和一个构造函数：

- & 运算符生成一个绑定到一个新的 AndQuery 对象上的 Query 对象。

- | 运算符生成一个绑定到新的 OrQuery 对象上的 Query 对象。

- ~ 运算符生成一个绑定到新的 NotQuery 对象上的 Query 对象。

- 构造函数生成一个新的 WordQuery 对象。

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g94jxw9lsgj20km0b8wg5.jpg)

### 15.9.2 Query_base 和 Query 类

#### Query_base 类

```cpp
class Query_base {
    friend class Query;

protected:

    // in my program, this is type:int in TextQuery.h
    // such like : map<string, shared_ptr<set<int>>> word2line;
    using line_no = TextQuery::line_num;

    virtual ~Query_base() = default;

private:

    // eval 返回与当前 Query 匹配的 QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;

    // rep 表示查询的一个 string
    virtual std::string rep() const = 0;
};
```

- Query_base 是一个抽象基类，我们将 `eval` 和 `rep` 函数定义为纯虚函数。且我们不希望用户或者派生类直接使用 Query_base，所以它没有公有成员。

- 所有对 Query_base 的使用都要经过 Query 对象，所以将 Query 对象声明为 Query_base 的友元。

- line_no 成员将在 eval 函数中使用。

- 析构函数是受保护的，它将隐式的在派生类析构函数中使用。

#### Query 类

设计 Query 类的目的是对外提供接口，同时隐藏 Query_base 的继承体系。

- 每个 Query 对象都含有一个指向 Query_base 对象的 shared_ptr。

- Query 是 Query_base 的唯一接口，所以 Query 必须定义自己的 eval 和 rep 版本。

```cpp
class Query {

    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    
    // 创建一个新的 WordQuery 的构造函数
    Query(const std::string&);

    QueryResult eval(const TextQuery &t) const { return q->eval(t); }

    std::string rep() const { return q->rep(); }

private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};
```

- 接受 string 的构造函数创建一个新的 WordQuery 对象，然后将 Query 类的 shared_ptr 成员绑定到这个 WordQuery 对象上。

- ~ | & 运算符分别创建 AndQuery, OrQuery, NotQuery 对象，这些运算符返回一个绑定到新创建对象上的 Query 对象。将这些运算符声明为友元的原因是他们需要访问 Query 类的私有构造函数。声明构造函数为私有的原因是我们不想让普通用户代码定义 Query_base 对象。

- eval 和 rep 公有成员实际调用的函数版本将由 q 所指向的对象类型在运行时决定。

>我们的查询对象使用 Query 来表示，对查询对象调用 eval 函数，相当于调用 Query 的成员：指向 Query_base 的指针的 eval 函数。
>eval 是一个虚函数，所以根据绑定到 Query_base 的派生类的类型，进行不同的函数调用。

#### Query 类的输出运算符

```cpp
std::ostream &operator<<(std::ostream &os, const Query &query) {
    return os << query.rep();
}
```

当我们打印一个 Query 时，输出运算符使用 Query 类的公有 rep 成员，并返回输出运算符的引用：

```cpp
Query andq = Query(s1) & Query(s2);
cout << andq << endl;  // 使用 AndQuery::rep()
```

#### 练习15.32 Query 类型的对象被拷贝移动赋值销毁发生什么

1. 拷贝：合成的拷贝构造函数会增加 shared_ptr 成员的引用计数。

2. 移动：合成的移动构造函数，新的对象的 shared_ptr 成员指向原位置，引用计数为1，原来的 shared_ptr 指向 nullptr。

3. 赋值：拷贝和移动赋值和上述相同。

4. 销毁：引用计数-1。如果引用计数变为0，shared_ptr 的析构函数会调用来删除指向地址的资源分配。

#### 练习15.33 Query_base 类的对象被拷贝移动赋值销毁发生什么

Query_base 是一个抽象基类，行为由其子类对应的实现决定。

### 15.9.3 派生类

- WordQuery 类的任务就是保存要查找的单词。

NotQuery, AndQuery, OrQuery 类的运算对象必须以 Query_base 指针的形式存储，这样就能把该指针绑定到任何我们需要的具体类上。

实际我们使用 Query 对象来保存 Query_base 的指针。

#### WordQuery 类

```cpp
class WordQuery : public Query_base {

    friend class Query; // 为了让 Query 类构造 WordQuery
    
private:
    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const {
        return t.query(query_word);
    }

    std::string rep() const { return query_word; }

    std::string query_word;
};
```

- WordQuery 类的所有成员都是私有的，同 Query_base，我们不想让普通用户代码调用使用该类。

- Query 必须作为 WordQuery 的友元，这样 Query 才能访问 WordQuery 的构造函数。

#### NotQuery 类和 ~ 运算符

```cpp
class NotQuery : public Query_base {

    friend Query operator~(const Query&); // 将运算符声明为友元以创建 NotQuery 对象

private:

    NotQuery(const Query &q) : query(q) {}

    QueryResult eval(const TextQuery &) const override;

    std::string rep() const override { return "~(" + query.rep() + ")"; }

    Query query;
};

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}
```

- NotQuery 类的所有成员都是私有的，为了让 operator~ 运算符可以创建 NotQuery 对象，需要将运算符声明为该类的友元。

- ~ 运算符分配一个新的 NotQuery 对象，其 return 语句 **隐式地使用接受一个 shared_ptr<Query_base> 的 Query 构造函数**，等价于：

```cpp
shared_ptr<Query)base> temp(new NotQuery(expr));
return Query(temp);
```

#### BinaryQuery 类

BinaryQuery 类是一个抽象基类，保存操作两个运算对象的查询类型所需的数据。

```cpp
class BinaryQuery : public Query_base {

protected:
    BinaryQuery(const Query &l, const Query &r, std::string s)
        : lhs(l), rhs(r), opSym(s) {}

    std::string rep() const {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};
```

- 成员是左右两侧的运算对象和运算符号。

- BinaryQuery 没有定义 eval，而是 **继承了该纯虚函数**，所以 BinaryQuery 也是一个抽象基类。我们不能创建该类的对象。

#### AndQuery OrQuery 类和相应的运算符

```cpp
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

private:
    
    AndQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "&") {}
    
    QueryResult eval(const TextQuery&) const override;

};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
```

```cpp
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

private:
    
    OrQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "|") {}
    
    QueryResult eval(const TextQuery&) const override;

};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
```

- 将各自的运算符定义成友元。

- 各自定义了一个构造函数，通过运算符创建 BinaryQuery基类部分。

- 继承 BinaryQuery 的 rep 函数但是覆盖 eval 函数。

- 返回值都是绑定到新分配对象上的 shared_ptr。return 语句负责将 shared_ptr 转换成 Query。

#### 练习15.34

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g94jxw9lsgj20km0b8wg5.jpg)

a. 列出处理表达式过程中执行的所有构造函数：

```cpp
Query("fiery") -> Query(const std::string&) -> WordQuery(const std::string&) 

Query("fiery") & Query("bird") -> AndQuery(const Query&, const Query&) -> BinaryQuery(const Query&, const Query&)

(Query("fiery") & Query("bird")) | Query("wind") -> OrQuery(const Query&, const Query&) -> BinaryQuery(const Query&, const Query&)

// -------------------------------------------------//
// 实际执行的 //
// -------------------------------------------------//
WordQuery::WordQuery(const std::string&)
Query::Query(const std::string&)
WordQuery::WordQuery(const std::string&)
Query::Query(const std::string&)
BinaryQuery::BinaryQuery(const Query&, const Query&, std::string)
AndQuery::AndQuery(const Query&, const Query&)
Query::Query(std::shared_ptr<Query_base>)
WordQuery::WordQuery(const std::string&)
Query::Query(const std::string&)
BinaryQuery::BinaryQuery(const Query&, const Query&, std::string)
OrQuery::OrQuery(const Query&, const Query&)
Query::Query(std::shared_ptr<Query_base>)
```

b. cout << q 所调用的 rep (?)

```cpp
Query::rep()
BinaryQuery::rep()   
Query::rep()
BinaryQuery::rep() 
Query::rep()
WordQuery::rep()
Query::rep()
WordQuery::rep()
Query::rep()
WordQuery::rep()
((fiery & bird) | wind)
```

c. q.eval() 所调用的 eval

```cpp
OrQuery::eval()
```

### 19.5.4 eval 函数

>我们的查询对象使用 Query 来表示，对查询对象调用 eval 函数，相当于调用 Query 的成员：指向 Query_base 的指针的 eval 函数。
>eval 是一个虚函数，所以根据绑定到 Query_base 的派生类的类型，进行不同的函数调用。

#### OrQuery::eval

```cpp
QueryResult OrQuery::eval(const TextQuery& text) const {
    // Query.eval 调用 Query_base 中定义的虚函数 eval
    // 返回每个运算对象的 QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    
    // 左侧运算对象的行号拷贝到一个新的 set<int> 内
    auto ret_lines = std::make_shared<set<int>>(left.begin(), left.end());

    // 右侧运算对象的行号插入
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(left.getfile(), ret_lines, rep());
}
```

#### AndQuery::eval

```cpp
QueryResult AndQuery::eval(const TextQuery &text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);

    auto ret_lines = std::make_shared<set<int>>();

    // inserter 使用 insert 的迭代器，
    // 第二个参数为指向给定容器的迭代器，插入到给定迭代器之前。
    // set_intersection 将两个输入序列相同的内容写入到目标位置
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                          inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(left.getfile(), ret_lines, rep());
}
```

#### NotQuery::eval

```cpp
QueryResult NotQuery::eval(const TextQuery &text) const {
    auto ret = query.eval(text);

    auto ret_lines = std::make_shared<set<int>>();

    auto beg = ret.begin(), end = ret.end(); // 遍历 set 的行号按照升序排列
    auto sz = ret.getfile()->size();

    // 例如 ret{2, 3}
    // 总行数  {0, 1, 2, 3, 4, 5}
    for (size_t n = 0; n < sz; ++n) {
        // 如果 ret 已经结束，则上边的 if 条件永远为真，将所有剩余行添加
        // 若 ret 未结束，看当前行号和 *beg 是否相等
        // 如果不等，就添加进结果集合
        // 若相等，则递增 beg ，检查集合中的下一个元素和下一个行号
        if (beg == end || n != *beg)
            ret_lines->insert(n);
        else 
            ++beg;
    }

    return QueryResult(ret.getfile(), ret_lines, rep());
}
```
