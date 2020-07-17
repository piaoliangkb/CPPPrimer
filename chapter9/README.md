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
        - [9.2.7 关系运算符](#927-关系运算符)
            - [容器的关系运算符 使用 元素的关系运算符 进行比较](#容器的关系运算符-使用-元素的关系运算符-进行比较)
    - [9.3 顺序容器操作](#93-顺序容器操作)
        - [9.3.1 向顺序容器添加元素](#931-向顺序容器添加元素)
            - [push_back](#push_back)
            - [push_front](#push_front)
            - [容器中的特定位置添加元素](#容器中的特定位置添加元素)
            - [插入范围内元素](#插入范围内元素)
            - [insert 的返回值](#insert-的返回值)
            - [emplace 进行构造而不是拷贝元素](#emplace-进行构造而不是拷贝元素)
        - [9.3.2 访问元素](#932-访问元素)
            - [访问成员函数返回的是引用](#访问成员函数返回的是引用)
            - [使用 at 来实现下标安全操作](#使用-at-来实现下标安全操作)
            - [练习9.24 空 vector 调用 at 下标运算符 front begin](#练习924-空-vector-调用-at-下标运算符-front-begin)
        - [9.3.3 删除元素](#933-删除元素)
            - [pop_front, pop_back](#pop_front-pop_back)
            - [从容器内部删除元素](#从容器内部删除元素)
            - [删除多个元素](#删除多个元素)
        - [9.3.4 forward_list 的特殊操作](#934-forward_list-的特殊操作)
        - [9.3.5 改变容器大小](#935-改变容器大小)
        - [9.3.6 容器操作使得迭代器失效](#936-容器操作使得迭代器失效)
            - [添加元素](#添加元素)
            - [删除元素](#删除元素)
    - [9.4 vector 对象是如何增长的](#94-vector-对象是如何增长的)
        - [管理容量的成员函数](#管理容量的成员函数)
        - [capacity 和 size](#capacity-和-size)
    - [9.5 额外的 string 操作](#95-额外的-string-操作)
    - [9.6 容器适配器](#96-容器适配器)
        - [stack](#stack)
        - [queue](#queue)

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

除了 forward_list 之外，每个容器类型都有三个与大小相关的操作：

- size ：返回容器中元素的数目

- empty ：当 size 为0的时候返回 true，否则返回 false

- max_size ：返回一个大于或等于该类型容器所能容纳的最大元素数的值

### 9.2.7 关系运算符

- 相等运算符（`==`, `!=`）每个容器都支持

- 关系运算符 （`>`, `<`, `>=`, `<=`）除了无序关联容器外的所有容器都支持

比较两个容器的方法：

- 如果两个容器大小相同，对应元素一一相等，则两个容器相等。

- 如果两个容器大小不同，较小容器中每个元素都等于较大容器中的元素，则较大容器大于较小容器。

```cpp
vector<int> v1{1, 2, 3, 4};
vector<int> v2{1, 2, 3, 4, 5, 6};
v2 > v1; // true
```

- 如果两个容器都不是另一个容器的前缀子序列，则他们的比较结果取决于第一个不相等的元素比较结果。

#### 容器的关系运算符 使用 元素的关系运算符 进行比较

- 容器的相等运算符是使用元素的 == 运算符进行比较的

- 其他关系运算符是使用元素的 < 运算符进行比较的

即只有当其元素类型定义了相应的比较运算时，我们才可以使用关系运算符来比较两个容器。

## 9.3 顺序容器操作

顺序容器和关联容器的不同之处在于两者组织元素的方式。本章将介绍顺序容器所特有的操作。

### 9.3.1 向顺序容器添加元素

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7eexzwxsyj20tx0o77e7.jpg)

#### push_back

- push_back 将一个元素追加到一个容器的尾部。

- 除了 array, forward_list 之外，每个顺序容器(vector, list, deque, string)都支持 push_back.

- 对 push_back 的调用在容器尾部创建了一个新的元素，将容器的 size 增加1。该元素的值为添加参数的一个拷贝。

当我们用对象来初始化容器，或者把一个对象插入容器的时候，实际上放入到容器中的是对象的一个拷贝而不是对象本身。

#### push_front

- push_front 将元素插入到容器的头部。

- list, forward_list, deque 支持 push_front。

#### 容器中的特定位置添加元素

- vector, deque, list, string 都支持 insert 成员。

- 每个 insert 函数都接受一个迭代器作为其第一个参数，迭代器可以指向容器中的任何位置，包括容器结尾的下一个位置，所以插入位置为该指定迭代器之前。

- vector, string 不可以使用 push_front，但可以使用 `insert(v.begin(), ...)`

#### 插入范围内元素

- insert 的一个版本接受一个元素数目和一个值，将指定数量的元素添加到指定位置之前:

```cpp
v.insert(v.end(), 10, "end");
```

- 接受一对迭代器：

```cpp
v.insert(v.begin(), v.end()-2, v.end());  // 将v的最后两个元素添加到v的开头
```

如果我们传递给 insert 一对迭代器，它们不能指向添加元素的目标容器。

```cpp
// runtime error
v.insert(v.begin(), v.begin(), v.end());
```

- 接受一个初始化列表：

```cpp
v.insert(v.end(), {"this", "is", "my"});
```

#### insert 的返回值

insert 返回指向第一个新加入元素的迭代器，如果范围为空，不插入任何元素，insert 操作会将第一个参数返回。

如下代码等价于调用 push_front.

```cpp
list<string> lst;
auto iter = lst.begin();
while (cin >> word)
    iter = lst.insert(iter, word);
```

#### emplace 进行构造而不是拷贝元素

C++11 新标准引入了 `emplace_front`, `emplace`, `emplace_back`，用来构造而不是拷贝函数。

调用 emplace 成员函数时，将参数传递给元素类型的构造函数，emplace 成员使用这些参数在函数管理的内存空间中直接构造元素。

```cpp
vector<Sales_data> v;
v.push_back("100001", 2, 15.99);  // error，没有接受三个参数的构造函数
v.emplace_back("100001", 2, 15.99);  // true，使用三个参数的 Sales_data 构造函数
v.push_back(Sales_data("100001", 2, 15.99));  // true，创建一个临时的 Sales_data 对象传递给 push_back
```

emplace 会根据参数来选择相应的构造函数：

```cpp
v.emplace_back(); // 使用 Sales_data 的默认构造函数
v.emplace(iter, "100001"); // 使用只接受一个 string 的构造函数
```

### 9.3.2 访问元素

- 包括 array 在内每个顺序容器都有一个 front 成员函数，返回首元素的引用。

- 除了 forward_list 之外每个顺序容器都有一个 back 成员函数，返回尾元素的引用。

在调用 front 和 back 之前，要确保容器非空。如果容器为空，则行为是未定义的。

- 下标操作 `c[n]` 返回 c 中下标为 n 的元素的引用，n 是无符号整数。若 `n>c.size()`函数行为未定义。

- `c.at(n)` 操作返回下标为 n 的元素的引用。如果下标越界，则抛出 `out_of_range` 异常。

#### 访问成员函数返回的是引用

访问元素的成员函数（front, back, []下标运算, at）返回的都是引用。容器是 const 对象返回 const 引用，否则返回普通引用。

```cpp
auto &v = c.back();
v = 40;
```

使用 auto 需要将变量定义为引用类型。

#### 使用 at 来实现下标安全操作

编译器不会检测下标越界。

使用 at 成员函数在下标越界的时候，at 会抛出一个 `out_of_range` 异常。

```cpp
vector<string> svec;
cout << svec[0];      // runtime error
cout << svec.at(0);   // 抛出 out_of_range 异常
```

#### 练习9.24 空 vector 调用 at 下标运算符 front begin

1. at 运算符

```cpp
std::vector<int> v;
auto &i = v.at(0);
```

运行错误：

```cpp
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)
```

2. 下标运算符

```cpp
std::vector<int> v;
auto &i = v[0];
std::cout << i << std::endl;
```

运行结果：无输出

3. front

```cpp
std::vector<int> v;
auto &i = v.front();
std::cout << i << std::endl;
```

运行结果：无输出

4. begin

```cpp
std::vector<int> v;
auto i = v.begin();
std::cout << *i << std::endl;
```

运行结果：无输出

### 9.3.3 删除元素

- 删除元素的操作不适合 array，因为会改变容器大小。

- `c.pop_back()` 删除尾元素，若 c 为空，则函数行为未定义。函数返回 void。不适用 forward_list。

- `c.pop_front()`删除首元素，若 c 为空，则函数行为未定义。函数返回 void。不适用 vector，string。

- `c.erase(p)` 删除迭代器 p 指定的元素，返回被删元素之后元素的迭代器(可以是尾后迭代器 off-the-end)。若 p 是尾后迭代器，则函数行为未定义。

- `c.erase(b, e)`删除迭代器 b 和 e 所指定范围内的元素(前闭后开)，返回最后一个被删除元素之后的迭代器（返回值和 e 相等）。**若 e 为尾后迭代器，函数也返回尾后迭代器。**

- `c.clear()`删除 c 中的所有元素。函数返回 void。

- 删除元素的成员函数不会检查参数，所以删除元素之前必须确保他们是存在的。

删除 deque 中 **除首尾之外的任何元素** 都会使得所有迭代器、引用和指针失效。

指向 vecrtor 或 string 中 **删除点之后位置** 的迭代器、引用和指针失效。

#### pop_front, pop_back

`pop_front` 和 `pop_back` 成员函数分别删除首元素和尾元素。

- vector 和 string 不支持 pop_front。

- forward_list 不支持 pop_back。

#### 从容器内部删除元素

成员函数 erase 返回最后一个删除元素之后的迭代器，从一个 list 中删除所有奇数元素：

```cpp
list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto it = lst.begin();
while (it != lst.end())
{
    if (*it % 2) it = lst.erase(it);
    else ++it;
}
```

#### 删除多个元素

删除一对迭代器内的元素：

```cpp
iter1 = lst.erase(iter1, iter2);
```

执行结束之后，iter1 == iter2

删除所有元素 `lst.clear();` 或者 `list.erase(lst.begin(), lst.end());`

### 9.3.4 forward_list 的特殊操作

forward_list 是一个单向链表，进行删除操作时，发生如图所示情况：

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7gimsk0twj20qk07ogmm.jpg)

为了在单向链表中添加或删除一个元素，我们需要访问其前驱：

- 定义了名为 `insert_after`, `emplace_after`, `erase_after` 的操作。

在上图中，为了删除 elem3 ，应该在 elem2 上使用 erase_after 操作。

- 定义了 `before_begin` 用来返回首前(off-the-beginning)迭代器，用来在链表首元素之前添加删除元素。

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7grnvnr9ej20u10g1tg0.jpg)

例如，使用迭代器在一个 forward_list 删除奇数元素：

```cpp
forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto prev = flst.before_begin();
auto cur = flst.begin();
while (cur != flst.end())
{
    if (*cur % 2) cur = flst.erase_after(prev); // 删除当前节点并指向下一个
    else {
        prev = cur;
        ++cur;
    }
} 
```

### 9.3.5 改变容器大小

- 可以使用 `resize` 来改变容器大小。

- 如果当前大于所要求的大小，容器后部的元素会被删除。

- 如果当前小于所要求的大小，会添加新元素到容器后（可选参数，若无参数执行值初始化；如果是类类型必须提供默认构造函数）

```cpp
c.resize(n);     // 调整大小为 n 个元素。
c.resize(n, t);  // 调整大小为 n 个元素，对新元素初始化为 t
```

- 如果缩小容器，指向被删除元素的迭代器、引用、指针都会失效。

- vector, string, deque 进行 resize 可能导致迭代器、引用、指针失效。

### 9.3.6 容器操作使得迭代器失效

向容器中添加元素和从容器中删除元素，可能会使只想容器元素的指针、引用或迭代器失效。

#### 添加元素

- vector 和 string：如果存储空间重新分配，所有都失效；如果未重新分配，插入位置之后失效，之前有效。

- deque：如果首尾添加元素，迭代器失效，指向存在的元素的引用和指针不变；插入首尾之外其他位置，所有都失效。

- list 和 forward_list：迭代器，指针，引用都有效。

#### 删除元素

被删除的元素指针、迭代器、引用都会失效。

- vector 和 string：被删元素之前的所有都有效。尾后迭代器失效。

- deque：删除尾元素，尾后迭代器失效，其他迭代器、指针、引用不受影响；删除首元素，不受影响；删除其他位置元素，所有都失效。

- list 和 forward_list：所有都有效。

对 vector, string, deque 来说，确保每次改变容器的操作之后都重新定位迭代器。

## 9.4 vector 对象是如何增长的

- 为了支持快速随机访问，vector 将元素连续存储。

- 当不得不获取新的内存时，vector 和 string 的实现通常会分配比需求空间更大的内存空间。

### 管理容量的成员函数

- `shrink_to_fit()` ：

1. 将 `capacity()` 减小为与 `size()` 相同大小；

2. vector, string, deque 可用；

3. 通过调用 `shrink_to_fit()` 来退回 deque, vector, string 不需要的内存空间；

4. 具体实现可以选择忽略此请求，即不保证调用后一定退回内存空间；

- `capacity()` ：
  
1. 在不重新分配内存的情况下最多保存多少元素；

2. vector, string 可用

- `reserve(n)` ：

1. 分配至少能容纳 n 个元素的内存空间；

2. vector, string 可用；

3. 不改变容器中元素的数量，只影响预先分配；

4. n 小于当前容量则什么都不做，即调用 `reserve` 不会减小容器占用的内存空间；和 `resize` 对比，`resize` 不会改变容量，会改变元素数目；

### capacity 和 size

- capacity 是指不分配新的内存空间的条件下最多可以保存多少元素。

- size 是指已经保存的元素数目。

- 只有执行 insert 操作的时候 size 和 capacity 相等，或者调用 resize 和 reserve 时给定大小超过当前 capacity，vector 才重新分配内存空间。

## 9.5 额外的 string 操作

见 chapter3

## 9.6 容器适配器

标准库定义了三个顺序容器适配器：`stack`, `queue`, `priority_queue`.

- 一个容器适配器可以接受一个已有的容器类型，使该适配器的行为看起来像一种不同的类型

- 所有容器适配器都支持的操作如下：

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7svuw26fdj20uy0f9aen.jpg)

- 所有适配器都a要求容器具有添加和删除元素的能力，所以不能使用 `array`。

- 所有适配器都要求容器具有添加，删除，访问尾元素的能力，所以不能使用 `forward_list`。

适配器 | 要求操作 | 可选构造容器| 默认容器
--- | --- | --- |---
stack | push_back, pop_back, back | deque, list, vector | deque
queue | back, push_back, front, push_front | deque, list, vector | deque
priority_queue | front, push_back, pop_back, 随机访问 | vector, deque | vector

- 指定适配器的底层容器

```cpp
stack<string> stk1;
stack<string, vector<string>> stk2; // 指定底层容器为 vector
```

### stack

```cpp
stack<int> int_stack;
for (size_t i=0; i<10; ++i)
{
    int_stack.push(i);
}
while (!int_stack.empty())
{
    cout << int_stack.top() << endl;
    int_stack.pop();
}
```

栈的其他操作：

操作 | 含义
-- | --
stack.pop() | 删除栈顶元素
stack.push(item) | 将 item 压入栈顶
stack.emplace(args) | 通过 args 构造元素压入栈顶
stack.top() | 返回栈顶元素

### queue

`queue` 和 `priority_queue` 都定义在头文件 `queue` 中。

- `queue` 采用先进先出的策略，进入队列对象放到队尾，离开队列对象从队首删除。

- `priority_queue` 为队列中的元素建立优先级，新加入的元素排在所有优先级比它低的元素之前。

队列的操作：

操作 | 含义
--- | ---
q.pop() | 删除 queue 的队首元素或者 priority_queue 的最高优先级元素，返回 void
q.front() | 返回首元素
q.back() | 返回尾元素，只适用于 queue
q.top() | 返回最高优先级元素，只适用于 priority_queue
q.push(item) | 在 queue 的结尾或者 priority_queue 某个位置添加元素
q.emplace(args) | 同上，构造元素
