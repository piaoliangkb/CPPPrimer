<!-- TOC -->

- [第十九章 特殊工具与技术](#第十九章-特殊工具与技术)
    - [19.2 运行时类型识别](#192-运行时类型识别)
        - [19.2.1 dynamic_cast 运算符](#1921-dynamic_cast-运算符)
            - [指针类型的 dynamic_cast](#指针类型的-dynamic_cast)
            - [引用类型的 dynamic_cast](#引用类型的-dynamic_cast)
        - [19.2.2 typeid 运算符](#1922-typeid-运算符)
            - [使用 typeid 运算符](#使用-typeid-运算符)
    - [19.3 枚举类型(enumeration)](#193-枚举类型enumeration)
        - [枚举成员](#枚举成员)
        - [枚举定义新的类型](#枚举定义新的类型)
        - [指定 enum 的大小(c++11)](#指定-enum-的大小c11)
        - [枚举类型的前置声明](#枚举类型的前置声明)
        - [形参匹配与枚举类型](#形参匹配与枚举类型)

<!-- /TOC -->

# 第十九章 特殊工具与技术

## 19.2 运行时类型识别

**运行时类型识别(run-time type identification, RTTI)** 的功能由两个运算符实现：

- typeid 运算符，用于返回表达式的类型。

- dynamic_cast 运算符，用于将基类的指针或引用安全地转换成派生类的指针或引用。

当我们把这两个运算符用于某种类型的指针或者引用，并且该类型含有虚函数时，运算符将使用指针或者引用所绑定对象的动态类型。

**适用情况**：像使用基类对象的指针或者引用执行派生类的操作，且该操作不是虚函数。

**一般来说应尽可能地使用虚函数**，当一个操作被定义成虚函数时，编译器将根据对象的动态类型自动地选择正确的函数版本。若无法使用虚函数，则可以使用本节提到的 RTTI 运算符，但是它相比虚成员函数蕴含更多的风险：必须直到转换的目标类型并且必须检查类型转换能否被成功执行。

### 19.2.1 dynamic_cast 运算符

使用形式：

```cpp
dynamic_cast<type *>(expression);
dynamic_cast<type &>(expression);
dynamic_cast<type &&>(expression);
```

其中，type 必须是一个类类型，通常情况下该类型含有虚函数。第一种形式：expression 必须是一个有效的指针；第二种：expression 必须是一个左值；第三种：expression 不能是左值。

expression 的类型必须符合以下三个条件中的任意一个：

1. e 的类型是目标 type 的公有派生类。

2. e 的类型是目标 type 的公有基类。

3. e 的类型就是目标 type 的类型。

如果类型符合，转换成功；否则转换失败：此时若转换目标为指针类型，结果为0；若转换目标为引用类型，则 dynamic_cast 运算符抛出一个 bad_cast 异常。

>https://www.nowcoder.com/questionTerminal/9a4991484ea74f9eb91aea062d4d2b47

- upcast 向上转型一定会成功

```cpp
class A {
public:
    A() {}
    virtual ~A() = default;
    virtual void print() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    B() {}
    virtual ~B() = default;
    void print() override {
        std::cout << "B" << std::endl;
    }
};

int main()
{
    B *pb = new B;
    A *pa = dynamic_cast<A *>(pb); // 转型成功
    if (pa == nullptr)
        std::cout << "cast error" << std::endl;
}
```

- downcast 向下转型看本质，例如：

```cpp
class A {
public:
    A() {}
    virtual ~A() = default;
    virtual void print() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    B() {}
    virtual ~B() = default;
    void print() override {
        std::cout << "B" << std::endl;
    }
};

class C : public B {
public:
    C() {}
    virtual ~C() = default;
    void print() override {
        std::cout << "C" << std::endl;
    }
};

int main()
{
    B *pb = new B;
    C *pc = dynamic_cast<C *>(pb);  // B* -> C* downcast，pb 的本质是 B* 而不是 C*，所以转换失败
    if (pc == nullptr) std::cout << "cast error" << std::endl; // cast error
}
```

#### 指针类型的 dynamic_cast

如果 Base 类含有一个虚函数，Derivec 是 Base 的公有派生类。若指针 bp 指向 Base，则可以在运行时将它转换成指向 Derived 的指针：

```cpp
if (Derived *dp = dynamic_cast<Derived *>(bp)) {
    // use dp
} else {
    // dp = nullptr, cannot use dp
}
```

在条件部分定义 dp 的好处是：可以在一个操作中同时完成类型转换和条件检查两项任务。且 dp 在 if 语句外部是不可访问的，就算转换失败，dp 也不可访问，保证了程序安全。

#### 引用类型的 dynamic_cast

不存在空引用，所以引用类型转换失败时，程序会抛出一个名为 `std::bad_cast` 的异常，该异常定义在头文件 `typeinfo` 中：

```cpp
void f(const Base &b) {
    try {
        const Derived &d = dynamic_cast<const Derived &>(b);
    } catch (bad_cast) {
        // deal with casting failure
    }
}
```

### 19.2.2 typeid 运算符

- 表达式形式：`typeid(expr)`

- 结果：一个常量对象的引用，类型为：标准库类型 `type_info` 或者 `type_info` 的公有派生类型（定义在 typeinfo 头文件中）

- 作用的表达式 `expr` 类型：

1. 顶层 const 被忽略 

2. 如果表达式是引用，typeid 返回引用所引对象的类型 

3. 若表达式是数组或函数，不会转换为指针，类型就是数组或函数类型。

4. 运算对象不属于类类型或者是一个不包含任何虚函数的类，则返回运算对象的静态类型。

5. 运算对象是至少定义了一个虚函数的类的左值时，结果运行时求得。

#### 使用 typeid 运算符

```cpp
Derived *dp = new Derived;
Base *bp = dp;

if (typeid(*bp) == typeid(*dp)) {
    // ...
}

if (typeid(*bp) == typeid(Derived)) {
    // ...
}
```

需要注意，**typeid 应作用于对象，所以不能传入指针。** 当运算对象为指针时，返回的结果是该指针的静态编译时的类型。

typeid 是否需要运行时检查，决定了表达式是否会被求值：

- 当表达式的类型含有虚函数时，编译器会对表达式求值。

- 表达式的类型如果没有虚函数，则 typeid 返回表达式的静态类型，无需对表达式求值。

如果表达式的动态类型和静态类型不同，则必须在运行时对表达式求值。对于 `typeid(*p)`：

- 如果 p 的类型不含有虚函数，则 p 不需要是一个有效的指针。

- 如果 p 的类型含有虚函数，p 必须是一个有效的指针。如果 p 是空指针，则 typeid(*p) 抛出一个名为 bad_typeid 的异常。
























## 19.3 枚举类型(enumeration)

枚举类型让我们可以将一组 **整型常量** 组织在一起。

和类一样，每个枚举类型定义了一种新的类型。

枚举属于 **字面值常量类型**。

- 限定作用域的枚举类型(scoped enumeration)：

C++11 新标准引入了 **限定作用域的枚举类型(scoped enumeration).**

形式：

首先是关键字 `enum class` 或 `enum struct`。

随后是枚举类型的名字。

之后是用花括号括起来的以逗号分隔的 **枚举成员(enumerator)** 列表。

```cpp
enum class open_modes {input, output, append};
```

- 不限定作用域的枚举类型(unscoped enumeration)：

定义 **不限定作用域的枚举类型(unscoped enumeration)** 时，省略掉关键字 `class` 或者 `struct`，枚举类型的名字是可选的。

形式：

关键字 `class` 或者 `struct` 被省略。

枚举类型可以是未命名的，若未命名，则只能在定义该 enum 时定义它的对象。

```cpp
enum color {red, yellow, green};

enum {floatPrec = 6, doublePrec = 10, double_doublePrec = 10};
```

### 枚举成员

- 枚举成员的作用域访问：

限定作用域的枚举类型中，枚举成员的名字在作用域外是不可访问的。

不限定作用域的枚举类型中，枚举成员的作用域与枚举类型本身的作用于相同。

例子：

```cpp
enum color {red, yellow, green};  // 不限定作用域的枚举类型
enum stoplight {red, yellow, green};  // error，重复定义了枚举成员
enum class peppers {red, yellow, green};  // true，枚举成员被隐藏

color eyes = green; // true
peppers p = green;  // false，pepers 的枚举成员不在有效的作用域内

color hair = color::red;  // true，允许显式地访问枚举成员
hair = yellow;  // true
peppers p2 = peppers::red;  // true
```

- 默认情况下，枚举值从 0 开始，依次 +1.

不过也可以为不同的枚举成员赋特殊的值：

```cpp
enum class intTypes {
    charTyp = 8, shortTyp = 16, intTyp = 16,
    longTyp = 32, long_longTyp = 64
};
```

- 枚举成员是 const，在初始化枚举成员时提供的初始值必须是 **常量表达式**。我们可以在任何使用常量表达式的地方使用枚举成员。

```cpp
constexpr intTypes charbits = intTypes::charTyp;
```

用途：

1. 可以将一个 enum 作为 switch 语句的表达式，将枚举值作为 case 标签。

2. 将枚举类型作为一个非类型模板形参使用。

3. 可以在类的定义中初始化枚举类型的静态数据成员。

### 枚举定义新的类型

- 要想初始化 enum 对象或者为 enum 对象赋值，必须使用该类型的一个枚举成员或者该类型的另一个对象：

```cpp
openmodes om = openmodes::input;
```

- 一个不限定作用域的枚举类型的对象或枚举成员自动地转换成整型，而限定作用于的枚举类型不会进行隐式转换

```cpp
int i = color::red;    // true
int j = prppers::red;  // false
```

### 指定 enum 的大小(c++11)

尽管每个 enum 都定义了唯一的类型，但实际上 enum 是由某种整数类型表示的。

在 C++11 新标准中，可以在 enum 的名字后加上冒号以及我们想在 enum 中使用的类型：

```cpp
enum intValues : unsigned long long {
    charTyp = 255, shortTyp = 65525, intTyp = 65535,
    longTyp = 4294967595UL, long_longTyp = 18463823093937123ULL
};
```

对于 **不限定作用域枚举类型来说，其枚举成员不存在默认类型，潜在类型依据机器而异。（限定作用域的枚举类型可以使用默认成员类型 int）** 如果我们指定了枚举成员的潜在类型，则一旦某个枚举类型的值超出了该类型所能容纳的范围，将引发程序错误。

指定 enum 潜在类型的能力使得我们可以控制不同实现环境中使用的类型。可以确保在一种实现环境中编译通过的程序所生成的代码与其他实现环境中生成的代码一致。

### 枚举类型的前置声明

在 C++11 新标准中，我们可以提前声明 enum。enum 的前置声明必须指定其成员的大小。

```cpp
enum intValues : unsigned long long;  // 不限定作用域的枚举类型，必须指定成员类型
enum class open_modes;  // 限定作用域的枚举类型，可以使用默认成员类型 int
```

### 形参匹配与枚举类型

- 要想初始化 enum 对象或者为 enum 对象赋值，必须使用该类型的一个枚举成员或者该类型的另一个对象。因此即使某个整型值恰好与枚举成员的值相等，他也不能作为函数的 enum 实参使用：

```cpp
enum Tokens {INLINE = 128, VIRTUAL = 129};

void ff(Tokens);

void ff(int);

int main() {
    Tokens curTok = INLINE;
    ff(128);   // call ff(int)
    ff(INLINE); // call ff(Tokens)
    ff(curTok); // call ff(Tokens)

    return 0;
}
```

尽管不能将整型值传递给 enum 形参，但是可以将一个不限定作用域的枚举类型的对象或枚举成员传递给整形形参。此时，enum 的值提升成 int 或者更大的整形，实际提升的结果由枚举类型的潜在类型决定：

```cpp
void newfunc(unsigned char);
void newfunc(int);

unsigned char uc = VIRTUAL;  // Tokens 最大值为 129，可以用 unsigned char 表示
newfunc(VIRTUAL);  // VIRTUAL 的值被提升为 int
newfunc(uc);
```
