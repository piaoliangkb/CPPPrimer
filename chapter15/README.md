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

有一个基类(base class)，其他类直接或者间接地从基类继承而来，这些类成为派生类(derived class)。

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

3. C++11 新标准允许派生类显式地著名它使用哪个成员函数改写基类的虚函数，即在形参列表之后添加一个 `override` 关键字。

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

- 基类通常定义一个虚析构函数，即使该函数不执行任何实际操作。

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