

# 第十九章 特殊工具与技术

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
