# 第二章 变量和基本类型

## 2.1 基本内置类型

C++定义了一套包含算术类型(arithmetic tyoe)和空类型(void)在内的基本数据类型。

### 2.1.1 算术类型

类型 | 含义 | 最小尺寸
--- | --- | ---
bool | 布尔类型 | 未定义
char | 字符 | 8 bit
wchar_t | 宽字符 | 16 bit
char16_t | Unicode字符 | 16 bit
char32_t | Unicode字符 | 32 bit
short | 短整形 | 16 bit
int | 整形 | 16 bit
long | 长整形 | 32 bit
long long | 长整形 | 64 bit
float | 单精度浮点数 | 6位有效数字
double | 双精度浮点数 | 10位有效数字
long double | 拓展精度浮点数 | 10位有效数字

- 基本的字符类型是char，一个char的空间应确保可以存放机器基本字符集中任意字符对的数字值。也就是说，一个char的大小和一个机器字节一样
  
- wchar_t用于确保可以存放机器最大拓展字符集中的任意一个字符, char16_t, char32_t为Unicode字符集服务(Unicode字符集是用于表示所有自然语言中字符的标准)

- 一个int至少和一个short一样大，一个long至少和一个int一样大，一个long long至少和一个long一样大。

- C++标准制定了一个浮点数有效位数的最小值，大多数编译器都实现了更高的精度。

- 通常，float以一个字(32 bit)表示，double以2个字(64 bit)来表示，long double以3或4个字(96 或 128 bit)来表示。一般来说，float和double分别有7个和16个有效位。类型long double常常被用于有特殊浮点需求的硬件。

#### 带符号类型和无符号类型

- 类型int, short, long, long long都是带符号的，通过在这些类型前边加unsigned就可以得到无符号类型。(unsigned int 可以缩写为 unsigned)

- 字符型分为 char, signed char, unsigned char.然而字符的表现形式只分为两种：带符号的和无符号的，char会表现哪种根据编译器决定。

- 无符号类型中的所有bit都用来存储值，例如8 bit的unsigned char可以表示0~255区间内的值。

#### 选择类型的建议

- 当明确知晓数值不可能为负时，选用无符号类型。

- 使用int执行整数运算。short常常太小，long和int有一样的尺寸。如果数值超过int的范围就使用long long。

- 只有在存放字符和布尔值时才使用char和bool。char在不同的机器上符号不同。如果使用一个不大的整数，一定要执行时signed char还是unsigned char。

- 执行浮点运算用double。对于某些机器来说双精度运算更快，long double运行消耗过大。

### 2.1.2 类型转换

```cpp
bool b = 42; // b is TRUE
int i = b; // i = 1
i = 3.14; // i = 3
double pi = i; // pi = 3.0
unsigned char c = -1; // 若unsigned char占8 bit，则c = 255
signed char c = 256； // 若signed char占8 bit，则c未定义
```

- 当我们赋给无符号类型一个超出他表示范围的值时，结果是初始值对无符号类型表示数值总数取模之后的余数。例如8bit大小的unsigned char可以表示0~255之内的值，如果赋予了区间外的值，实际结果是该值对256取模后的余数。

- 当我们赋给带符号类型一个超出他表示范围的值时，结果是未定义的，undefined。此时程序可能继续工作，可能崩溃，也可能生成垃圾数据。

#### unsigned char test code

```cpp
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    unsigned char c = 96;
    cout << c << endl;
    printf("%d\n", c);

    unsigned char c2 = -1;
    cout << c2 << endl;
    printf("%d\n", c2);

    signed char c3 = 256;
    cout << c3 << endl;
    printf("%d\n", c3);
    
    return 0;
}

```

输出结果：

