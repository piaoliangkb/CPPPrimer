<!-- TOC -->

- [第九章 顺序容器](#第九章-顺序容器)
    - [9.1 顺序容器概述](#91-顺序容器概述)
        - [顺序容器类型](#顺序容器类型)
            - [string 和 vector](#string-和-vector)
            - [list 和 forward_list](#list-和-forward_list)
            - [deque](#deque)
            - [array](#array)
        - [容器选择](#容器选择)
    - [9.2 容器库概览](#92-容器库概览)
        - [容器保存元素类型](#容器保存元素类型)
        - [容器操作](#容器操作)
        - [9.2.1 迭代器](#921-迭代器)
            - [迭代器范围 (iterator range)](#迭代器范围-iterator-range)
                - [左闭右合区间](#左闭右合区间)
        - [9.2.2 容器类型成员](#922-容器类型成员)
        - [9.2.3 begin 和 end 成员](#923-begin-和-end-成员)
        - [9.2.4 容器定义和初始化](#924-容器定义和初始化)
            - [将一个容器初始化为另一个容器的拷贝](#将一个容器初始化为另一个容器的拷贝)
            - [列表初始化](#列表初始化)
            - [与顺序容器大小相关的构造函数](#与顺序容器大小相关的构造函数)
            - [array 固定大小](#array-固定大小)
                - [array 类型的定义和使用](#array-类型的定义和使用)
                - [array 的构造函数](#array-的构造函数)
                - [array 的拷贝和赋值操作](#array-的拷贝和赋值操作)
        - [9.2.5 赋值和 swap](#925-赋值和-swap)
            - [赋值运算符](#赋值运算符)
            - [assign(顺序容器中)](#assign顺序容器中)
            - [swap 操作](#swap-操作)
        - [9.2.6 容器大小操作](#926-容器大小操作)

<!-- /TOC -->


# 第九章 顺序容器

- 顺序容器(sequential container)：顺序容器中的元素是按照它们在容器中的位置来顺序保存和访问的，例如：`array`, `vector`, `list`, `forward_list`, `deque`, `string`

- 关联容器(associative-container)：关联容器中的元素是按照关键字来保存和访问的，例如：`map`, `set`, `multimap`, `multiset`

## 9.1 顺序容器概述

所有顺序容器都提供了快速顺序访问元素的能力，在下面两个方面有性能的折衷：

- 向容器中添加元素或者删除元素

- 非顺序地访问容器中的元素

### 顺序容器类型

容器类型 | 介绍（数据结构；元素访问方式；插入删除速度）
--- | ---
vector | 可变大小数组；快速随机访问；尾部之外位置插入删除很慢
deque | 双端队列；快速随机访问；头尾位置插入删除很快
list | 双向链表；只支持双向顺序访问；任何位置插入删除都很快
forward_list | 单向链表；只支持单向顺序访问；任何位置插入删除都很快
array | 固定大小数组；快速随机访问；不能添加或删除元素
string | 保存字符，与 vector 类似；快速随机访问；尾部插入删除速度快

#### string 和 vector

- 元素保存在连续的内存空间内，由下标计算地址很快。

- 在中间位置插入或删除元素，需要移动被操作位置之后的所有元素，很耗时。

#### list 和 forward_list 

- 容器的任何位置添加和删除元素都很快。

= 不支持元素的随机访问，为了访问某一个元素，必须从头或者结尾遍历整个容器。

- 和 vector string array 比，额外内存开销大。

- forward_list 是新 C++ 标准增加的类型。

- forward_list 没有 size 操作。

#### deque

- 支持快速随机访问。

- 在中间位置添加或删除元素开销很大，在头尾添加或删除元素很快。

#### array

- array 是新 C++ 标准增加的类型。

- array 对象的大小是固定的，所以不支持添加或者删除元素和其他改变容器大小的操作。

### 容器选择

1. 通常情况下，选择 vector。

2. 程序有很多小的元素，且空间开销重要，不要选择 list 和 forward_list。

3. 对元素随机访问，使用 vector 或者 deque。

4. 需要在中间插入或者删除元素，使用 list 或者 forward_list。

5. 在头尾插入或者删除元素而不会在中间插入删除，选择 deque。

6. 中间位置添加元素的两种处理办法：

- 向 vector 追加数据，然后使用 sort 方法。

- 输入阶段使用 list，输入完成拷贝到 vector。

如果不确定使用什么容器，尽量使用 vector 和 list 的公共操作：使用 iterator 而不是下标操作来避免随机访问。

## 9.2 容器库概览

本节介绍所有容器都适用的操作。

### 容器保存元素类型

顺序容器几乎可以保存任何元素类型。

```c
vector<vector<string>> lines;
vector<vector<string> > lines;  // 较旧的编译器可能需要在两个尖括号之间加上一个空格
```

然而，某些容器操作对元素类型有其自己的特殊要求。若某些类没有默认构造函数，则初始化时候不能只提供一个元素数目参数：

```cpp
vector<noDefault> v1(10, init);  // init 是 noDefault 类的初始化器
vector<noDefault> v2(10);        // 错误
```

### 容器操作

见P295

### 9.2.1 迭代器

P96 列出了迭代器支持的所有操作：

| 运算符                          | 含义                                                                                             |
| ------------------------------- | ------------------------------------------------------------------------------------------------ |
| *iter                           | 返回迭代器iter所指元素的引用                                                                     |
| iter->name                      | 解引用iter并获取该元素名为name的成员，等价于(*iter).name                                         |
| ++iter                          | 令iter指向容器中的下一个元素                                                                     |
| --iter                          | 令iter指向容器中的上一个元素                                                                     |
| iter1 == iter2 / iter1 != iter2 | 判断两个迭代器是否相等，如果两个迭代器指示的是同一个元素或者同一个容器的尾后迭代器，那么他们相等 |

特别注意：forward_list 迭代器不支持递减运算符。

P99 列出了迭代器支持的算术运算，只能应用于 string, vector, deque, array 的迭代器。

| 运算符        | 含义                                                                                                  |
| ------------- | ----------------------------------------------------------------------------------------------------- |
| iter + n      | 迭代器指示的新位置比原来的位置向前移动n个元素，结果为指向容器内的一个元素或者容器结尾元素的下一个位置 |
| iter - n      | 同上                                                                                                  |
| iter += n     | 将iter+n的结果赋给iter                                                                                |
| iter -= n     | 将iter-n的记过赋给iter                                                                                |
| iter1 - iter2 | 同一个容器中两个迭代器之间的距离                                                                      |
| \>, >=, <, <= | 指向同一个容器中迭代器前后位置的比较                                                                  |

#### 迭代器范围 (iterator range)

一个迭代器范围由一对迭代器表示，分别指向同一个容器中的元素或者尾元素之后的位置(one past the last element)。

即构成迭代器范围的两个迭代器的要求是：

- 指向同一个容器中的元素

- 可以通过反复递增 begin 来到达 end

##### 左闭右合区间

包含一个容器中所有元素的迭代器范围是 [begin, end) ，这种也被称为左闭合区间(left-inclusive interval)。

三种方便的性质：

- 如果 begin == end ，则范围为空

- 如果 begin != end ，则范围至少包含一个元素，且 begin 指向第一个

- 可以对 begin 递增若干次来到达 end

### 9.2.2 容器类型成员

每个容器都定义了多个类型：size_type, iterator, const_iterator。除了已经使用过的迭代器类型，大多数容器还提供反向迭代器。

类型别名：通过类型别名，可以在不了解容器中元素类型的情况下使用它。（泛型编程中使用）。


使用时需要显式的指示其类名：

```cpp
list<string>::iterator iter;
vector<int>::difference_type count;
```

### 9.2.3 begin 和 end 成员

- begin：生成指向容器中第一个元素的迭代器

- end：生成指向容器中尾元素之后位置的迭代器

多个版本：

- r 开头的版本返回 反向迭代器

- c 开头的版本返回 const 迭代器

- 不以 c 开头的版本都是被重载过的，即有两个名为 begin 的成员，一个是 const 成员，返回 const_iterator；另一个是非 const 成员，返回 iterator。

对于非 const 成员来说，显式的指定 iterator：

```cpp
list<string>::const_reverse_iterator it = a.rbegin();
```

### 9.2.4 容器定义和初始化

每个容器都定义了一个默认构造函数，除 array 之外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素初始值的参数。

参考 P299

#### 将一个容器初始化为另一个容器的拷贝

有两种拷贝方法：

- 直接拷贝整个容器，要求两个容器类型和元素类型必须匹配。

- 拷贝由一个迭代器对指定的元素范围(array 除外)，不要求容器类型相同，元素类型也可以不同，只要可以转换

```cpp
list<string> authors = {"millon", "shakes", "auston"};
vector<const char*> articles = {"a", "aaa", "ttt"};

list<string> lst1(authors); // 类型匹配的拷贝

list<const char*> lst(articles.begin(), articles.end());  // 使用迭代器范围来拷贝
auto it = lst.rbegin();
cout << *it << endl; // output is ttt
```

#### 列表初始化

C++11 新标准中，我们可以对容器进行列表初始化：

对于 array 之外的容器，列表初始化还隐含地制定了容器的大小。

```cpp
list<string> lst = {"123", "456", "789"};
```

对于 array 容器来说，列表初始化可以指定全部或者部分值：

```cpp
array<int, 10> arr = {1, 2, 3, 5, 6};
```

#### 与顺序容器大小相关的构造函数

只有顺序容器的构造函数才接受大小参数，关联容器并不支持。

```cpp
vector<int> ivec(10, -1);  // 10个 int ，每个初始化 -1
list<string> lst(10, "hi");  // 10个 string ，每个初始化为 "hi"
forward_list<int> ivec(10);  // 10个 int ，每个初始化为 0
deque<string> svec(10);      // 10个 string ，每个都为空
```

- 如果元素是内置类型或者是具有默认构造函数的类类型，可以只为构造函数提供一个容器大小参数。

- 如果元素类型没有默认构造函数，除了大小参数必须指定一个显式的元素初始值。

#### array 固定大小

##### array 类型的定义和使用

标准库 array 的大小也是类型的一部分，定义时候需要指定：

```cpp
array<int, 42> arr1;
array<string, 10> arr2;
```

为了使用 array 类型，必须同时指定元素类型和大小：

```cpp
array<int, 42>::size_type i;
```

##### array 的构造函数

一个默认构造的 array 是非空的：包含了与其大小一样多的元素，这些元素都被默认初始化。

```cpp
array<int, 10> arr1; // all is 0
array<int, 10> arr2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
array<int, 10> arr3 = {42}; // arr3[0] = 42; else = 0;
```

和内置数组的对比：

```cpp
int a[10]; // 未被定义，例如：4200860 0 4667744 0 1512272 0 1 0 -1 -1
int a[10] = {1, 2, 3}; // else is 0
```

##### array 的拷贝和赋值操作

我们不能对内置数组进行拷贝和赋值操作，但是可以在 array 上进行如此操作。

```cpp
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int cpy[10] = a; // error

array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
array<int, 10> copy = arr1; // true
```

### 9.2.5 赋值和 swap

#### 赋值运算符

与赋值相关的运算符可以作用于所有容器。

```cpp
c1 = c2;
c1 = {a, b, c};
```

如果赋值符号左右两边的容器大小不同，赋值运算后两者大小都与右边容器的大小相同。

与内置数组不同，标准库 array 允许赋值，赋值符号左右两边的运算对象必须具有相同的类型：

```cpp
array<int, 10> a1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
array<int, 10> a2 = {0};
a1 = a2;  // 合理
a2 = {0}; // 不合理，不能将一个花括号列表赋予数组
```

#### assign(顺序容器中)

赋值运算符要求左边和右边的运算对象具有相同的类型。而顺序容器的 assign 成员，允许我们从一个不同但是相容的类型赋值，或者从容器的一个子序列赋值。

`assign` 成员的三种形式：

```cpp
seq.assign(begin, end); // begin 和 end 两个迭代器，迭代器不能指向 seq 中的元素

seq.assign({...}); // 列表初始化表达式

seq.assigh((n, t)); // 替换成 n 个值为 t 的元素
```

```cpp
list<string> authors = {"millon", "shakes", "auston"};
vector<const char*> articles = {"a", "aaa", "ttt"};

authors.assign(articles.begin(), articles.end());
authors.assign({"111", "222", "333", "444"});
authors.assign(10, "hi");
```

#### swap 操作

swap 交换两个相同类型容器的内容，例如：

```cpp
vector<string> svec1(10);
vector<string> svec2(24);
swap(svec1, svec2);
```

**耗时：**

- 除了 array 之外，交换两个容器内容的操作很快：只交换容器内部的数据结构，元素本身没有被交换（常数时间内完成）。

- swap 两个 array 会交换他们的元素，耗时与 array 中元素的数目成正比。

**指针，引用，迭代器绑定元素：**

- 由于元素不会被移动，（string除外），所以指向容器的迭代器，指针，引用在 swap 操作之后都不会失效。但是元素已经处于不同的容器里边了。

- 对一个 string 调用 swap 之后，迭代器，指针，引用会失败。

- array swap 之后，指针，引用，迭代器绑定的元素保持不变，但是元素的值已经与另一个 array 中对应元素的值进行了交换。

vector 容器 swap 之后仍然指向 swap 操作之前的元素：

```cpp
vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {99, 98, 97, 96};
int* p1 = &v1[2];
int& p2 = v2[1];
vector<int>::iterator it1 = v1.begin();
cout << *p1 << endl;
cout << p2 << endl;
cout << *it1 << endl;

swap(v1, v2);

cout << *p1 << endl;
cout << p2 << endl;
cout << *it1 << endl;
// output is 3 98 1 3 98 1
```

string 容器 swap 之后会导致迭代器，引用，指针失效（？）：

```cpp
string s1 = "hello, world";
string s2 = "please find me";
char* c1 = &s1[2];
char& c2 = s2[5];
string::iterator it2 = s1.begin();
cout << *c1 << endl;
cout << c2 << endl;
cout << *it2 << endl;

swap(s1, s2);

cout << *c1 << endl;
cout << c2 << endl;
cout << *it2 << endl;
// output is l e h l e h 
// 未表明失效
```

array swap 之后，指针、引用、迭代器所绑定的元素保持不变，但是元素值已经交换：

```cpp
array<int, 3> arr1 = {1, 2, 3};
array<int, 3> arr2 = {100, 99, 98};
int* p1 = &arr1[0];
int& p2 = arr2[0];
array<int, 3>::const_iterator it1 = arr1.begin();
++it1;
cout << *p1 << endl;
cout << p2 << endl;
cout << *it1 << endl;

swap(arr1, arr2);
cout << *p1 << endl;
cout << p2 << endl;
cout << *it1 << endl;
// output is 1 100 2 100 1 99
```

统一使用非成员版本的 swap 是一个 good habit。

### 9.2.6 容器大小操作
