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

如果想在字符串中保留输入时候的空白符，应该用<code>getline()</code>函数替代<code>>></code>.

<code>getline(istream &is, string s)</code>

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

<code>string.size()</code>的返回类型是string::size_type，不返回int或者unsigned体现了**标准库类型与机器无关的特性**。

size_type是一个无符号类型的值，允许编译器通过auto或者decltype来推断变量的类型：

```cpp
auto len = line.size();
decltype(line.size()) len;
```

注：假如n是一个负值int，那么表达式<code> s.size()<n </code>的判断结果一定是true。因为负值会自动的转换成一个比较大的无符号值。

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