<!-- TOC -->

- [第六章 函数](#第六章-函数)
    - [6.1 函数基础](#61-函数基础)
        - [调用函数](#调用函数)
        - [形参和实参](#形参和实参)
        - [函数的形参列表](#函数的形参列表)
        - [函数返回类型](#函数返回类型)
        - [6.1.1 局部对象](#611-局部对象)
            - [自动对象](#自动对象)
            - [局部静态对象](#局部静态对象)
        - [6.1.2 函数声明](#612-函数声明)
            - [在头文件中进行函数声明](#在头文件中进行函数声明)
        - [6.1.3 分离式编译](#613-分离式编译)
            - [编译和链接多个源文件](#编译和链接多个源文件)
    - [6.2 参数传递](#62-参数传递)
        - [6.2.1 传值 参数](#621-传值-参数)
            - [指针形参](#指针形参)
        - [6.2.2 传引用 参数](#622-传引用-参数)
            - [使用引用避免拷贝](#使用引用避免拷贝)
            - [使用引用形参返回额外信息](#使用引用形参返回额外信息)
        - [6.2.3 const 形参和实参](#623-const-形参和实参)
            - [const 和 指针，引用形参](#const-和-指针引用形参)
            - [尽量使用常量引用](#尽量使用常量引用)
        - [6.2.4 数组形参](#624-数组形参)
            - [传递数组形参的大小](#传递数组形参的大小)
                - [使用标记指定数组长度](#使用标记指定数组长度)
                - [使用标准库规范](#使用标准库规范)
                - [显式传递一个表示数组大小的形参](#显式传递一个表示数组大小的形参)
            - [数组引用形参](#数组引用形参)
            - [传递多维数组](#传递多维数组)
        - [6.2.5 main函数：处理命令行参数](#625-main函数处理命令行参数)
        - [6.2.6 含有可变形参的函数](#626-含有可变形参的函数)
            - [initializer_list 形参](#initializer_list-形参)
            - [省略符形参](#省略符形参)
    - [6.3 返回类型和 return 语句](#63-返回类型和-return-语句)
        - [6.3.1 无返回值函数](#631-无返回值函数)
        - [6.3.2 有返回值函数](#632-有返回值函数)
            - [值是如何被返回的](#值是如何被返回的)
            - [不要返回局部对象的引用或指针](#不要返回局部对象的引用或指针)
            - [返回 类 的函数](#返回-类-的函数)
            - [引用返回左值](#引用返回左值)
            - [列表初始化返回值](#列表初始化返回值)
            - [主函数 main 的返回值](#主函数-main-的返回值)
            - [递归](#递归)
        - [6.3.3 函数返回数组指针](#633-函数返回数组指针)
            - [直接定义](#直接定义)
            - [使用类型别名](#使用类型别名)
            - [使用尾置返回类型(trailing return type)](#使用尾置返回类型trailing-return-type)
            - [使用 decltype](#使用-decltype)
        - [练习6.36 6.37](#练习636-637)

<!-- /TOC -->

# 第六章 函数

## 6.1 函数基础

一个函数包括以下部分：

- 返回类型 (return type)

- 函数名

- 由0个或多个形参(parameter)组成的列表

- 函数体(function body)

使用 **调用运算符 (call operator)** 来执行函数。调用运算符是一对圆括号，作用于一个表达式，该表达式是 **函数** 或者 **指向函数的指针**。

### 调用函数

函数的调用完成两项工作：

1. 用实参初始化函数对应的形参

2. 将控制权转移给被调用函数；主调函数 (calling function) 的执行被暂时中断，被调函数 (called function) 开始执行。

执行函数的第一步：

1. 隐式的定义并初始化形参

遇到 return 的执行过程：

1. 返回 return 语句中的值

2. 将控制权从被调函数转移回到主函数

### 形参和实参

1. 实参和形参存在对应关系，但是没有规定实参的求值顺序。编译器能以任意可行的顺序对实参求值。

2. 实参的类型必须和形参的类型匹配

### 函数的形参列表

1. 函数的形参列表可以为空，为了和C语言兼容，也可以使用关键字 void 表示函数没有形参。

2. 即使两个形参类型一样，也必须把两个类型都写出来。

```cpp
int f (int a, int b)
{
    ...
}
```

### 函数返回类型

- 返回类型为 void ，表示函数不返回任何值。

- 返回类型不能为数组或者函数类型，但是可以为 **指向数组的指针** 或 **指向函数的指针** 。

### 6.1.1 局部对象

函数体是一个语句块，块构成一个新的作用域，我们可以在内部定义变量。

形参和函数体内定义的变量统称为局部变量(local variable)，仅在函数作用域内可见，若有重名变量，则函数体内变量起作用。

#### 自动对象

只存在于块执行期间的对象称为 **自动对象** (automatic object)。

形参是一种自动对象，对于局部变量对应的自动对象来说：

1. 如果变量定义本身含有初始值，就用这个初始值初始化；

2. 变量定义本身不含有初始值，执行默认初始化。产生未定义的值。

>p40 定义在函数体内的内置类型变量将不被初始化，一个未被初始化的内置类型变量的值是未定义的。

#### 局部静态对象

使用 `static` 定义的对象。

局部静态对象(local static object) 在程序执行路径第一次经过对象定义语句时初始化，并且直到程序终止才被销毁。

如果局部静态变量没有显式初始值，执行值 **初始化** ，内置类型的局部静态变量初始化为0。

### 6.1.2 函数声明

函数只能定义一次，但是可以声明多次。如果一个函数没有被用到，那么它可以只有声明没有定义。

函数声明示例：

`void print(vector<int>::const_iterator begin, vector<int>::const_iterator end);`

#### 在头文件中进行函数声明

函数应该在头文件中声明，在源文件中定义。

### 6.1.3 分离式编译

C++ 支持分离式编译(seperate compilation)。分离式编译允许我们把程序分割到几个文件中去。

#### 编译和链接多个源文件

如果 face 函数定义在一个 face.cc 文件中，声明位于 Chapter6.h 文件中。

face.cc 文件应该包含 Chapter6.h 头文件。

在 faceMain.cc 的文件中创建 main 函数，main 函数将调用 face 函数。

对于上述步骤，若要使用 g++ 编译器生成可执行文件：

```bash
$ g++ faceMain.cc face.cc  # generate faceMain.exe or a.out
$ g++ faceMain.cc face.cc -o main # generate main or main.exe
```

如果只修改了一个源文件，那么我们只需要重新编译改动了的文件。编译器提供了分离式编译每个文件的机制，这一过程通常会产生后缀名为 `.obj` 或者 `.o` 的文件，后缀名含义是该文件包含 对象代码 (object code)。

接下来编译器负责链接。

```bash
$ g++ -c faceMain.cc # generate faceMain.o
$ g++ -c face.cc # generate face.o
$ g++ faceMain.o face.o # generate faceMain.exe or a.out
$ g++ faceMain.o face.o -o main # generate main.exe or main
```

## 6.2 参数传递

- 形参为引用类型：绑定到对应的实参上。实参被引用传递 (passed by reference)，函数被传引用调用 (called by reference)。

- 形参为非引用类型：将实参的值拷贝后赋值给形参。形参和实参是两个独立的对象，这样的实参被值传递 (passed by value)，函数被传值调用 (called by value)。

### 6.2.1 传值 参数

当初始化一个非引用类型的变量时，初始值被拷贝给变量。

#### 指针形参

当执行指针拷贝操作时，拷贝的是指针的值，和两个指针是不同的指针，但是访问的对象相同也可以修改。

例如，使用函数交换两个数的值：

```cpp
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

C++ 中建议使用引用类型的形参代表指针，来访问函数外部的变量。

### 6.2.2 传引用 参数

通过引用形参，可以让函数改变一个或者多个实参的值。

例如，利用函数重置一个值为0：

```cpp
void reset(int &i)
{
    i = 0;
}
```

#### 使用引用避免拷贝

拷贝大的类类型对象比较低效，甚至有的类类型就不支持拷贝(IO类型)。

例如，string 对象可能比较长，使用引用形参避免拷贝：

```cpp
bool compare(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
```

其中，如果函数无需改变引用形参的值，那么最好将其声明为常量引用。

#### 使用引用形参返回额外信息

若一个函数想要返回多个信息，可以定义一个新的数据类型，或者使用引用形参可以一次返回多个结果。

### 6.2.3 const 形参和实参

顶层const 作用于对象本身，当用实参初始化形参时，会忽略掉 顶层const。当形参有 顶层const 时，传给他常量对象或者非常量对象都可以。

忽略掉顶层const的一个缺陷：在C++中允许函数名字相同，形参不同。但是由于忽略掉顶层const，所以如下定义是重复定义

```cpp
void f(const int i);
void f(int i);
```

由于顶层const 被忽略掉，所以他们的形参一样。

#### const 和 指针，引用形参

可以使用非常量初始化一个底层 const 对象。

#### 尽量使用常量引用

把函数不会改变的形参定义长引用是一种比较常见的错误，这种做法会带来一种误导：函数可以修改它的实参的值。

使用引用而非常量引用会限制函数能接受的实参类型：不能把 const 对象，字面值传递给普通的引用形参。

### 6.2.4 数组形参

数组的两个特殊性质让我们在定义和使用数组上的函数有影响：

- 不允许拷贝数组，所以不能以值传递的方式使用数组参数。所以当为函数传递一个数组时，实际上传递的是指向数组首元素的指针。

- 使用数组时通常会转换成指针。

其中，三个等价的传递数组的参数：

```cpp
void print(const int*);
void print(const int[]);
void print(const int[10]);    // 这里体现了我们期望数组有多少元素，实际数量不一定。
```

上述三个函数调用时，只检查传入的参数是否为 `const int*` 类型。

例如:

```cpp
int i = 0, j[2] = {0, 1};
print(&i); // true
print(j);  // true
```

以数组作为形参的函数必须保证使用数组时不会越界。

#### 传递数组形参的大小

数组是以指针形式传递给函数的，所以一开始函数不知道数组的确切尺寸。传递数组形参的大小有三种方式。

##### 使用标记指定数组长度

要求数组本身包含一个结束标记，例如C风格字符串：C风格字符串存储在字符数组中，并且在最后一个字符后面跟着一个空字符`\0`。

```cpp
void print(const char *cp)
{
    if (cp)         // 如果cp不是一个空指针
    {
        while (*cp) cout << *cp++;  // 当cp不是一个空字符'\0'，打印并向前移动一个位置
    }
}
```

##### 使用标准库规范

传递指向数组首元素和尾后元素的指针。

```cpp
void print(const int *begin, const int *end)
{
    while (begin != end)
     cout << *begin++ << endl;
}
```

为了调用这个函数，需要传递两个指针：指向首元素和指向结尾元素下一个元素的指针。

```cpp
int j[2] = {0, 1};
print(std::begin(j), std::end(j));
```

##### 显式传递一个表示数组大小的形参

专门定义一个表示数组大小的形参。

```cpp
void print(const int ia[], size_t size)
{
    for (size_t i = 0; i != size; ++i)
    {
        cout << ia[i] << endl;
    }
}
```

调用的时候必须传入数组的大小。

```cpp
int j[] = {1, 2};
print(j, std::end(j) - std::begin(j));
```

#### 数组引用形参

C++ 允许将变量定义为数组的引用，形参也可以是数组的引用。

```cpp
void print(int (&arr)[10])
{
    for (auto i : arr)
        cout << i << endl;
}
```

其中，arr 两端的括号不可少。

- `int &arr[10]` 表示有10个 int 引用的数组

- `int (&arr)[10]` 表示 arr 是引用，类型为 int ，大小为10，即大小为10的 int 类型数组

然而这种方法限制了 print 函数的可用性，只能将函数作用于大小为10的数组：

若要传入数组 `int j[2] = {0, 1};`，会报错：

```
error: invalid initialization of reference of type 'const int (&)[10]' from expression of type 'int [2]'
```

#### 传递多维数组

```cpp
void print(int (*matrix)[10], int rowSize)；
// 等价定义
void print(int matrix[][10], int rowSize); // 从声明看起来是二维数组，实际是指向含有10个整数的数组的指针
```

其中，matrix 指向数组的首元素，数组的每个元素都是大小为10的数组。

*matrix 两端的括号不可少：

- `int *matrix[10];` 表示 matrix 是 int* 类型的数组，大小为10

- `int (*matrix)[10];` 表示 matrix 是指针，指向 int 类型大小为10的数组

### 6.2.5 main函数：处理命令行参数

命令行参数通过两个可选的形参传递给 main 函数：

`int main(int argc, char *argv[])`

或者可以写成：

`int main(int argc, char **argv)`

- 第一个形参 argc 表示数组中字符串的数量

- 第二个形参 argv 是一个数组，它的元素是指向C风格字符串的指针，即 `argv` 指向 `char*`

其中，argv[0]保存程序名字。

### 6.2.6 含有可变形参的函数

为了能处理不同数量实参的函数，C++11 提供了两种方法：

- 如果所有实参类型相同，可以传递一个名为 `initializer_list` 的标准库类型

- 如果实参类型不同，可以编写可变参数模板（chapter 16.4）

此外，C++ 还有省略符形参，这种只用于与 C 函数交互的接口程序。

#### initializer_list 形参

如果实参数量位置，但是类型都相同，可以使用该种方法。

initializer_list 提供的操作有：

- 默认初始化，列表为空：`initializer_list<T> list;`

- 赋值初始化，列表的元素是初始值的副本，类型为const：`initializer_list<T> list{a, b, c..};`

- 拷贝或赋值对象：`list2 = list1;` 或者 `list2(list2);`，不会拷贝列表中的元素，原始列表和副本共享元素。

- 元素数量，首元素指针，尾元素下一个位置的指针：`list.size()`, `list.begin()`, 'list.end()'

initializer_list 对象中的元素永远是常量值。

```cpp
void error_msg(initializer_list<string> list)
{
    for (const auto &s : list)
        cout << s << endl;
}
```

#### 省略符形参

省略符形参是为了便于 C++ 程序访问某些特殊的 C代码 设置的。大多数 **类类型的对象** 在传递给省略符形参时都无法正确拷贝。

省略符形参只能出现在形参列表的最后一个位置：

```cpp
void foo(parm_list, ...);

void foo(...);
```

举例：

```cpp
void function(...)  //代号: 1
{
    std::cout << 1 << std::endl;
}

void function(int number, ...) //代号: 2
{
    std::cout << 2 << std::endl;
}


//function的匹配规则是: 如果第一个参数是int,或者转为int的类型就优先调用: 2, 其他情况调用: 1.
int main()
{
    int n = 10;
    function(n);  
    std::cout << "----------------" << std::endl;

    std::string str = "shihua";
    function(str.c_str());
    function("hello");

    return 0;
}
```

## 6.3 返回类型和 return 语句

### 6.3.1 无返回值函数

没有返回值的 return 语句只能用在返回类型为 void 的函数中。此外，返回类型为 void 的函数不要求一定要有 return 语句，因为这类函数的最后一句后面会隐式地执行 return。

一个返回类型是void的函数，`return expression;` 中的 expression 也必须是另一个返回 void 的函数。

### 6.3.2 有返回值函数

只要函数的返回类型不是void，则该函数内每条 return 语句必须返回一个值。

返回值类型必须与函数返回类型相同，或者可以隐式地转换成函数的返回类型。

#### 值是如何被返回的

返回一个值的方式和初始化一个变量或者形参的方式相同：返回值用于初始化调用点的一个临时量，该临时量就是函数调用的结果。

如果函数 **返回引用**，那么该引用仅仅是它所引对象的一个别名。例如：

```cpp
const string &shortString(const string &s1, const string &s2)
{
    return s1.size() < s2.size() ? s1 : s2;
}
```

此处返回的是 const string 的引用。

#### 不要返回局部对象的引用或指针

函数完成之后，局部变量的引用将不再指向有效的内存区域。

```cpp
const string &manip()
{
    string ret;
    ret = .....;

    if (!ret.empty())
        return ret;
    else
        return "EMPTY";
}
```

上面两条返回语句都将返回未定义的值，第一条语句返回局部对象的引用，第二条的字符串字面值转换成一个局部临时string对象。

#### 返回 类 的函数

如果函数返回指针，引用，或者类的对象，我们就可以使用函数调用的结果访问结果对象的成员。

例如：

```cpp
auto size = shorterString(s1, s2).size();
```

#### 引用返回左值

- 调用一个返回引用的函数得到左值

- 其他返回类型得到右值

若函数返回值是一个引用，那么他是一个左值，可以出现在赋值运算符的左侧。

例如：

```cpp
// 返回某个位置字符的引用
char &get_val(const string &s, string::size_type ix)
{
    return s[ix];
}

// 返回引用的函数可以出现在赋值运算符的左侧
int main()
{
    string s("some value");
    get_val(s, 0) = 'S';
}
```

#### 列表初始化返回值

C++11 规定，函数可以返回花括号包围的值的列表。

列表用来对表示函数返回的临时量进行初始化。如果列表为空，临时量执行值初始化。

- 如果函数返回的是内置类型，则话花括号中最多包含一个值，并且该值所占空间不应该大于目标类型的空间。

- 如果函数返回值为类类型，由类本身定义初始值如何使用。

例子：

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> err()
{
    return {"404 not found", "403 forbidded error", "502 bad gateway"};
}

int getIntNum()
{
    return {2};
}

double getDoubleNum()
{
    return {3.14};
}

int main()
{
    vector<string> errormsg = err();
    for (auto &item : errormsg) cout << item << endl;

    cout << getIntNum() << endl;
    cout << getDoubleNum() << endl;

    return 0;
}
```

#### 主函数 main 的返回值

- 之前规定如果函数的返回类型不是void，那么必须有一个返回值

- 如果函数为 main 函数，那么可以没有 return 语句。因为编译器将在结尾处插入 `return 0;`

main函数的返回值可以看做状态指示器，返回0表示执行成功，返回其他值表示执行失败。

其中 cstalib 头文件定义了两个预处理变量：

```cpp
int main()
{
    if (failure) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
```

#### 递归

一个函数调用了它本身，称该函数为递归函数(recursive function)。

main 函数不能调用自己。

### 6.3.3 函数返回数组指针

数组不能被拷贝，所以函数不能返回数组，但是函数可以返回数组的指针或者引用。

#### 直接定义

我们在定义一个指向数组的指针的时候，表述方式如下：

```cpp
int arr[10];
int (*p)[10] = &arr;
```

同理，返回数组指针的函数定义如下：

`Type (*func(params))[dimension]`

```cpp
int (*func(int i))[10];   // 函数的参数为i，返回值为指向大小为10的int数组的指针
```

逐层理解：

- `func(int i)` 表示函数参数为int类型

- `(*func(int i))` 表示函数返回结果可以解引用（是一个指针）

- `(*func(int i))[10]` 表示解引用函数返回结果得到大小为10的数组

- `int (*func(int i))[10]` 数组元素类型为 int

#### 使用类型别名

```cpp
typedef int arrT[10];   // arrT是一个类型别名，表示的类型是含有10个int的数组
//or
using arrT = int[10];

arrT *func(int i);      // 函数func 返回指向10个int数组的指针
```

#### 使用尾置返回类型(trailing return type)

C++11 新标准中可以使用尾置返回类型生命比较复杂的函数。

函数真正返回类型在形参列表之后，前边使用 auto 代替。

```cpp
auto func(int i) -> int (*)[10];
auto func(int i) -> int (&)[10];
```

#### 使用 decltype

如下所示，decltype 关键字的结果是一个数组，若要返回指针，需要在函数前加符号`*`。

```cpp
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

decltype(odd) *f(int i)
{
    return (i % 2) ? &odd : &even;
    // 返回一个指向数组的指针，若不加取地址符，则会报错：
    // error: cannot convert 'int*' to 'int (*)[5]' in return
}
```

### 练习6.36 6.37

编写一个函数声明，返回数组的引用，并且改数组包含10个string对象。

1. 直接声明

```cpp
string (&func(string (&s)[10]))[10];
```

2. 使用类型别名

```cpp
typedef string sarr[10];
using sarr = string[10];

sarr &func(sarr &s);
```

3. 使用尾置返回类型

```cpp
auto func(string (&s)[10]) -> string(&)[10];
```

4. 使用 decltype 关键字

```cpp
string arr[10];

decltype(arr) &func(decltype(arr) &s);
```

