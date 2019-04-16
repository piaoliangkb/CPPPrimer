<!-- TOC -->

- [第三章 字符串，向量，数组](#第三章-字符串向量数组)
    - [3.1 使用using声明命名空间](#31-使用using声明命名空间)
    - [3.2 标准库类型string](#32-标准库类型string)
        - [3.2.1 定义和初始化string对象](#321-定义和初始化string对象)
        - [3.2.2 string对象的操作](#322-string对象的操作)
            - [读写string对象](#读写string对象)
            - [读取位置数量的string对象](#读取位置数量的string对象)
            - [使用getline读取一整行](#使用getline读取一整行)
            - [empty()和size()](#empty和size)
            - [string::size_type 类型](#stringsize_type-类型)
            - [比较string对象](#比较string对象)
            - [string对象和字面值相加](#string对象和字面值相加)
        - [3.2.3 处理string对象中的字符](#323-处理string对象中的字符)
            - [使用for语句打印每个字符](#使用for语句打印每个字符)
            - [使用for语句修改每个字符](#使用for语句修改每个字符)
            - [使用下标执行迭代](#使用下标执行迭代)
    - [3.3 vector](#33-vector)
        - [3.3.1 定义和初始化vector对象](#331-定义和初始化vector对象)
            - [列表初始化vector对象](#列表初始化vector对象)
            - [创建指定数量的元素](#创建指定数量的元素)
            - [值初始化](#值初始化)
            - [初始化的圆括号和花括号](#初始化的圆括号和花括号)
        - [3.3.2 向vector对象添加元素](#332-向vector对象添加元素)
        - [3.3.3 其他vector操作](#333-其他vector操作)
            - [使用for语句处理vector对象的所有元素](#使用for语句处理vector对象的所有元素)
            - [vector.size()](#vectorsize)
            - [vector对象的索引](#vector对象的索引)
    - [3.4 迭代器](#34-迭代器)
        - [3.4.1 使用迭代器](#341-使用迭代器)
            - [迭代器运算符](#迭代器运算符)
            - [迭代器类型](#迭代器类型)
            - [begin和end运算符](#begin和end运算符)
            - [解引用和成员访问操作](#解引用和成员访问操作)
        - [3.4.2 string和vector迭代器运算](#342-string和vector迭代器运算)

<!-- /TOC -->

# 第三章 字符串，向量，数组

## 3.1 使用using声明命名空间

例如：

```cpp
#include <iostream>

using std::cin;
using std::endl;

int main()
{
    int a, b;
    cin >> a >> b;
    std::cout << a+b << endl;

    return 0;
}
```

- 头文件不应包含using声明：头文件会被拷贝到所有引用他的文件中

## 3.2 标准库类型string

### 3.2.1 定义和初始化string对象

写法 | 解释 
--- | --- 
string s1 | 默认初始化，s1是一个空串
string s2(s1) | s2是s1的副本 
string s2 = s1 | 等价于s2(s1)，s2是s1的副本
string s3("value") | s3是字面值"value"的副本，除了字面值最后的空字符
string s3 = "value" | 等价于s3("value")
string s4(10, 'c') | s4的内容是"cccccccccc"
string s5 = string(10, 'c') | 拷贝初始化

- 如果使用等号执行的是**拷贝初始化**，否则为**直接初始化**

### 3.2.2 string对象的操作

操作 | 解释
--- | ---
os<<s | 将字符串s写到输出流os中，返回os
is>>s | 从is中读取的字符串赋给s，字符串以空白分割，返回is
getline(is, s) | 从is中读取一行赋给s，返回is
s.empty() | s为空则返回true
s.size() | 返回s中字符的个数
s[n] | 返回s中第n个字符的**引用**
s1+s2 | 返回s1和s2连接后的结果
s1=s2 | 用s2的副本代替s1中原来的字符
s1==s2, s1!=s2 | 比较两个字符串所含字符是否完全相等
<, >, <=, >= | 利用字符在字典中的顺序进行比较

#### 读写string对象

在执行读取操作时候，string对象会自动忽略开头的空白(空格，换行，制表)，从第一个真正的字符读取到下一个空白为止。

#### 读取位置数量的string对象

```cpp
while (cin >> s) // 反复读取，直到文件末尾
    cout << s << endl;
```

#### 使用getline读取一整行

如果想在字符串中保留输入时候的空白符，应该用`getline()`函数替代`>>`.

`getline(istream &is, string s)`

函数从输入流中读取内容，直到遇到换行符，换行符也被读取，但是s中不保存换行符。

getline会返回流参数，所以getline函数可以作为判断的条件。

```cpp
while (getline(cin, s)) // 每次从输入中读取一行并打印，直到遇到EOF
    cout << s << endl;
```

#### empty()和size()

- empty返回bool
- size返回string对象的长度

#### string::size_type 类型

`string.size()`的返回类型是string::size_type，不返回int或者unsigned体现了**标准库类型与机器无关的特性**。

size_type是一个无符号类型的值，允许编译器通过auto或者decltype来推断变量的类型：

```cpp
auto len = line.size();
decltype(line.size()) len;
```

注：假如n是一个负值int，那么表达式` s.size()<n `的判断结果一定是true。因为负值会自动的转换成一个比较大的无符号值。

#### 比较string对象

- 如果两个string长度不同，较短的string每个字符都和较长的string相同，就说短的小于长的。
- 如果两个string在某个位置上不一致，那么string对象的比较结果就是string对象中第一对相异字符比较的结果。

#### string对象和字面值相加

确保每个加法运算符的两侧的运算对象至少有一个是string

```cpp
string s1 = "hello";
string s2 = s1 + " world!";
```

C++中字符串字面值不是string类型的对象。是const char*

### 3.2.3 处理string对象中的字符

改变某个字符的特性，可以使用cctype头文件中定义的标准库函数。

函数 | 功能
--- | ---
isalbum(c) | 当c为字母或数字
isalpha(c) | 当c为字母
iscntrl(c) | 当c是控制字符
isdigit(c) | 当c为数字
isgraph(c) | 当c不是空格但是可以打印
islower(c) / isupper(c) | 当c为小写字母 / 大写字母
isprint(c) | 当c是可打印字符（是空格或者具有可视形式）
ispunct(c) | 当c是标点符号
isspace(c) | 当c是空白时
isxdigit(c) | 当c是十六进制数字时
tolower(c) / toupper(c) | 转为小写 / 大写字母

#### 使用for语句打印每个字符

```cpp
string str("something");
for (auto c : str)
{
    cout << c << endl;
}
```

#### 使用for语句修改每个字符

```cpp
string str("something");
for (auto &c : str)       // 注意，这里c是引用
{
    c = toupper(c);
}
cout << std << endl;
```

#### 使用下标执行迭代

```cpp
// 程序的目标是把第一个单词全部换为大写
s = "hello world!"
for (decltype(s.zize()) index = 0; index != s.size() && !isspace(s[index]); ++index)
{
    s[index] = toupper(s[index]);
}
```

## 3.3 vector

标准库类型`vector`表示对象的集合，要想使用vector，必须包含头文件：

```cpp
#include <vector>
using std::vector;
```

vector是一个**类模板**，编译器根据模板创建类或函数的过程称为实例化，当使用模板时，需要指出编译器应把类或函数实例化成何种类型：

以vector为例

```cpp
vector<int> ivec;                // ivec保存int类型的对象
vector<vector<string>> file;     // file保存vector<string>类型的对象
```

vector能容纳绝大多数对象作为其元素，因为引用不是对象，所以不存在包含引用的vector。

### 3.3.1 定义和初始化vector对象

初始化vector对象的方法：

方法 | 简介
--- | ---
vector<T> v1 | v1是一个空vector，元素为类型T，执行默认初始化
vector<T> v2(v1) | v2中包含有v1所有元素的副本
vector<T> v2 = v1 | 等价于v2(v1)
vector<T> v3(n, val) | v3包含了n个重复的元素，每个元素的值都为val
vector<T> v4(n) | v4包含了n个执行了值初始化的对象，经过测试值为0
vector<T> v5{a, b, c, ...} | v5包含了初始值个数的元素，并赋初值
vector<T> v5 = {a, b, c, ...} | 同上

`v4(n)`test:

```cpp
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v(10);
    for (int i=0;i<10;++i)
        cout << v[i] << " ";
    return 0;
}
// output is : 0 0 0 0 0 0 0 0 0 0 
```

#### 列表初始化vector对象

使用花括号：

```cpp
vector<string> articles = {"a", "an", "the"};
// or
vector<string> articles{"a", "an", "the"};
```

#### 创建指定数量的元素

```cpp
vector<int> ivec(10, -1);
vector<string> s(10, "hi!");
```

#### 值初始化

可以只提供vector对象容纳的元素数量而略去其初始值。此时库会创建一个**值初始化的**元素初值，并把他赋给容器中的所有元素。

例如：

int -> 0, string -> ""

- 有些类明确的要求必须提供初始值，只提供元素的数量不提供初始值无法完成初始化。
- 如果只提供了元素的数量没有提供元素的值，则只能使用直接初始化。即不能用`=`，因为等号为拷贝初始化。

例如：

```cpp
vector<int> ivec(10);       // 10个元素，每个元素的值都为0
vector<string> svec(10);    // 10个元素，每个元素都为空string对象

vector<int> i1 = 10;        // 不合法
```

#### 初始化的圆括号和花括号

在某些情况下，初始化的真实含义依赖于传递初始值时用的是花括号还是圆括号。

- 圆括号，提供的值是用来构造(construct) vector对象

- 花括号，提供的值是用来列表初始化(list initializa)vector对象

```cpp
vector<int> v1(10);          // v1有10个元素，值都为0
vector<int> v2{10};          // v2有1个元素，该元素的值是10

vector<int> v3(10, 1);       // v3有10个元素，每个元素的值都是1
vector<int> v4{10, 1};       // v4有2个值，分别为10, 1
```

如果在初始化的时候使用了花括号的形式，但是提供的值不能用来列表初始化，那么就要考虑构造vector对象。

```cpp
vector<string> v7{10};       // v7有10个默认初始化的string对象的元素
vector<string> v8{10, "hi"}; // v8有10个"hi"
```

若想列表初始化vector对象，花括号里边的值必须与元素类型相同。

### 3.3.2 向vector对象添加元素 

使用`push_back`成员函数，把一个值push到vecror对象的back。

注：范围for循环语句体内不应该改变所遍历序列的大小，因为范围for循环预存了vector.end()的值，改变序列大小会导致end()失效。

### 3.3.3 其他vector操作

操作 | 解释
--- | ---
v.empty() | v为空则返回true
v.size() | 返回v中字符的个数
v.push_back(t) | 向v的尾端添加元素t
v[n] | 返回v中第n个位置上元素的**引用**
v1=v2 | 用v2中元素的拷贝代替v1中的元素
v1={a, b, c, ...} | 用列表中元素的拷贝代替v1中的元素
v1==v2, v1!=v2 | 比较两个vector是否完全相同
<, >, <=, >= | 以字典中的顺序进行比较

#### 使用for语句处理vector对象的所有元素

```cpp
vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
for (auto &i : v)
{
    i *= 2;
}
for (auto i : v)
{
    cout << i << " ";
}
```

#### vector.size()

```cpp
vector::size_type        // 错误
vector<int>::size_type   // 正确
```

#### vector对象的索引

vector对象的索引也是size_type类型。不能用下标的形式添加元素

## 3.4 迭代器

所有标准库容器都可以使用迭代器，但是只有少数几种才同时支持下标运算符和迭代器。例如`vector`和`string`。

### 3.4.1 使用迭代器

有迭代器的类型都拥有名为`begin`和`end`的成员，其中`begin`成员负责返回指向第一个元素的迭代器。

```cpp
auto b = v.begin(), e = v.end();
```

`end`成员负责返回指向**尾元素的下一个位置**的迭代器，end成员返回的迭代器通常被称为**尾后迭代器(off-the-end iterator)**或者被简称为**尾迭代器(end iterator)**。

如果容器为空，那么begin和end返回的是同一个尾后迭代器。

#### 迭代器运算符

运算符 | 含义
--- | ---
*iter | 返回迭代器iter所指元素的引用
iter->name | 解引用iter并获取该元素名为name的成员，等价于(*iter).name
++iter | 令iter指向容器中的下一个元素
--iter | 令iter指向容器中的上一个元素
iter1 == iter2 / iter1 != iter2 | 判断两个迭代器是否相等，如果两个迭代器指示的是同一个元素或者同一个容器的尾后迭代器，那么他们相等

例：把一个string对象的第一个字符改为大写形式：

```cpp
string s("this is my string");
if (s.begin() != s.end())      // 确保s非空
{
    auto it = s.begin();
    *it = toupper(*it);
}
```

例：把一个string对象的第一个单词改为大写形式

```cpp
string s("this is my string");
for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
{
    *it = toupper(*it);
}
```

迭代器建议使用`!=`而不是`<`的原因是：所有标准库容器都定义了==和!=，而他们中的大多数都没定义<.

#### 迭代器类型

使用`iterator`和`const_iterator`来表示迭代器的类型

```cpp
vector<int>::iterator it;     // it可以读写vector<int>类型的元素
string::iterator it2;         // it2可以读写string对象中的字符

vector<int>::const_iterator it3;    // it3只能读元素，不能写
string::const_iterator it4;         // it4只能读字符，不能写
```

如果vector和string对象是一个常量，那么迭代器类型只能使用`const_iterator`，如果vector和string对象不是常量，那么既可以使用`const_iterator`也可以使用`iterator`.

#### begin和end运算符

begin和end运算符返回的具体类型由对象是否是常量来决定，如果对象是常量则返回`const_iterator`

```cpp
vector<int> v;
const vector<int> cv;

auto it1 = v.begin();    // it1的类型是vector<int>::iterator
auto it2 = cv.begin();   // it2的类型是vector<int>::const_iterator
```

如果对象只需要读操作而不需要写操作的话，最好使用常量类型，C++11标准引入了两个新函数`vbegin()`和`vend()`。

```cpp
auto it3 = v.cbegin();   // it3的类型是vector<int>::const_iterator
```

#### 解引用和成员访问操作

```
(*it).empty()；   // 解引用it，然后调用结果对象的empty成员
*it.empty()；     // 错误，试图访问it的empty成员
```

由上可见，解引用然后访问成员的时候，圆括号不可缺少。为了简化上述表达式，C++定义了**箭头运算符 ->**，使得`(*it).mem`和`it->mem`所要表达的含义相同。

### 3.4.2 string和vector迭代器运算

string和vector的迭代器提供了额外的运算符(iterator arithmetic)

运算符 | 含义
--- | ---
iter + n | 迭代器指示的新位置比原来的位置向前移动n个元素，结果为指向容器内的一个元素或者容器结尾元素的下一个位置
iter - n | 同上
iter += n | 将iter+n的结果赋给iter
iter -= n | 将iter-n的记过赋给iter
iter1 - iter2 | 同一个容器中两个迭代器之间的距离
>, >=, <, <= | 指向同一个容器中迭代器前后位置的比较

只要两个迭代器指向的是同一个容器中的元素或者尾元素的下一个位置，就能将他们相减，结果的类型名是`difference_type`，是一个有符号整数。