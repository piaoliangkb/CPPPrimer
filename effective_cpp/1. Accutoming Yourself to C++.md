<!-- TOC -->

- [Accustoming Yourself to C++](#accustoming-yourself-to-c)
    - [01: View C++ as a federation of languages](#01-view-c-as-a-federation-of-languages)
    - [02: Prefer consts, enums, and inlines to #define](#02-prefer-consts-enums-and-inlines-to-define)
        - [使用 constants(常量) 替换 #define 的两种情况](#使用-constants常量-替换-define-的两种情况)
        - [使用 enum 代替 #define](#使用-enum-代替-define)
        - [使用 inline 代替 #define 函数](#使用-inline-代替-define-函数)
    - [03: Use const whenever possible](#03-use-const-whenever-possible)
        - [const 成员函数](#const-成员函数)
    - [04: Make sure that objects are initialized before they're used](#04-make-sure-that-objects-are-initialized-before-theyre-used)
        - [使用构造函数初始化列表](#使用构造函数初始化列表)
        - [non-local static 对象在不同编译单元的初始化顺序](#non-local-static-对象在不同编译单元的初始化顺序)

<!-- /TOC -->
# Accustoming Yourself to C++

> 让自己习惯 C++

## 01: View C++ as a federation of languages

> 视 C++ 为一个语言联邦

当前的 C++ 是一个多重范式编程语言(multiparadigm programming language)，同时支持：

- 过程形式 (procedural)

- 面向对象形式 (object-oriented)

- 函数形式 (functional)

- 泛型形式 (generic)

- 元编程形式 (metaprogramming)

遵守高效编程守则，例如：

对于内置类型而言，pass-by-value 通常比 pass-by-reference 更高效。然而由于用于自定义的类的析构函数和构造函数的出现，pass-by-reference-to-const 往往更好。

## 02: Prefer consts, enums, and inlines to #define

> 尽量以 const, enum, inline 替换 #define

可以理解为：宁愿以编译器替换预处理器(preprocessor)，因为 `#define` 不被视为语言的一部分。

例如：`#define ASPECT_RATIO 1.653` 

可能 `ASPECT_RATIO` 没有进入到记号表中(symbol table)。

可以使用 `const double AspectRatio = 1.653;` 替换它。此时 `AspectRatio` 会进入到记号表被编译器看到。此外，使用 `#define` 的话可能会在程序中有多份 1.653 的拷贝(multiple copies of 1.653 in your object code)，使用 `const` 定义的 `AspectRatio` 不会超过一份拷贝。

### 使用 constants(常量) 替换 #define 的两种情况

1. defining constant pointers(常量指针)

通常常量定义会在头文件中，所以将指针定义为 const 很有必要。

例如对于 `char*-based` 的 `string`，需要定义为：

```cpp
const char* const authorName = "Scott Meyers";
```

对于 `std::string`，需要定义为：

```cpp
const std::string authorName("Scott Meyers");
```

2. class-specific constants(类限定的常量)

可以使用 `static const` 修饰成员：

```cpp
class F {
private:
    static const int num = 5;
};
```

对于类内声明有初值的 `static const` 成员，有时候需要在类外定义（不提供初值）：

```cpp
const int F::num;
```

若类内声明式没有获得初值：

```cpp
class FF {
private:
    static const int num;
};
```

需要在类外实现文件内常量的定义处提供初值：

```cpp
const int FF::num = 55;
```

>[\[c++ primer\] chapter7.6 类的静态成员](https://github.com/piaoliangkb/cppprimer/blob/master/chapter7/README.md#76-%E7%B1%BB%E7%9A%84%E9%9D%99%E6%80%81%E6%88%90%E5%91%98) 
>
>静态成员可以在类内初始化也可以在类外初始化。
>
>类内初始化要求：1. 静态成员必须是字面值常量类型的常量表达式 2. 给静态成员提供的初始值必须是常量表达式。 所以我们可以使用 constexpr 检查成员是否是字面值常量类型。
>
>上述定义语句可以改写为 `static constexpr int num = 5;`

### 使用 enum 代替 #define

若不允许类内定义 static const 常量，可以使用 `the enum hack`。

例如：

```cpp
class GamePlayer {
private:
    enum { NumTurns = 5; };

    int scores[NumTurns];
};
```

### 使用 inline 代替 #define 函数

使用 #define 定义函数有时可以避免函数调用带来的开销。

例如：

```cpp
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))
```

换为内联函数：

```cpp
template<typename T>
inline void call_With_Max(connst T &a, const T &b) {
    f(a > b ? a : b);
}
```

## 03: Use const whenever possible

>尽可能使用 const

- const 写在类型之前，或者 const 写在类型之后，星号之前。这两种写法是等同的。

```cpp
void f1(const int *p);
void f2(int const *p);
```

- const <>::iterator 和 <>::const_iterator

```cpp
std::vector<int> vec;

const std::vector<int>::iterator iter = vec.begin(); // T * const 指针指向不变
*iter = 10;  // true
++iter;      // false

std::vector<int>::const_iterator iter1 = vec.begin(); // const T * 指向内容不变
*iter = 10;  // false
++iter;      // true
```

- 将返回值设置为 const。

例如对于有理数的 `operator*` 函数，定义为：

```cpp
const Rational operator*(const Rational &lhs, const Rational &rhs);
```

可以避免发生如下情况：

```cpp
(a * b) = c;
// or
if (a * b = c){
    // ...
}
```

### const 成员函数

- const 成员函数可以被该类的 const 对象调用，好处为：

1. 可以明确的得知哪个函数可以改变函数内容而哪个函数不行。

2. 让操作 const 对象成为可能。

3. 两个成员函数如果只是常量性不同(differing only in their constness)，则可以被重载。

例如：

若 TextBlock 为常量，则下标调用返回也为常量。否则为非常量。

```cpp
class TextBlock {
public:
    const char &operator[](std::size_t pos) const {
        return text[pos];
    }

    char &operator[](std::size_t pos) {
        return text[pos];
    }
private:
    std::string text;
};
```

- 可以用 mutable 修饰类的成员，让 const 成员函数可以修改这个变量。


>[\[c++ primer\] chapter7 可变数据成员 mutable](https://github.com/piaoliangkb/cppprimer/blob/3d9da248e41878518cba4f329622315ffa52d0c4/chapter7/README.md#%E5%8F%AF%E5%8F%98%E6%95%B0%E6%8D%AE%E6%88%90%E5%91%98)
>
>mutable 用来修饰类的 const 实例中的部分可变数据成员的。即 const 成员函数可以修改这个变量。
>
>例如追踪某个类的成员函数调用了多少次：
>
>```cpp
>class Screen {
>    public:
>        void some_func() const;
>    private:
>        mutable size_t access_time;
>        // .... other members
>}
>
>void Screen::somefunc() const {
>    ++access_time;
>    // .... other operations
>}
>```

- 当 const 和 non-const 成员函数有着 **实质等价的实现(essentially identical implementations)** 时，令 non-const 版本调用 const 版本可避免代码重复。

例如：

```cpp
class TextBlock {
public:
    const char &operator[](std::size_t pos) const {
        // ...
        // ...
        // ...
        return text[pos];
    }

    char &operator[](std::size_t pos) {
        return const_cast<char&>(static_cast(const TextBlock&)(*this)[pos]);
    }
private:
    std::string text;
};
```

解释：

1. 我们先通过 static_cast 运算符将 *this 转换成 const TextBlock& 类型。

2. 此时，让 *this 调用 const 版本的 operator[] 运算符，返回值为 const char &.

3. 使用 const_cast 将 const char & 转换为 char &.

## 04: Make sure that objects are initialized before they're used

>确定对象被使用前已被初始化

对于内置类型，我们可以手工初始化。

对于类类型，我们可以使用构造函数进行初始化。需要确保构造函数将对象的每一个成员都初始化。

### 使用构造函数初始化列表

C++ 中对象的成员变量初始化发生在进入构造函数函数体之前。

例如如下代码：

```cpp
class ABEntry {
public:
    ABEntry(const std::string &name, const std::string &address);

private:
    std::string theName;
    std::string theAddr;
    int numTimes;
};

ABEntry::ABEntry(const std::string &name, const std::string &address) {
    theName = name;
    theAddr = address;
    numTimes = 0;
}
```

在 ABEntry 的构造函数体内，变量不是被初始化而是被赋值。变量的初始化发生在这些成员的 default 构造函数被自动调用之前。而 `numTimes` 由于是内置类型，不能保证他在赋值之前被初始化了。

构造函数的正确写法应该是使用 **初始化列表(member initialization list)**：

```cpp
ABEntry::ABEntry(const std::string &name, const std::string &address)
    : theName(name), theAddr(address), numTimes(0) {}
```

和上一个构造函数对比，上一个构造函数先使用 default 构造函数为 theName 和 theAddr 成员初始化，在函数体在为他们赋值。

使用初始化列表的构造函数直接对成员进行初始化。效率更高。

规定在初始值列表中列出所有成员变量。如果初始值列表遗漏了 `int numTimes`，那么它就没有初值。

如果数据成员是 const 或者 reference，那么它们就必须被初始化而不能被赋值。

### non-local static 对象在不同编译单元的初始化顺序

- static object：寿命从被构造出来到程序结束。包括：全局对象，namespace 中的对象，类内部的 static 对象，函数内的 static 对象，文件作用域内的 static 对象。

- local-static object：定义在函数内的 static 对象(local to a function)。

- non-local-static object：其他的 static 对象。

- translation unit：编译单元。产出单一目标文件的源码。

考虑到两个源码文件，其中每一个都包含一个 non-local static 对象。其中一个 non-local static 对象的初始化使用了另外文件的 non-local static 对象。当初始化该对象时，另外文件的 non-local static 对象可能还没初始化。因为 C++ 没有规定相关的初始化顺序。

例如：

```cpp
// ------ FileSystem.h ------//
class FileSystem {
public:
    std::size_t numDisks() const;
};

extern FileSystem tfs;

// ------ Directory.h ------//
class Directory {
public:
    Directory(params);
};

Directory::Directory(params) {
    std::size_t disks = tfs.numDisks();
}
```

当我们要创建一个 Directory 对象的时候：`Directory dir(params);`。

dir 和 tfs 是不同人定义在不同编译单元的 non-local static 对象，无法保证 tfs 在 dir 前初始化。

- 解决办法：

定义一个函数，将每个 non-local static 对象移动到它自己的函数内，即为每个 non-local static 对象定义一个自己的函数，在这个函数中，它被声明为 static 的。

函数的返回值为他们所含对象的引用。

这种方式保证了函数内的 local static 对象会在函数被调用时初始化；如果没有调用这个函数，则不会发生这个对象的构造和析构操作。non-local static 对象没有这种优势。

此时代码可以修改为：

```cpp
// ------ FileSystem.h ------//
class FileSystem { ... };

FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}

// ------ Directory.h ------//
class Directory { ... };

Directory::Directory(params) {
    std::size_t disks = tfs().numDisks();
}

Directory& tempDir() {
    static Directory td(params);
    return td;
}
```

然而这种初始化方式在多线程情况下可能有不确定性，解决方法是：在程序的单线程启动阶段 (single-threaded startup portion) 手工调用所有的 reference-returning 函数。