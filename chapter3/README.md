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
        - [3.2.4 补充](#324-补充)
            - [string.find()方法](#stringfind方法)
            - [chapter 9.5 额外的 string 操作](#chapter-95-额外的-string-操作)
                - [9.5.1 构造 string](#951-构造-string)
                - [9.5.2 改变 string 的其他方法](#952-改变-string-的其他方法)
                - [9.5.3 string 搜索](#953-string-搜索)
                    - [指定搜索位置](#指定搜索位置)
                    - [compare 函数](#compare-函数)
                - [9.5.5 数值和 string 转换](#955-数值和-string-转换)
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
        - [3.3.4 补充](#334-补充)
            - [vector.back()](#vectorback)
    - [3.4 迭代器](#34-迭代器)
        - [3.4.1 使用迭代器](#341-使用迭代器)
            - [迭代器运算符](#迭代器运算符)
            - [迭代器类型](#迭代器类型)
            - [begin和end运算符](#begin和end运算符)
            - [解引用和成员访问操作](#解引用和成员访问操作)
        - [3.4.2 string和vector迭代器运算](#342-string和vector迭代器运算)
    - [3.5 数组](#35-数组)
        - [3.5.1 定义和初始化内置数组](#351-定义和初始化内置数组)
            - [显式初始化数组元素](#显式初始化数组元素)
            - [不允许拷贝和赋值](#不允许拷贝和赋值)
            - [复杂的数组声明](#复杂的数组声明)
            - [访问数组元素](#访问数组元素)
        - [3.5.3 指针和数组](#353-指针和数组)
            - [指针也是迭代器](#指针也是迭代器)
            - [使用begin和end函数操作数组](#使用begin和end函数操作数组)
            - [指针运算](#指针运算)
            - [解引用和指针运算](#解引用和指针运算)
            - [下标运算](#下标运算)
        - [3.5.4 C风格字符串](#354-c风格字符串)
            - [C标准库string函数](#c标准库string函数)
            - [比较字符串，C风格和C++风格的](#比较字符串c风格和c风格的)
            - [连接字符串](#连接字符串)
        - [混用C风格和C++风格字符串](#混用c风格和c风格字符串)
            - [使用数组初始化vector对象](#使用数组初始化vector对象)
    - [3.6 多维数组](#36-多维数组)
        - [多维数组的初始化](#多维数组的初始化)
            - [使用for循环遍历多维数组（注意引用）](#使用for循环遍历多维数组注意引用)
            - [定义指向多维数组的指针](#定义指向多维数组的指针)
            - [使用auto和decltype来遍历多维数组](#使用auto和decltype来遍历多维数组)
            - [使用类型别名简化多维数组的指针](#使用类型别名简化多维数组的指针)
            - [习题3.43, 3.44, 3.45中多维数组的几种遍历方法](#习题343-344-345中多维数组的几种遍历方法)

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

| 写法                        | 解释                                            |
| --------------------------- | ----------------------------------------------- |
| string s1                   | 默认初始化，s1是一个空串                        |
| string s2(s1)               | s2是s1的副本                                    |
| string s2 = s1              | 等价于s2(s1)，s2是s1的副本                      |
| string s3("value")          | s3是字面值"value"的副本，除了字面值最后的空字符 |
| string s3 = "value"         | 等价于s3("value")                               |
| string s4(10, 'c')          | s4的内容是"cccccccccc"                          |
| string s5 = string(10, 'c') | 拷贝初始化                                      |

- 如果使用等号执行的是**拷贝初始化**，否则为**直接初始化**

### 3.2.2 string对象的操作

| 操作           | 解释                                              |
| -------------- | ------------------------------------------------- |
| os<<s          | 将字符串s写到输出流os中，返回os                   |
| is>>s          | 从is中读取的字符串赋给s，字符串以空白分割，返回is |
| getline(is, s) | 从is中读取一行赋给s，返回is                       |
| s.empty()      | s为空则返回true                                   |
| s.size()       | 返回s中字符的个数                                 |
| s[n]           | 返回s中第n个字符的**引用**                        |
| s1+s2          | 返回s1和s2连接后的结果                            |
| s1=s2          | 用s2的副本代替s1中原来的字符                      |
| s1==s2, s1!=s2 | 比较两个字符串所含字符是否完全相等                |
| <, >, <=, >=   | 利用字符在字典中的顺序进行比较                    |

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

| 函数                    | 功能                                      |
| ----------------------- | ----------------------------------------- |
| isalbum(c)              | 当c为字母或数字                           |
| isalpha(c)              | 当c为字母                                 |
| iscntrl(c)              | 当c是控制字符                             |
| isdigit(c)              | 当c为数字                                 |
| isgraph(c)              | 当c不是空格但是可以打印                   |
| islower(c) / isupper(c) | 当c为小写字母 / 大写字母                  |
| isprint(c)              | 当c是可打印字符（是空格或者具有可视形式） |
| ispunct(c)              | 当c是标点符号                             |
| isspace(c)              | 当c是空白时                               |
| isxdigit(c)             | 当c是十六进制数字时                       |
| tolower(c) / toupper(c) | 转为小写 / 大写字母                       |

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

### 3.2.4 补充

#### string.find()方法

从一个字符串中查询是否存在某个字符串，返回初始位置类型为`std::size_t`，否则返回结尾位置`std::string::npos`.

![](https://ws1.sinaimg.cn/large/7e197809ly1g34brby7ijj20pd072gm6.jpg)

> leetcode 771

```cpp
string s = "aabbccd";
string j = "ab";
string k = "f";

auto pos = s.find(j);
cout << pos << endl;

auto pos1 = s.find(k);
if (pos1 != s.npos) cout << pos1 << endl;
else cout << "not found" << endl;
```

#### chapter 9.5 额外的 string 操作

##### 9.5.1 构造 string

- `string s(cp, n)` 拷贝数组 cp 的前 n 个字节 **（cp 是数组 const char\* 类型）**

```cpp
const char* cp = "this is my world!";
string cp1(cp, 7);
cout << cp1 << endl; // res is 'this is'

char notnull[] = {'h', 'e', 'r', 'o'};
string s1(notnull, 4);
cout << s1 << endl;  // res is 'hero'
```

- `string s(s1, pos)` s 是 string s1 从下标 pos 开始的拷贝 **（s1 是 string）**

若 `pos > s1.size()` 则该构造函数行为未定义

```cpp
string s1 = "this is my whole world!";
string s(s1, 7);
cout << s << endl;  // res is ` my whole world!`
```

- `string s(s1, pos, len)` s 是 string s1 从下标 pos 开始长度为 len 个字符的拷贝

若 `pos > s1.size()` 则该构造函数行为未定义；

最多拷贝到结尾

```cpp
string s1 = "this is my whole world!";
string s(s1, 8, 2);
cout << s << endl;   // res is 'my'

string s2(s1, 8, 100);
cout << s2 << endl;  // res is 'my whole world!'
```

总结：

1. 从 `const char*` 创建 string：

拷贝前 n 个字符。

指针指向的数组必须以空字符结尾，拷贝操作遇到空字符停止。

如果传递给构造函数计数值，则不必异空字符结尾。

未定义的行为：未传递计数值且数组未以空字符结尾 或 给定计数值大于数组大小。

2. 从 string 拷贝字符：

提供开始位置和位置之后拷贝的长度。

out_of_range 异常：传递的位置大于 size。

最多拷贝到结尾。

- `substr(pos, n)`：返回一个 string，包含 s 中从 pos 开始长度为 n 个字符的拷贝。pos默认为0，n默认为 size-pos。即默认拷贝整个字符串。

```cpp
string s("yyfyyf.taobao.com");
string s2 = s.substr(0, 6);    // yyfyyf
string s3 = s.substr(7);       // taobao.com
```

##### 9.5.2 改变 string 的其他方法

string 支持顺序容器的 **赋值运算符** 和 `assign`, `insert`, `erase`操作。

- 此外，还定义了额外的 **支持下标** 的 `insert` 和 `erase` 版本。

```cpp
s.insert(s.size(), 5, '!');  // 在结尾插入5个'!'
s.erase(s.size()-5, 5);      // 删除结尾5个字符

string s1 = "hello", s2 = "world";
s2.insert(0, s1);  // s2 = "helloworld"
s1.insert(0, s2, 0, s2.size());  // 在 s1 的开头位置插入 s2 从 0 到 s2.size() 的内容
// s1 = 'helloworldhello'
```

- 接受 C 风格字符数组的 `insert` 和 `assign` 版本。

```cpp
const char *cp = "hello, world";
s.assign(cp, 5);   // 将前5个字符拷贝给 s
s.insert(s.size(), cp+5);  // s = "hello, world"
```

- `append` 在 string 结尾插入内容

- `replace` 替换字符串中的内容，相当于 `erase` + `insert`

```cpp
string s = "c++ primer 4th edition";
s.erase(11, 3);
s.insert(11, "5th"); // s = "c++ primer 5th edition"

// 上述操作等价于

s.replace(11, 3, "5th");
```

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7r4dfknilj20sh0lxtg0.jpg)

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7r4e1hek5j20sl0b4q52.jpg)

##### 9.5.3 string 搜索

- `find` 函数完成最简单的搜索，返回第一个匹配位置的下标，否则返回 `string::npos`

```cpp
string name("annabella");
string s("bella");
auto pos = name.find("Ana");
if (pos != string::npos)
{
    cout << pos << endl;
}
else cout << "cannot find" << endl;
```

- `rfind` 返回最后一个出现的位置，否则返回 `string::npos`

- `find_first_of` 和 `find_last_of` 分别查找字符第一次出现的位置和最后一次出现的位置，否则返回 `string::npos` （匹配）

```cpp
string numbers("1234567890"), code("zxc00234");
cout << code.find_last_of(numbers) << endl; // code 中最后一次出现数字的位置
cout << code.find_first_of(numbers) << endl;// code 中第一次出现数字的位置
```

- `find_first_not_of` 和 `find_last_not_of` 查找字符中第一个不在参数中的字符的位置和最后一个不在参数中的字符的位置

```cpp
string numbers("1234567890"), code("11223zxcvbb");
auto pos1 = code.find_first_not_of(numbers);  // pos1 = 5
auto pos2 = code.find_last_not_of(numbers);   // pos2 = 10
auto pos3 = code.find_first_not_of("123zxcvb"); // pos3 = string::npos
```

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7rr9vppp8j20se097juh.jpg)

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7rra7eeivj20sf07wjtk.jpg)

其中每个操作都可以指定一个开始搜索的位置 `pos`

- `cp, pos`

```cpp
string name("annabellanna");
const char* cp = "nn";
string::size_type pos = 0;

while ((pos = name.find(cp, pos)) != string::npos)
{
    cout << "found string [" << cp << "] at index " << pos << endl;
    ++pos; 
}
/*
在字符串 name 中搜索指针 cp 指向的以空字符结尾的 C 风格的字符串
found string [nn] at index 1
found string [nn] at index 9
*/
```

- `cp, pos, n`

```cpp
string name("annabellanna");
const char* cp = "nn";
string::size_type pos = 0;

while ((pos = name.find(cp, pos, 1)) != string::npos)
{
    cout << "found string [" << cp << "] at index " << pos << endl;
    ++pos; 
}
/*
搜索指针 cp 指向的数组的前 1 个字符，即"n"
found string [nn] at index 1
found string [nn] at index 2
found string [nn] at index 9
found string [nn] at index 10
*/
```

###### 指定搜索位置

通过指定搜索位置在字符串中循环搜索某个字符串出现的位置。

```cpp
string name("annabellanna");
string s("anna");
string::size_type pos = 0;
while ((pos = name.find(s, pos)) != string::npos)
{
    cout << "found string [" << s << "] at index " << pos << endl;
    ++pos; 
}
/*
found string [anna] at index 0
found string [anna] at index 8
*/
```

###### compare 函数

`compare` 函数的几种参数形式：

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7rzutdmjsj20sh0bm77i.jpg)

##### 9.5.5 数值和 string 转换

C++11 新标准引入了多个函数实现数值数据和 string 之间的转换

```cpp
double d = 3.1415909988;
std::string s = std::to_string(d);
std::cout << s << std::endl; // 3.141591
double dd = std::stod(s);    // dd = 3.14159
```

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7s4kf2vmmj20uu0elq8t.jpg)

转换函数如上图所示，

- string 参数中第一个非空白字符比如是符号 (+, -) 或者数字。

- 可以以小数点开头，包含 e 来表示指数部分，也可以以 0x 或者 0X 开头表示十六进制数字。

- 根据不同的基数可以包含字母字符来表示大于数字9的数。

- 如果 string 不能转换为数值，抛出 `invalid_argument` 异常。

- 如果转换得到的数值不能用任何类型来表示，抛出 `out_of_range` 异常。


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

| 方法                          | 简介                                           |
| ----------------------------- | ---------------------------------------------- |
| vector<T> v1                  | v1是一个空vector，元素为类型T，执行默认初始化  |
| vector<T> v2(v1)              | v2中包含有v1所有元素的副本                     |
| vector<T> v2 = v1             | 等价于v2(v1)                                   |
| vector<T> v3(n, val)          | v3包含了n个重复的元素，每个元素的值都为val     |
| vector<T> v4(n)               | v4包含了n个执行了值初始化的对象，经过测试值为0 |
| vector<T> v5{a, b, c, ...}    | v5包含了初始值个数的元素，并赋初值             |
| vector<T> v5 = {a, b, c, ...} | 同上                                           |

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

| 操作              | 解释                             |
| ----------------- | -------------------------------- |
| v.empty()         | v为空则返回true                  |
| v.size()          | 返回v中字符的个数                |
| v.push_back(t)    | 向v的尾端添加元素t               |
| v[n]              | 返回v中第n个位置上元素的**引用** |
| v1=v2             | 用v2中元素的拷贝代替v1中的元素   |
| v1={a, b, c, ...} | 用列表中元素的拷贝代替v1中的元素 |
| v1==v2, v1!=v2    | 比较两个vector是否完全相同       |
| <, >, <=, >=      | 以字典中的顺序进行比较           |

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

vector对象的索引也是`size_type`类型。不能用下标的形式添加元素

### 3.3.4 补充

#### vector.back()

- `vector.back()`方法返回vector最后一个元素的引用。
- `vector.front()`方法返回vector首元素的引用。
- `vector.begin()`方法返回指向vector第一个元素的迭代器。
- `vector.end()`方法返回指向vector尾元素的下一个元素的迭代器。

>reference leetcode120

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

| 运算符                          | 含义                                                                                             |
| ------------------------------- | ------------------------------------------------------------------------------------------------ |
| *iter                           | 返回迭代器iter所指元素的引用                                                                     |
| iter->name                      | 解引用iter并获取该元素名为name的成员，等价于(*iter).name                                         |
| ++iter                          | 令iter指向容器中的下一个元素                                                                     |
| --iter                          | 令iter指向容器中的上一个元素                                                                     |
| iter1 == iter2 / iter1 != iter2 | 判断两个迭代器是否相等，如果两个迭代器指示的是同一个元素或者同一个容器的尾后迭代器，那么他们相等 |

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

| 运算符        | 含义                                                                                                  |
| ------------- | ----------------------------------------------------------------------------------------------------- |
| iter + n      | 迭代器指示的新位置比原来的位置向前移动n个元素，结果为指向容器内的一个元素或者容器结尾元素的下一个位置 |
| iter - n      | 同上                                                                                                  |
| iter += n     | 将iter+n的结果赋给iter                                                                                |
| iter -= n     | 将iter-n的记过赋给iter                                                                                |
| iter1 - iter2 | 同一个容器中两个迭代器之间的距离                                                                      |
| \>, >=, <, <= | 指向同一个容器中迭代器前后位置的比较                                                                  |

只要两个迭代器指向的是同一个容器中的元素或者尾元素的下一个位置，就能将他们相减，结果的类型名是`difference_type`，是一个有符号整数。

## 3.5 数组

- 数组和vector相似的地方：数组也是存放相同对象的容器。

- 数组和vector不同的地方：数组的大小固定不变，不能随意添加元素。

数组的大小固定，对于某些特殊的程序运行的性能比较好，但相应的损失了一些灵活性。

### 3.5.1 定义和初始化内置数组

编译时，数组的维度必须是已知的，即维度必须是一个**常量表达式**。

```cpp
unsigned cnt = 42;        // 不是常量表达式
constexpr unsigned sz = 42;   // 常量表达式，关于constexpr，参见2.4.4
int arr[10];
int *parr[sz];            // 含有42个整形指针的数组
string bad[cnt];          // false，cnt不是常量表达式
string strs[get_size()]   // 当get_size()是constexpr时候正确，否则错误
```

>2.4.4:一般来说，如果你认定一个变量是一个常量表达式，那就把它声明成`constexpr`类型

然而，实际测试的时候(`g++ -std=c++11`)：

```cpp
unsigned count = 32;

int bad[count];

cout << sizeof(bad) << endl;

const unsigned count1 = 32;

string good[count1];

constexpr unsigned count2 = 33;

int well[count2];

cout << sizeof(well) << endl;
```

三种初始化参数的值`unsigned count`, `const unsigned`, `constexpr unsigned`，都可以正常初始化数组.这是因为在编译的时候，变量`count`已经获得了确定的数值。

如果在编译的时候没有获得确定的数值，例如下边：

```cpp
unsigned count3;

cin >> count3;

int notok[count3];

cout << sizeof(notok) << endl;
```

编译也正常的工作。若定义函数作为数组初始化的维度，也可正常工作，如下所示。

```cpp
int get_size()
{
    int a, b;
    cin >> a >> b;

    return a - b;
}


int main()
{
    int testfunc[get_size()];

    cout << sizeof(testfunc) << endl;
}
```

#### 显式初始化数组元素

可以对数组的元素进行显式初始化，此时允许忽略数组的维度。

```cpp
const unsigned sz = 3;
int a1[sz] = {0, 1, 2};
int a2[] = {0, 1, 2};
int a3[5] = {0, 1, 2};           // a3 = {0, 1, 2, 0, 0}
string a4[3] = {"hi", "hello"};  // a4 = {"hi", "hello", ""}
int a5[2] = {0, 1, 2};           // false，初始值太多
```

其中字符数组初始化的时候具有特殊性：

```cpp
char a1[] = {"C", "+", "+"};
char a2[] = {"C", "+", "+", "\0"};
char a3[] = "C++"；              // 自动添加表示字符串结尾的空字符
const char a4[5] = "Hello";      // false，没有空间存放空字符
```

#### 不允许拷贝和赋值

不能将数组的内容拷贝给其他数组作为其初始值，也不能用数组为其他数组赋值：

```cpp
int a[] = {0, 1, 2};
int a2[] = a;         // false
a2 = a;               // false
```

#### 复杂的数组声明

默认情况下，类型修饰符从右向左依次绑定（从右向左读）。

```cpp
int *p[10];           // p是一个含有10个整形指针的数组

int &ref[10] = ?;     // false，不存在引用的数组

int (*p)[10] = &arr;  // p指向一个含有10个整数的数组（先读括号内部，p是一个指针，指针指向数组arr，arr含有10个整数）

int (&arrRef)[10] = arr;  //arrRef引用一个含有10个整数的数组（先读括号内部，arrRef是一个引用，然后读右侧，引用数组arr，含有10个整数）

int *(&ref)[10] = arr;    // ref引用一个含有10个整形指针的数组（先读括号内部，ref是一个引用，然后读右侧，引用数组arr，大小为10，元素为整形指针）

```

#### 访问数组元素

数组下标的类型是`size_t`类型。`size_t`是一种机器相关的无符号类型，它被设计得足够大，以便能表示内存中任意对象的大小。

- 数组的下标运算符是由C++直接定义的，vector的下标运算符由库模板vector定义。

### 3.5.3 指针和数组

使用数组的时候编译器一般会把它转化成指针，使用取地址符可以获得指向数组某个元素的指针。

```cpp
string nums[] = {"one", "two", "three"};
// 此处为获得指向某个元素的指针，若要获得某个元素，可以直接string p = nums[1];
string *p0 = &nums[0];
string *p1 = &nums[1];

string *p2 = &nums;          // 等价于获得数组nums首元素的地址，即指针指向数组首元素
```

- 使用数组作为一个auto变量的初始值时，推断得到的类型是指针：

```cpp
int ia[] = {0, 1, 2, 3, 4};
auto ia2(ia);        // ia2是一个整形指针，指向ia的第一个元素
```

上述编译器初始化时执行的工作类似于：

```cpp
auto ia2(&ia[0]);
```

- 使用decltype关键字时，`dealtype(ia)`返回的类型是由10个整数构成的数组。

```cpp
decltype(ia) ia3 = {0, 1, 2, 3, 4};
ia3[2] = 100;
```

#### 指针也是迭代器

vector和string迭代器支持的运算，指针全部支持。

```cpp
int arr[] = {0, 1, 2, 3, 4, 5, 6 ,7, 8, 9};
int *b = arr;         // b指向arr的第一个元素
int *e = &arr[10];    // 相当于尾后迭代器，指向arr尾元素下一个位置的指针

// 用于输出arr的元素
for (int *b = arr; b != e; ++b)
    cout << *b << endl;
```

#### 使用begin和end函数操作数组

C++11 引入了begin和end函数，对于一个数组，begin和end分别可以获得首元素的指针和尾元素下一位置的指针。

这两个函数定义在`<iterator>`头文件中

```cpp
int arr[] = {0, 1, 2, 3, 4};
int *b = begin(arr);
int *e = end(arr);
```

#### 指针运算

指针可以进行加减运算，结果仍然是指针。

```cpp
constexpr size_t size= 5;
int arr[size] = {0, 1, 2, 3, 4};

int *begin = arr;         // 首元素的指针
int *end = begin + size;  // 首元素指针+size即为尾元素下一个元素的指针，尾后指针
```

两个指针相减的结果是它们之间的距离，类型为`ptrdiff_t`，因为可能为负值，所以是一种带符号类型。

```cpp
auto n = end(arr) - begin(arr);
```

指针的比较可以用来遍历一个数组的元素。

```cpp
int *b = arr, *e = arr + sz;
while (b < e)
{
    cout << *b << endl;
    ++b;
}
```

#### 解引用和指针运算

解引用时候的在不同情况下要添加。

例如：

```cpp
int ia[] = {0, 1, 2, 3, 4};
int last = *(ia + 4);       // 此处为ia+4指向地址再解引用

int notlast = *ia + 4;      // 此处为对ia解引用再+4
```

#### 下标运算

内置的下标运算符所用的索引值不是无符号类型，而vector和string的下标索引值都是无符号类型。

即：数组的下标符号可以为负。

```cpp
int arr[] = {0, 1, 2, 3, 4};
int *p = &arr[2];

int a0 = p[-2];
int a1 = p[-1];
int a3 = p[1];
int a4 = p[2]
```

### 3.5.4 C风格字符串

字符串字面值是一种通用结构的实例，这种结构是C++由C继承而来的**C风格字符串**。

按此习惯书写的字符串放在字符数组中以空字符(null terminated)结束。

#### C标准库string函数

这些函数在C语言中定义在`<string.h>`头文件中，在C++中定义在`<cstring>`头文件中

| 函数           | 含义                                                                                  |
| -------------- | ------------------------------------------------------------------------------------- |
| strlen(p)      | 返回p的长度，空字符不计算在内                                                         |
| strcmp(p1, p2) | 比较p1和p2的长度。如果p1==p2，返回0；如果p1>p2，返回一个整数；如果p1<p2，返回一个负数 |
| strcat(p1, p2) | 将p2附加到p1之后，返回p1                                                              |
| strcpy(p1, p2) | 将p2拷贝给p1，返回p1                                                                  |

传入此类函数的指针必须指向以空字符作为结束的数组。

```cpp
char ca = {'C', '+', '+'};
cout << strlen(ca) << endl;  // false，ca没有以空字符结束 
```

#### 比较字符串，C风格和C++风格的

C++风格：

```cpp
string s1 = "A string example";
string s2 = "A different string";
if (s1 == s2, s1 < s2, s1 > s2, ...) 
```

C风格：

```c
const char ca1[] = "A string example";
const char ca2[] = "A different string";
if (ca1 < ca2)       // error,试图比较两个无关的地址
if (strcmp(ca1, ca2) < 0)     // 相当于if (ca1 < ca2)
```

#### 连接字符串

C++风格：

```cpp
string str = str1 + " " + str2;
```

C风格：

```cpp
// 必须计算准确str的大小
strcpy(str, ca1);
strcat(str, " ");
strcat(str, ca2);
```

### 混用C风格和C++风格字符串

允许使用字符串字面值来初始化`string`对象，但是若要使用string对象初始化C风格字符串，需要使用函数`c_str()`，该函数的返回值是一个 ***指针，指向一个以空字符结束的字符数组，内容和`string`对象相同*** 。

```cpp
string s = "hello, world";

char *str = s;                    // false, 不能使用string对象初始化char*
const char *str = s.c_str();      // true
```

但是无法保证`c_str()`函数返回的数组一直有效，若要保证可以一直使用其返回的数组，最好进行一份拷贝。例子如下：

```cpp
int main()
{
    string s = "hello, world";
    const char *str = s.c_str();
    cout << str << endl;
    // 更改string对象s的值
    // 相应的str也会改变
    s = "hello, didi";
    cout << s << endl;
    cout << str << endl;

    return 0;
}
```

#### 使用数组初始化vector对象

不允许使用一个数组为另外一个内置类型的数组赋初始值，也不允许使用vector对象初始化数组。但是可以使用数组初始化vector对象。

```cpp
int arr[] = {1, 2, 3, 4, 5, 6};
vector<int> v(begin(arr), end(arr));
vector<int> v2(arr+1, arr+3);         //拷贝数组arr[1], arr[2]
```

![](https://ws1.sinaimg.cn/large/7e197809ly1g2spwl1g1bj20tx02q0tl.jpg)

## 3.6 多维数组

```cpp
int a[3][4];  // 数组大小为3，每个元素是含有4个整数的数组
int b[10][20][30];  // 数组大小为10，每个元素是大小为20的数组，大小为20数组的元素是含有三数个整数的数组
```

### 多维数组的初始化

```cpp
int a[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

//或者
int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

//如果只想初始化每行的第一个元素，未被列出的元素自动初始化
int a[3][4] = {{0}, {1}, {2}};

//初始化前几个元素
int a[3][4] = {1, 2, 3, 4};

//定义引用，把row绑定到a[1]这一行
int (&row)[4] = a[1];  
```

程序中经常用两重循环来处理多维数组：

```cpp
constexpr size_t row = 3, col = 4;
int a[row][col];
for (size_t i=0; i!=row; ++i)
{
    for (size_t j=0; j!=col; ++j)
    {
        a[i][j] = i * row + j;
    }
}
```
在C++11中可以如下简化：

```cpp
size_t count = 0;
for (auto &row : a)
{
    for (auto &x : row)
    {
        x = count;
        ++count;
    }
}
```

#### 使用for循环遍历多维数组（注意引用）

如果使用范围for语句遍历多维数组，除了最内层的循环之外，其他所有循环的控制变量都应该是 ***引用类型*** 。
如果不是引用类型，如下所示：

```cpp
for (auto x: a)
{
    for (auto i: x)
}
```

因为x不是引用类型，所以编译器初始化x的时候会自动将这些数组形式的元素转换成指向该数组内首元素的指针，即x是`int*`，那么内层的循环将不合法。（参见3.5.3）

> ***使用数组作为一个auto变量的初始值时，推断得到的类型是指针***：
>
>```cpp
>int ia[] = {0, 1, 2, 3, 4};
>auto ia2(ia);        // ia2是一个整形指针，指向ia的第一个元素
>```
>
>上述编译器初始化时执行的工作类似于：
>
>```cpp
>auto ia2(&ia[0]);
>```

#### 定义指向多维数组的指针

```cpp
int a[3][4];
int (*p)[4] = a;    // 首先p是一个指针，指针的内容是维度为4的数组，类型为整形，首地址为a
p = &a[2];
```

>关于`int (*p)[4] = a`，见`test.cpp`

#### 使用auto和decltype来遍历多维数组

```cpp
int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
for (auto p=a; p!=a+3; ++p)
{
    for (auto q=*p; q!=*p+4; ++q)
    {
        cout << *q << " ";
    }
    cout << endl;
}
```

上述表达方法使用`begin`和`end`函数更简单一些。

```cpp
for (auto p=begin(a); p!=end(a); ++p)
{
    for (auto q = begin(*p); q!=end(*p); ++q)
        cout << *q << " ";
    cout << endl;
}
```

#### 使用类型别名简化多维数组的指针

```cpp
using int_array = int[4];
// or
typedef int int_array[4];
```

#### 习题3.43, 3.44, 3.45中多维数组的几种遍历方法

```cpp
int main()
{
    int ia[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // 范围for语句
    for (int (&row)[4]: ia)
        for (int col: row) cout << col << " ";
    cout << endl;

    // 普通for语句，下标运算符
    for (size_t i=0; i<3; ++i)
        for (size_t j=0; j<4; ++j) cout << ia[i][j] << " ";
    cout << endl;

    // 普通for语句，指针
    for (int (*p)[4]=ia; p!=ia+3; ++p)
        for (int *q=*p; q!=*p+4; ++q) cout << *q << " ";
    cout << endl;
}
```

使用类型别名：

```cpp
int main()
{
    int ia[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    typedef int int_array[4];
    // using int_array int[4];

    // 范围for语句
    for (int_array &row: ia)
        for (int col: row) cout << col << " ";
    cout << endl;

    // 普通for语句，下标运算符
    for (size_t i=0; i<3; ++i)
        for (size_t j=0; j<4; ++j) cout << ia[i][j] << " ";
    cout << endl;

    // 普通for语句，指针
    for (int_array *p=ia; p!=ia+3; ++p)
        for (int *q=*p; q!=*p+4; ++q) cout << *q << " ";
    cout << endl;
}
```

使用auto：

```cpp
int main()
{
    int ia[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // 范围for语句，使用auto的时候范围for循环必须添加引用
    for (auto &row: ia)
        for (auto col: row) cout << col << " ";
    cout << endl;

    // 普通for语句，下标运算符
    for (size_t i=0; i<3; ++i)
        for (size_t j=0; j<4; ++j) cout << ia[i][j] << " ";
    cout << endl;

    // 普通for语句，指针，使用auto的时候可以不加引用
    for (auto p=ia; p!=ia+3; ++p)
        for (auto q=*p; q!=*p+4; ++q) cout << *q << " ";
    cout << endl;
}
```