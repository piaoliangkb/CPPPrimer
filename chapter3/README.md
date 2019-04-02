<!-- TOC -->

- [第三章 字符串，向量，数组](#%E7%AC%AC%E4%B8%89%E7%AB%A0-%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%90%91%E9%87%8F%E6%95%B0%E7%BB%84)
  - [3.1 使用using声明命名空间](#31-%E4%BD%BF%E7%94%A8using%E5%A3%B0%E6%98%8E%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4)
  - [3.2 标准库类型string](#32-%E6%A0%87%E5%87%86%E5%BA%93%E7%B1%BB%E5%9E%8Bstring)
    - [3.2.1 定义和初始化string对象](#321-%E5%AE%9A%E4%B9%89%E5%92%8C%E5%88%9D%E5%A7%8B%E5%8C%96string%E5%AF%B9%E8%B1%A1)
    - [3.2.2 string对象的操作](#322-string%E5%AF%B9%E8%B1%A1%E7%9A%84%E6%93%8D%E4%BD%9C)
      - [读写string对象](#%E8%AF%BB%E5%86%99string%E5%AF%B9%E8%B1%A1)
      - [读取位置数量的string对象](#%E8%AF%BB%E5%8F%96%E4%BD%8D%E7%BD%AE%E6%95%B0%E9%87%8F%E7%9A%84string%E5%AF%B9%E8%B1%A1)
      - [使用getline读取一整行](#%E4%BD%BF%E7%94%A8getline%E8%AF%BB%E5%8F%96%E4%B8%80%E6%95%B4%E8%A1%8C)
      - [empty()和size()](#empty%E5%92%8Csize)
      - [string::size_type 类型](#stringsizetype-%E7%B1%BB%E5%9E%8B)

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