![](https://ws1.sinaimg.cn/large/7e197809ly1g15zulj3c0j20u20b50tu.jpg)

#### unsigned int test code 

```cpp
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    unsigned int n = -10;
    cout << n << endl;
    printf("%d\n", n); // %d表示有符号整数
    printf("%u\n", n); // %u表示无符号整数
    return 0;
}
```

输出结果：

```
4294967286
-10
4294967286
```

### 2.1.3 字面型常量

#### 整型和浮点型字面值

- 十进制字面值的类型是int, long, long long中尺寸最小的那个，前提时这种类型要容得下当前的值。一般来说十进制字面值不会是负数，对于-42这样的字面值，符号不在字面值之内。

- 八进制和十六进制字面值的类型是能容纳其数值的int, unsigned int, long, unsigned long, long long, unsigned long long中的尺寸最小者。

- 如果一个字面值连与之关联的最大的数据类型都放不下，将产生错误。

- 类型short没有对应的字面值。

- 浮点型字面值默认是一个double。

#### 字符和字符串字面值

- 字符串字面值是由常量字符构成的数组，结尾添加空字符'\0'
- 字符串字面值可以分多行书写

```cpp
std::cout << "a really long string "
             "that spans two lines" << std::endl;
```

#### 转义序列

有两类字符串不能直接使用：不可打印的字符串，比如退格或者其他控制字符，因为他们没有可视的图符；另一类是在C++语言中有特殊含义的字符（单引号，双引号，问号，反斜线），在这些情况下需要用到转义序列。

C++规定的转义序列包括如下：

转义序列 | 表示
---|---
换行符 | \n
纵向制表符 | \v
横向制表符 | \t
反斜线 | \\\
回车符 | \r
退格符 | \b
问号 | \\?
进纸符 | \f
报警符 | \a
双引号 | \\"
单引号 | \\'

泛化的转义序列：

- \x后边紧跟一个或多个16进制数字。例如<code>\x1234</code>表示一个16位的字符，该字符由这4个十六进制数所对应的比特唯一确定。因为大多数辑器的char型数据占8位，所以上边这个例子可能会报错。

- \后边紧跟一个或两个或三个八进制数字。如果反斜线后边的八进制数字超过三个，只有前三个数字与\构成转义序列。例如 <code>\1234</code> 表示两个字符，即八进制数123对应的字符以及字符4.

#### 指定字面值的类型

```cpp
L'a' // 宽字符型字面值，类型是'wchar_t'
u8"hi!" // utf-8字符型字面值，utf-8是用8位编码一个Unicode字符
42NLL // 无符号整数型字面值，类型是unsigned long long
1E-3F // 单精度浮点型字面值，类型是float
3.14159L // 拓展精度浮点型字面值，类型是long double 
```

前缀类型：

前缀 | 含义 | 类型
--- | --- | ---
u | Unicode16字符 | char16_t
U | Unicode32字符 | char32_t
L | 宽字符 | wchar_t
u8 | UTF-8(仅用于字符串字面常量) | char

后缀类型：

整形字面型后缀 | 最小匹配类型
--- | --- 
u or U | unsigned 
l or L | long 
ll or LL | long long

以U为后缀的十进制数，八进制数或十六进制数都将从unsigned int， unsigned long， unsigned long long中选择能匹配的空间最小的一个作为其数据类型。


浮点型字面型后缀 | 类型
--- | ---
f or F | float
l or L | long double

#### 练习2.5

> 指出下面字面值的字符类型  
> (a) 'a', L'a', "a", L"a"  
> (b) 10, 10u, 10L, 10uL, 012, 0xC  
> (c) 3.14, 3.14f, 3.14L  
> (d) 10, 10u, 10., 10e-2

答案：

(a)字符字面值(character literal)，宽字符字面值(wide character literal)，字符串字面值(string literal)，宽字符字符串字面值(string wide character literal)  

(b)十进制(decimal)，无符号十进制(unsigned decimal)，长整形十进制(long decimal)，无符号长整形十进制(unsigned long decimal)，八进制(octal)，十六进制(hexadecimal)  

(c)double， float， long double

(d)十进制，无符号十进制，double， double