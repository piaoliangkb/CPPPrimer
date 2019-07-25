<!-- TOC -->

- [第五章](#%e7%ac%ac%e4%ba%94%e7%ab%a0)
  - [5.1 简单语句](#51-%e7%ae%80%e5%8d%95%e8%af%ad%e5%8f%a5)
  - [5.2 语句作用域](#52-%e8%af%ad%e5%8f%a5%e4%bd%9c%e7%94%a8%e5%9f%9f)
  - [5.3 条件语句](#53-%e6%9d%a1%e4%bb%b6%e8%af%ad%e5%8f%a5)
    - [5.3.1 if 语句](#531-if-%e8%af%ad%e5%8f%a5)
      - [悬垂 else (dangling else)](#%e6%82%ac%e5%9e%82-else-dangling-else)
    - [5.3.2 switch 语句](#532-switch-%e8%af%ad%e5%8f%a5)
      - [default label](#default-label)
      - [switch 内部的变量定义](#switch-%e5%86%85%e9%83%a8%e7%9a%84%e5%8f%98%e9%87%8f%e5%ae%9a%e4%b9%89)
  - [5.4 迭代语句](#54-%e8%bf%ad%e4%bb%a3%e8%af%ad%e5%8f%a5)
    - [5.4.1 while语句](#541-while%e8%af%ad%e5%8f%a5)
    - [5.4.2 for语句](#542-for%e8%af%ad%e5%8f%a5)
      - [传统 for循环 的执行流程](#%e4%bc%a0%e7%bb%9f-for%e5%be%aa%e7%8e%af-%e7%9a%84%e6%89%a7%e8%a1%8c%e6%b5%81%e7%a8%8b)
      - [for语句头中的多重定义](#for%e8%af%ad%e5%8f%a5%e5%a4%b4%e4%b8%ad%e7%9a%84%e5%a4%9a%e9%87%8d%e5%ae%9a%e4%b9%89)
      - [省略for语句头的某些部分](#%e7%9c%81%e7%95%a5for%e8%af%ad%e5%8f%a5%e5%a4%b4%e7%9a%84%e6%9f%90%e4%ba%9b%e9%83%a8%e5%88%86)
    - [5.4.3 范围for语句](#543-%e8%8c%83%e5%9b%b4for%e8%af%ad%e5%8f%a5)
    - [5.4.4 do while 语句](#544-do-while-%e8%af%ad%e5%8f%a5)
  - [5.5 跳转语句](#55-%e8%b7%b3%e8%bd%ac%e8%af%ad%e5%8f%a5)
    - [5.5.1 break语句](#551-break%e8%af%ad%e5%8f%a5)
    - [5.5.2 continue语句](#552-continue%e8%af%ad%e5%8f%a5)
    - [5.5.3 goto语句](#553-goto%e8%af%ad%e5%8f%a5)

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

case 关键字和它对应的值一起被称为 case标签 (case label)。case标签 必须是整型常量表达式。

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

