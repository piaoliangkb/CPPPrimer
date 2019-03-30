<!-- TOC -->

- [第二章 变量和基本类型](#第二章-变量和基本类型)
    - [2.1 基本内置类型](#21-基本内置类型)
        - [2.1.1 算术类型](#211-算术类型)
            - [带符号类型和无符号类型](#带符号类型和无符号类型)
            - [选择类型的建议](#选择类型的建议)
        - [2.1.2 类型转换](#212-类型转换)
            - [unsigned char test code](#unsigned-char-test-code)
            - [unsigned int test code](#unsigned-int-test-code)
        - [2.1.3 字面型常量](#213-字面型常量)
            - [整型和浮点型字面值](#整型和浮点型字面值)
            - [字符和字符串字面值](#字符和字符串字面值)
            - [转义序列](#转义序列)
            - [指定字面值的类型](#指定字面值的类型)
            - [练习2.5](#练习25)
    - [2.2 变量](#22-变量)
        - [2.2.1 变量定义](#221-变量定义)
            - [何为对象](#何为对象)
            - [初始化和赋值](#初始化和赋值)
            - [列表初始化](#列表初始化)
            - [默认初始化](#默认初始化)
        - [2.2.2 变量的声明和定义](#222-变量的声明和定义)
            - [静态类型(statically typed)](#静态类型statically-typed)
        - [2.2.3 标识符](#223-标识符)
            - [变量命名规范](#变量命名规范)
        - [2.2.4 名字的作用域](#224-名字的作用域)
            - [嵌套的作用域](#嵌套的作用域)
    - [2.3 复合类型](#23-复合类型)
        - [2.3.1 引用](#231-引用)
        - [2.3.2 指针](#232-指针)
            - [指针和引用的相同点和不同点](#指针和引用的相同点和不同点)
            - [指针存放对象的地址](#指针存放对象的地址)
            - [指针值](#指针值)
            - [利用指针访问对象](#利用指针访问对象)
            - [空指针](#空指针)
            - [指针的赋值](#指针的赋值)
            - [其他指针操作](#其他指针操作)
            - [void* 指针](#void-指针)
        - [2.3.3 理解复合类型的声明](#233-理解复合类型的声明)
            - [指向指针的引用](#指向指针的引用)
    - [2.4 const限定符](#24-const限定符)
        - [2.4.1 const的引用](#241-const的引用)
            - [初始化和对const的引用](#初始化和对const的引用)
            - [对const的引用可以是一个并非const的对象](#对const的引用可以是一个并非const的对象)
        - [2.4.2 指针和const](#242-指针和const)
            - [const指针](#const指针)
            - [练习2.27](#练习227)
            - [练习2.28](#练习228)
        - [2.4.3 顶层const(top level const)和底层const(low level const)](#243-顶层consttop-level-const和底层constlow-level-const)
        - [2.4.4 constexpr和常量表达式](#244-constexpr和常量表达式)
            - [constexpr变量](#constexpr变量)
            - [字面值类型](#字面值类型)
            - [constexpr和指针](#constexpr和指针)
    - [2.5 类型](#25-类型)
        - [2.5.1 类型别名](#251-类型别名)
        - [2.5.2 auto](#252-auto)
            - [练习2.35](#练习235)
        - [2.5.3 decltype类型指示符](#253-decltype类型指示符)
            - [decltype和auto的不同](#decltype和auto的不同)
            - [decltype和引用](#decltype和引用)
    - [2.6 自定义数据结构](#26-自定义数据结构)
        - [2.6.3 使用自己的头文件](#263-使用自己的头文件)
            - [预处理器](#预处理器)

<!-- /TOC -->

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

## 2.2 变量

### 2.2.1 变量定义

变量定义的基本形式是：首先是类型说明符(type specifier)，随后紧跟由一个或多个变量名组成的列表，变量名以逗号分隔，最后以分号结束。

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string book("aes-256-cfb");
    std::cout << book << std::endl;
    std::cout << sizeof(book) << std::endl;
    return 0;
}


// output:
// aes-256-cfb
// 8
// 
// string的size是动态分配的，与sizeof无关。无论放多长的字符串，sizeof都是固定的
// sizeof(std::string) gives you the size of the class instance and its data members, not the length of the string.
// https://stackoverflow.com/questions/3629301/c-sizeof
```

#### 何为对象

对象是一块能存储数据并具有某种类型的内存空间。

#### 初始化和赋值

初始化不是赋值。

- 初始化的含义是创建变量时赋予其一个初始值。
- 赋值的含义时把对象的当前值擦出，以一个新值替代。

#### 列表初始化

```cpp
int a = 0;
int a = {0};
int a{0};
int a(0);
```

#### 默认初始化

- 定义在函数体之外的变量被初始化为0(包括main函数之外)
- 定义在函数体内部的内置类型变量将不被初始化，未被初始化的内置类型变量的值是未定义的，参考**2.1.2 内置变量**

函数体和类：

- 定义于函数体内的内置类型的对象如果没有被初始化，则其值未定义
- 类的对象如果没有显式地初始化，则其值由类确定

### 2.2.2 变量的声明和定义

- 声明：使得某个名字被程序所知，一个文件如果想使用从别处定义的名字，就必须包括对那个名字的声明。

- 定义：负责创建与名字关联的实体。

```cpp
extern int i; // 声明i
int j; // 定义j
extern double a = 3.1415; // 定义a，extern就没用了
```

在函数体内部，如果试图初始化由一个extern关键字标记的变量，将引发错误。在函数体外部则会发出警告<code>warning: 'a' initialized and declared 'extern'</code>

#### 静态类型(statically typed)

静态类型的定义是在编译阶段检查类型，检查类型的过程叫做**类型检查(type checking)**

### 2.2.3 标识符

C++的标识符必须以字母或者下划线开始，不得以数字开始。

#### 变量命名规范

- 变量标识符要能体现实际的含义。
- 变量名一般用小写字母，如index，不要用INDEX或者Index。
- 用户自定义的类名一般以大写字母开头，如Sales_item。
- 如果标识符有多个单词组成，那么单词之间应该有明显的区分，例如student_load或者studentLoad。

### 2.2.4 名字的作用域

C++中大多数作用域都以花括号分隔。

例如：
- main 定义于所有花括号之外，那么他和其他函数名字一样拥有全局作用域(global scope)
- 某个名字作用于函数限定的作用域之内，称作块作用域(block scope)

#### 嵌套的作用域

作用域能被彼此包含，被包含的称为**内层作用域**，包含着别的的称为**外层作用域**。

## 2.3 复合类型

复合类型(compound type)是指基于其他类型定义的类型。

### 2.3.1 引用

>我们现在所说的引用是左值引用(lvalue reference)

引用为对象起了另外一个名字，它并非对象。

```cpp
int ival = 1024;
int &refval = ival; // refval 指向 ival，是ival的另一个名字
```

### 2.3.2 指针

指针(pointer)是指向另一种类型的复合类型。

#### 指针和引用的相同点和不同点

相同点：

- 都实现了对其他对象的间接访问。

不同点：

- 指针本身就是一个对象，允许对指针赋值和拷贝，在指针的生命周期内可以先后指向几个不同的对象。引用并非对象，一旦初始化之后无法将引用重新绑定到另一个对象，必须重新初始化。
- 指针在定义时无需赋初始值，在块作用域内定义的指针如果没有被初始化，将拥有一个不确定的值。引用必须赋值。

```cpp
int *p1, *p2;
double dp, *dp1;
```

#### 指针存放对象的地址

指针存放某个对象的地址，若要获得该地址，必须使用取地址符。

```cpp
int ival = 42;
int *p = &ival;
```

指针类型要和它指向的对象完全匹配。

```cpp
double dval;
double *pd = &dval; // true，初始值是double型对象的地址
double *pd2 = pd; // true，初始值是指向double对象的指针

int *p1 = pd; // false, 指针pi的类型和pd的类型不匹配
pi = &dval； // false，试图把double型对象的地址赋给int型指针
```

#### 指针值

- 指向一个对象。
- 指向紧邻对象所占空间的下一个位置（用来标识有效对象的边界，一旦到达这里表示有效对象要结束了）
- 空指针。
- 无效指针，上述情况之外的其他值。

第四种指针访问或者拷贝都将引发错误，编译器不负责检查此类错误。  

第二种和第三种形式的指针是有效的，但是这些指针没有指向任何具体的对象，所以试图访问此类指针对象的行为不被允许。

#### 利用指针访问对象

如果指针指向了一个对象，则允许使用解引用符(*)来访问该对象：

```cpp
int ival = 42;
int *p = &ival;
cout << *p;
```

对指针解引用会得出所指的对象，如果给解引用的结果赋值，实际上也就是给指针所指的对象赋值。

```cpp
*p = 0;
cout << *p; // output is 0
```

#### 空指针

空指针(null pointer)不指向任何对象。

生成空指针的方法

```cpp
int *p1 = nullptr; // c++11的新标准
int *p2 = 0; 
// 需要先导入cstdlib
int *p3 = NULL;
```

过去的程序还会使用一个名为NULL的**预处理变量(prprocessor variable)**来给指针赋值，这个变量在头文件<code>cstdlib</code>中定义，它的值是0.

如果使用了未经初始化的指针，则该指针所占的内存空间当前的内容将被看作一个地址值。如果访问该指针，则相当于访问一个本不存在位置上本不存在的对象。

#### 指针的赋值

```cpp
int i = 42;
int *pi = 0;      // pi被初始化，但是不指向任何对象
int *pi2 = &i;    // pi2被初始化，指向i
int *pi3;         // 如果pi3被定义在块内，那么pi3的值无法确定

pi3 = pi2;        // pi3和pi2指向同一个对象pi2
pi2 = 0;          // pi2不指向任何对象

pi = &ival;       //pi的值被改变，现在指向ival
*pi = 0;          // ival的值被改变，pi不变
```

- “=”的左操作数可以是*p，也可以是p。
- 当“=”的左操作数是*p时，改变的是p所指向的地址存放的数据。
- 当“=”的左操作数是p时，改变的是p所指向的地址。

https://blog.csdn.net/snowq/article/details/2050129

#### 其他指针操作

指针可以用在条件表达式中，如果指针是0，则条件表达式为false。

对于两个类型相同的合法指针，可以用==或者!=来判断，两个指针存放地址相同有三种可能：

- 都为空
- 都指向同一个对象
- 都指向同一个对象的下一个地址

注：一个指针指向某个对象，另一个指针指向另外对象的下一个地址，此时也有可能出现两个指针值相同的情况。

#### void* 指针

<code>void*</code>可用于存放任意对象的地址。

```cpp
double obj = 3.14, *pd = &obj;
void *pv = &obj;
pv = pd;
```

### 2.3.3 理解复合类型的声明

#### 指向指针的引用

引用不是对象，因此不能定义指向引用的指针；指针是对象，存在对指针的引用。

```cpp
int i = 42;
int *p;
int *&r = p;         // r是对指针p的引用

r = &i;              // r引用了指针p，所以给r赋值&i就是把指针p指向i
*r = 0;              // 解引用r得到i，也就是p指向的对象，所以i的值被改为0
```

上述例子中，我们要理解r的值是什么，最简单的办法就是从右向左阅读r的定义。离变量名最近的符号有最直接的影响，此处是&符号，表示r是一个引用；符号*表示r引用的是一个指针；根据声明符指出r引用的是一个int型指针。

## 2.4 const限定符

我们使用const限定符使得变量的值不能被改变。因为const对象一旦创建之后它的值就不能被改变，所以const对象必须初始化。

默认情况下，const对象仅在文件内有效，例如定义一个bufsize

```cpp
const int bufSize = 512;
```

编译器在编译过程中把所有用到该变量的地方替换成对应的值。如果程序包含多个文件，则每个用了const对象的文件都必须得能访问到他们的初始值才行，要做到这一点，就必须在每一个用到变量的文件中都有对它的定义。

为了支持这一用法，同时避免对同一个变量的重复定义，默认情况下const对象被设定为仅在文件内有效。多个文件出现了同名的const变量的时候，等同于在不同的文件中分别定义了独立的变量。

如果要解决多个文件共享一个const对象，解决方法是对const变量的定义和声明都添加<code>extern</code>关键字：

```cpp
// file1.h头文件
extern const int bufsize;
// file1.cpp
extern const int bufsize = 1024;
```

### 2.4.1 const的引用

可以把引用绑定到const上，我们称为**对常量的引用**。

```cpp
const int a = 1024;
const int &r = a;       // true
r = 42;                 // false, 不能修改const的值
int &r2 = a;            // false，试图让一个非const引用指向一个const对象
```

#### 初始化和对const的引用

**2.3.1节**提到，引用的类型必须和其引用的对象一致，但是有两个例外。一个是在初始化常量引用的时候，允许用任意表达式作为初始值，只要表达式的值可以转换成引用的类型即可。

```cpp
int i = 42;
const int &r1 = i;     // 允许将const int&绑定到一个普通的int对象上
const int &r2 = 42;    // 正确，r2是一个常量引用
const int &r3 = r1*2;  // 正确，r3是一个常量引用
int &r4 = r1*2;        // 错误，r4是一个普通的非常量引用
```

当一个常量引用被绑定到另一种类型上时，发生了什么：

```cpp
double dval = 3.14;
const int &ri = dval;
```

此处ri引用了一个int型的数，但是dval却是一个双精度浮点数而非整数，为了确保让ri绑定一个整数，编译器把上述代码变成了如下形式：

```cpp
const int temp = dval;  // 由双精度浮点数生成一个临时的整形变量
const int &ri = temp;   // 让ri绑定到这个临时量
```

那么当ri不是常量时，即不加const，那么就会允许对ri赋值。然而此时绑定的对象时temp而不是dval，不合理，所以C++把这种行为归为非法。

#### 对const的引用可以是一个并非const的对象

```cpp
int main()
{
    int i = 42;
    int &r1 = i;
    const int &r2 = i;

    cout << r2 << endl;
    r1 = 40;
    cout << r2 << endl;

    return 0;
}
// output is : 42 40
```

上述例子中常量引用r2绑定了i，修改i值的话，r2的值也会变化.

### 2.4.2 指针和const

指向常量的指针不能用于改变其所指对象的值，但没有规定指向对象的值不能通过其他方式改变。

```cpp
const double pi = 3.14;
double *ptr = &pi;        // false ptr是一个普通指针
const double *cptr = &pi; // true
*cptr = 42;               // false

double dval = 3.14;
cptr = &dval;             // true
```

指向常量的指针不规定其所指的对象必须是一个常量。

#### const指针

常量指针(const pointer)必须初始化，把*放在const关键字之前用以说明指针是一个常量，即不变的是指针本身的值而非指针指向的值。

```cpp
int num = 0;
int *coust curNum = &num;

const double pi = 3.14;
const double *const pip = &pi; // pip是一个指向常量对象的常量指针
```

#### 练习2.27

```cpp
int i = -1, &r = 0;          // 不合法，非常量引用必须引用到相关的对象
int *const p2 = &i2;         // 合法，p2是一个常量指针
const int i = -1, &r = 0;    // 合法，i为常量-1，r为常量引用，可以为0；非常量引用必须引用相关的对象
const int *const p3 = &i2;   // 合法，p3是一个指向常量的常量指针
const int *p1 = &i2;         // 合法，p1是一个指向常量的指针
const int &const r2;         // 不合法，引用不能加const
const int i2 = i, &r = i;    // 合法，i2为一个常量，r为一个常量引用
```

> const在前表示指针指向或者引用的对象为常量，const在指针后表示指针为常量指针

#### 练习2.28

```cpp
int i, *const cp;           // 不合法，cp为常量指针必须被初始化
int *p1, *const p2;         // 不合法，p2为常量指针，必须被初始化
const int ic, &r = ic;      // 不合法，ic为常量，必须被初始化
const int *const p3;        // 不合法，p3为指向常量的常量指针，必须被初始化
const int *p;               // 合法，p为指向常量的指针
```

### 2.4.3 顶层const(top level const)和底层const(low level const)

顶层表示对象（指针本身）是个常量，底层表示指针指向的对象是个常量。

```cpp
int i = 0;
int *const p1 = &1;          // 顶层const，指针p1的值不能被修改
const int ci = 42;           // 顶层const，ci的值不能被修改
const int *p2 = &ci;         // 底层const，指针p2的值可以被修改
const int *const p3 = p2;    // 右边的const是顶层const，左边的const是底层const
const int &r = ci;           // 用于声明引用的const都是底层const
```

在执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层const资格，或者两个对象能够进行数据转化。非常量可以转化成常量。

### 2.4.4 constexpr和常量表达式

常量表达式(const expression)是指值不会改变并且在编译过程中就能得到计算结果的表达式。字面值属于常量表达式。

```cpp
const int max_file = 20;  // 是常量表达式
const int limit = max_file +1; // 是常量表达式
int staff_size = 3; // 不是常量表达式
const int sz = get_size(); // 不是常量表达式
```

#### constexpr变量

C++11的新标准规定，允许将变量声明为<code>constexpr</code>类型以便由编译器来验证变量的值是否为一个常量表达式。声明为constexpr的值一定是一个常量，而且必须用常量表达式初始化。

```cpp
constexpr int mf = 20;    // 20是常量表达式
constexpr int limit = mf+1;
constexpr int sz = size(); // 当size是一个constexpr函数时，这才是一条正确的声明语句。具体看6.5.2节
```

#### 字面值类型

截至目前，算术类型、引用、指针都属于字面值类型。

尽管指针和引用都可以定义成constexpr，但是一个constexpr指针的初始化必须是nullptr或者0，或者是存储于某个固定地址中的对象（函数体之内的变量地址不固定，函数体制外地址固定不变）。

#### constexpr和指针

如果在constexpr生命中定义了一个指针，那么限定符constexpr只对指针起作用，与指针所指的对象无关。

```cpp
const int *p = nullptr;        // p是一个指向整数常量的指针
constexpr int *q = nullptr;    // q是一个指向整数的常量指针，顶层const
```

## 2.5 类型

### 2.5.1 类型别名

定义类型别名的两种方式：

- 使用关键字**typedef**

```cpp
typedef double wages;
typedef wages base, *p;  // base是double的同义词，p是double*的同义词
```

- 使用别名声明(alias declaration)

```cpp
using SI = Sales_item; // SI是Sales_item的同义词
```

>注：不要把别名替换成他本来的样子去理解代码

### 2.5.2 auto

auto让编译器通过初始值来推断变量的类型，所以auto定义的变量必须有初始值。

当引用被用作初始值时，真正参与初始化的其实是引用对象的值，此时编译器引用对象的类型作为auto的类型：

```cpp
int i = 0, &r = i;
auto a = r;
```

这时，a是一个int类型。

auto一般会忽略掉顶层const(对象本身是个常量)，底层const一般会保存下来，例如当初始值是一个指向常量的指针时：

```cpp
const int ci = i, &cr = ci;
auto b = ci; // b是一个整数，顶层const被忽略掉
auto c = cr; // c是一个整数，cr是对ci的引用，而ci是一个顶层const
auto d = &i; // d是一个整形指针
auto e = &ci; // e是一个指向整型常量的指针(对常数对象取地址是一种底层const)
```

如果希望推断出的auto类型是一个顶层const：

```cpp
const auto f = ci;
```

此外还可以将引用的类型设置为auto，原来的初始化规则仍然适用：

```cpp
auto &g = ci; // g是一个整形常量引用，绑定到ci
auto &h = 42; // 错误，不能将非常量引用绑定到字面值，需要在前边加const
const auto *j = 43;  // 正确
```

#### 练习2.35

```cpp
const int i = 42;  // const int
auto j = i;        // int
const auto &k = i; // 对常量的引用
auto *p =  &i;     // 对常量对象取地址是底层const，保存，const int*

const auto j2 = i, &k2 = i; // const int, const int&
```

### 2.5.3 decltype类型指示符

类型说明符**deceltype**的作用是选择并返回操作数的数据类型。在这个过程中，编译器分析表达式的值并得到它的类型，缺不实际计算表达式的值：

```cpp
decltype(f()) sum = x; // sum的类型就是函数f()的返回类型
```

#### decltype和auto的不同

- decltype使用的表达式如果是一个变量，那么decltype返回该变量的类型。
- auto一般会忽略掉顶层const，底层const会保留下来。

#### decltype和引用

decltype的结果可以是引用类型

```cpp
int i = 42, *p = &i, &r = i;
decltype(r+0) b;    // 加法的结果是int，因此b是一个未初始化的int
decltype(*p) c;     // 错误，c是一个int&，必须被初始化
```

如果表达式的内容是解引用操作，那么decltype将得到引用类型。

**解引用指针可以得到指针所指的对象，而且还能给这个对象赋值。因此decltype(*p)的结果类型就是int&，而不是int。**

**对于左值表达式或者带括号的表达式，decltype的结果永远是引用。而decltype(v)只有当v本身就是一个引用的时候结果才是引用。**

参考资料：

- https://stackoverflow.com/questions/25312225/c-why-decltype-this-returns-a-reference
- https://www.cnblogs.com/QG-whz/p/4952980.html

## 2.6 自定义数据结构

### 2.6.3 使用自己的头文件

头文件通常包含那些只能被定义一次的实体，如类，const和constexpr变量。

有时候需要对头文件做适当的处理，使其遇到多次包含的情况也能安全和正常的工作。

#### 预处理器

确保头文件多次包含仍能安全工作的常用技术是预处理器。预处理器是在编译之前执行的一段程序。<code>#include</code>就是一项与处理功能。当预处理器看到<code>#include</code>标记时，就会用指定的头文件内容代替<code>#include</code>。

另一个预处理功能是**头文件保护符(header guard)**.

- <code>#define</code>指令把一个名字设定为预处理变量
- <code>#ifdef</code>当且仅当变量已定义时为真
- <code>#ifndef</code>当且仅当变量未定义时为真
- 一旦检查结果为真，执行后续操作直到<code>#endif</code>指令为止

整个程序中预处理变量包括头文件保护符必须唯一，通常的做法是基于头文件中类的名字来构建保护符的名字。

- 头文件即使没有被包含在任何头文件中，也应该设置保护符。习惯加上！

例如：

```cpp
// file1.h
class file1 {
};

// file2.h
#include "file1.h"
class file2 {
};

// file3.h
#include "file1.h"
#include "file2.h"
```

这时，file3.h文件展开式这样的：

```cpp
// file1.h展开的内容
class file1 {
};
// file2.h展开的内容
class file1 {
};
class file2 {
};
```

这时，file1类就被重定义了。需要给每个文件加上头文件保护符：

```cpp
// file1.h
#ifndef FILE1_H
#define FILE1_H

class file1{};

#endif
```

```cpp
// file2.h
#ifndef FILE2_H
#define FILE2_H

#include "file1.h"
class file2 {};

#endif
```

```cpp
// file3.h
#ifndef FILE3_H
#define FILE3_H

#include "file1.h"
#include "file2.h"

#endif
```

此时展开file3.h文件，<code>FILE1_H</code>只会被定义一次，就不会出现重定义错误了。