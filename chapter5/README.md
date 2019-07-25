<!-- TOC -->

- [第五章](#第五章)
    - [5.1 简单语句](#51-简单语句)
    - [5.2 语句作用域](#52-语句作用域)
    - [5.3 条件语句](#53-条件语句)
        - [5.3.1 if 语句](#531-if-语句)
            - [悬垂 else (dangling else)](#悬垂-else-dangling-else)
        - [5.3.2 switch 语句](#532-switch-语句)
            - [default label](#default-label)
            - [switch 内部的变量定义](#switch-内部的变量定义)
    - [5.4 迭代语句](#54-迭代语句)
        - [5.4.1 while语句](#541-while语句)
        - [5.4.2 for语句](#542-for语句)
            - [传统 for循环 的执行流程](#传统-for循环-的执行流程)
            - [for语句头中的多重定义](#for语句头中的多重定义)
            - [省略for语句头的某些部分](#省略for语句头的某些部分)
        - [5.4.3 范围for语句](#543-范围for语句)
        - [5.4.4 do while 语句](#544-do-while-语句)
    - [5.5 跳转语句](#55-跳转语句)
        - [5.5.1 break语句](#551-break语句)
        - [5.5.2 continue语句](#552-continue语句)
        - [5.5.3 goto语句](#553-goto语句)
    - [5.6 try 语句块和异常处理](#56-try-语句块和异常处理)
        - [5.6.1 throw 表达式](#561-throw-表达式)
        - [5.6.2 try 语句块](#562-try-语句块)
            - [函数寻找异常处理代码的过程](#函数寻找异常处理代码的过程)
        - [5.6.3 标准异常](#563-标准异常)
            - [初始化异常对象实例](#初始化异常对象实例)

<!-- /TOC -->

# 第五章 

## 5.1 简单语句

- 表达式语句(expression statement)：表达式语句的作用是执行表达式并丢掉求值结果。

例如：

```cpp
ival + 5;
cout << ival;
```

- 空语句(null statement)：空语句只有一个单独的分号，用于语法需要语句而逻辑不需要语句的地方。

- 复合语句(compound statement)：用花括号括起来的语句和声明和序列，复合语句也被称作块。在块中引用的名字只能在块内部以及嵌套在块中的子块里访问。

## 5.2 语句作用域

可以在 if, switch, while, for 语句的控制结构内定义变量，定义在控制结构当中的变量只在相应语句的内部可见。

## 5.3 条件语句

### 5.3.1 if 语句

if 语句的语法形式是：

```
if (condition)
     statement
```

#### 悬垂 else (dangling else)

当有 if 语句嵌套的时候，很可能 if 分支会多于 else 分支。对 C++ 来说，它规定 else 与离它最近的尚未匹配的 if 匹配，从而消除程序的二义性。

### 5.3.2 switch 语句

switch 语句首先对括号里的表达式求值，该表达式跟随在关键词 switch 的后面，可以是一个初始化的变量声明。

表达式的值转换成整数类型，然后与每个 case 标签的值比较。

case 关键字和它对应的值一起被称为 case标签 (case label)。case标签 必须是 ***整型常量表达式*** 。

#### default label

如果没有任何一个 case 标签的值能匹配上 swtich 表达式的值，程序将执行紧随在 default标签 后面的语句。

#### switch 内部的变量定义

C++ 规定，不允许跨过变量的初始化语句直接跳转到该变量作用域内的另一个位置。

例如：

```cpp
case true:
    // 程序的执行流程可能绕开下面的初始化语句，所以该switch语句不合法
    string file_name;    // 隐式初始化，错误
    int ival = 0；       // 显式初始化，错误
    int jval;            // jval 没有被初始化，合理
case false:
    jval = 1;            // 给jval赋值，正确
```

上述写法不推荐，推荐的写法是：把变量定义在块内，从而确保后边的所有标签都在变量的作用域之外。

```cpp
case true:
    {
        string file_name = get_file_name();
    }
    break;
case false:
    cout << file_name << endl;    // 错误，file_name不在作用域内
```

## 5.4 迭代语句

### 5.4.1 while语句

```cpp
while (condition)
    statement
```
定义在 while 条件部分或者 while 循环体内的变量每次迭代都经历从创建到销毁的过程。

### 5.4.2 for语句

```cpp
for (init-statement; condition; expression)
    statement
```

- init-statement 必须是以下三种形式的一种：声明语句，表达式语句，空语句。

#### 传统 for循环 的执行流程

- 循环开始，首先执行一次 init-statement。

- 判断 condition，如果符合条件，执行循环体内内容，否则循环中止。

- 最后执行 expression。

#### for语句头中的多重定义

init-statement 可以定义多个对象，但是 init-statement 只能有一条声明语句，所以所有变量的基础类型必须相同。

例如：

```cpp
for (int i=0, j=0; i<indexi && j<indexj; ++i, ++j)
{
    ;
}
```

#### 省略for语句头的某些部分

- init-statement 可以省略

- condition 可以省略，效果等于在条件部分写了一个 true

- expression 可以省略，这样的循环要求条件部分或者循环体必须改变迭代变量的值，例如：

```cpp
vector<int> v;
for (int i; cin >> i; )
{
    v.push_back(i);
}
```

### 5.4.3 范围for语句

```cpp
for (declaration: expression)
    statement
```

- expression 表示的必须是一个序列，必须用花括号括起来的初始值列表，数组，vector，string等类型的对象。这些对象的共同特点是拥有能够返回迭代器的 begin 和 end 成员。

- declaration 定义一个变量，序列中的每个元素都得能转换成该变量的类型。确保类型相容最简单的方法是使用 auto 类型说明符。

每次迭代都会重新定义循环控制变量，并将其初始化成序列中的下一个值。

范围for语句的定义等价如下：

```cpp
for (auto beg = v.begin(), end = v.end(); beg != end; ++beg)
{
    ...
}
```

所以不能通过范围for语句增加迭代对象的元素，因为范围for语句中预存了 end() 的值。

### 5.4.4 do while 语句

```cpp
do
    statement
while (condition);
```

do while 语句应该在后边加一个分号表示语句结束，

## 5.5 跳转语句

C++ 有四种跳转语句：break, continue, goto, return.

### 5.5.1 break语句

break语句 负责中止离它最近的 while, do while, for, switch 语句。

break语句 只能出现在迭代语句或者 switch语句 的内部。

### 5.5.2 continue语句

continue语句 中止最近的循环中的当前迭代并立即开始下一次迭代。

continue语句 只能出现在 for, while, do while 循环的内部。

### 5.5.3 goto语句

不要在程序中使用 goto语句 ！

```cpp
goto begin;

begin: 
    cout << 123 << endl;
```

## 5.6 try 语句块和异常处理

在 C++ 中，异常处理包括：

- throw 表达式(throw expression)：异常检测部分使用 throw 表达式来表示它遇到了无法处理的问题，我们可以说 throw 引发 (raise) 了异常。

- try 语句块 (try block)：try 语句块以关键字 try 开始，并以一个或多个 catch 子句 (catch clause) 结束。因为 catch 子句处理异常，所以他们也被称作 异常处理代码(exception handler)。

- 一套异常类(exception class)：用于在 throw 表达式和相关的 catch 字句之间传递异常的具体信息。

### 5.6.1 throw 表达式

throw 表达式包括关键字 throw 和紧随其后的一个表达式，其中表达式的类型就是抛出的异常类型。

throw 表达式后面通常紧跟一个分号，从而构成一条表达式语句。

```cpp
if (item1.isbn() != item2.isbn())
    throw runtime_error("Data must refer to same ISBN");

cout << item1 + item2 << endl;
```

### 5.6.2 try 语句块

```cpp
try {
    statements
} catch (exception-declaration) {
    handler-statements
} catch (exception-declaration) {
    handler-statements
}
```

try 块后边是多个 catch 子句，catch 子句包括三个部分：关键字catch，括号内的异常声明（exception declaration），以及一个块。

#### 函数寻找异常处理代码的过程

- 当异常抛出时，首先搜索抛出该异常的函数。

- 当前函数没有找到，就中止该函数，并在调用该函数的函数中继续寻找。

- 如果最后没有找到匹配的 catch 子句，程序转到名为 `terminate` 的标准库函数。该函数行为决定于系统，一般情况下，执行该函数将导致程序非正常退出。

### 5.6.3 标准异常

C++ 标准库定义了一组类，用于报告标准库函数遇到的问题，这些异常类也可以在用户编写的程序中使用。定义在四个头文件中：

- exception 头文件定义了最通用的异常类 exception。

- stdexcept 头文件定义了几种常用的异常类。

异常类名称 | 解释
--- | ---
exception | 最常见的问题
runtime_error | 只有在运行时才能检测出的问题
range_error | 运行时错误：outside the range of values
overflow_error | 运行时错误：计算上溢出
underflow_error | 运行时错误：计算下溢出
logic_error | 程序逻辑错误
domain_error | 逻辑错误：参数对应的结果值不存在
invalid_argument | 逻辑错误：无效参数
length_error | 逻辑错误：试图创建一个超出该类型的最大长度的对象
out_of_range | 逻辑错误：使用一个超出有效范围的值

- new 头文件定义了 bad_alloc 异常类型

- type_info 头文件定义了 bad_cast 异常类型

只能以默认初始化的方法初始化 exception, bad_alloc, bad_cast 对象，不允许为这些对象提供初始值。

其他异常类型的行为则恰好相反：应该用 string 对象或者C风格字符串初始化这些类型的对象，不允许使用默认初始化的方式。创建此类对象时，必须提供初始值，该初始值含有错误相关的信息。

异常类型只定义了一个名为 `what` 的成员函数，该函数没有参数，返回的是一个 `const char*` 。该字符串的目的是提供关于异常的一些文本信息。

#### 初始化异常对象实例

```cpp
int a, b;
cin >> a >> b;

try {
    if (b == 0) throw runtime_error("divisor cannot be 0");
    cout << static_cast<double>(a)/b << endl;
} catch (runtime_error err) {
    cout << err.what() << endl;
}
```