<!--
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-05-18 23:45:30
 * @LastEditTime: 2019-05-18 23:45:30
 * @LastEditors: your name
 -->
书写格式：

## 标题

>引用多少页的内容

详细解释

```
代码
```
--------------------------------
## 目录

<!-- TOC -->

- [标题](#标题)
- [目录](#目录)
- [对常量的引用](#对常量的引用)
- [赋值运算右结合律，返回左侧运算对象](#赋值运算右结合律返回左侧运算对象)
- [解引用和递增运算符](#解引用和递增运算符)
- [条件运算符的右结合律](#条件运算符的右结合律)
- [逻辑和关系运算符，运算对象和求值结果都是右值](#逻辑和关系运算符运算对象和求值结果都是右值)
- [string （字符串） 和 char[] （字符数组）的指针](#string-字符串-和-char-字符数组的指针)
- [字符串赋值给字符指针](#字符串赋值给字符指针)
- [让 std::cin 读取空白字符](#让-stdcin-读取空白字符)
- [解引用和递增运算符](#解引用和递增运算符-1)
- [指针的引用](#指针的引用)
- [递归打印 vector](#递归打印-vector)
- [检查类型是否为字面值(literal type)](#检查类型是否为字面值literal-type)

<!-- /TOC -->
--------------------------------

## 对常量的引用

>p127 逻辑和关系运算符

s被声明为了对常量的引用，在这里因为text的内容是string对象，可能非常大。所以把s声明成引用可以避免对元素的拷贝。由于不需要对s进行写，所以声明成对常量的引用。

```cpp
for (const auto &s: text){
    cout << s;
    if (s.empty() || s[s.size()-1] == '.') cout << endl;
    else cout << " ";
}
```

## 赋值运算右结合律，返回左侧运算对象

>p129 赋值运算符

赋值运算符满足右结合律，返回左侧运算对象。

```cpp
int a, b;
a = b = 1;
// 相当于，其中b为右侧赋值运算符的返回值
a = (b = 1);
```

## 解引用和递增运算符

>p132 递增运算符

递增运算符的优先级大于解引用运算符。所有执行结果是返回当前值，然后向前移动一个位置。

`*p++` = `*(p++)`

## 条件运算符的右结合律

>p135 嵌套条件运算符

条件运算符的结合性是右结合的，即 `a?b:c?d:e` 为 `a?b:(c?d:e)` ，即靠右边的条件运算构成了靠左边的条件运算的分支。

若它是左结合的话，上述条件表达式加括号应为 `(a?b:c)?d:e` .

## 逻辑和关系运算符，运算对象和求值结果都是右值

>p126 逻辑和关系运算符

留个坑

## string （字符串） 和 char[] （字符数组）的指针

>p133 成员访问运算符

对于该章节的例子，声明指向某一个 string 的指针：

```cpp
string s1 = "hello, world", *p1 = s1; 
```

上述写法报错：

```
error: cannot convert 'std::string {aka std::basic_string<char>}' to 'std::string* {aka std::basic_string<char>*}' in initialization
     string s1 = "hello, world", *p = s1;
```

正确写法为：需要在 s1 前方加上取地址符。

```cpp
string s1 = "hello, world", *p1 = &s1;
```

不要和指向字符数组的指针搞混，指向字符数组可以不加取地址符。

```cpp
char s2[] = "HELLO WORLD", *p1 = s2;
cout << *p1;  // 输出'H'
```

## 字符串赋值给字符指针

对于语句 `const char *a = "HELLO"`来说，声明了一个字符指针，并将字符串常量的第一个字符的地址赋值给指针 a。

```cpp
char *a = "hello";
cout << *a << " " << *(a+1) << endl; 
// warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
//     char *a = "hello";
// 不赞成将字符串常量转换成 char*
```

正确写法应该为 `const char *a = "hello";`

## 让 std::cin 读取空白字符

>p164 习题5.11

习题5.11统计空格，制表符，换行符的数量。所以需要 std::cin 读取空格。

在标准的流中，有一个skipws标记，默认是置位的，表明当读取空白字符时，会将它们丢弃。使用std::noskipws操纵符可以清除这个标记：

```cpp
while (std::cin >> std::noskipws >> c)
{
     std::cout << c << std::endl;
}
```

默认是忽略掉空格的，也就是：

```cpp
while (std::cin >> std::skipws >> c)
{
     std::cout << c << std::endl;
}
```

## 解引用和递增运算符

>p132 在一条语句中混用解引用和递增运算符

后置运算符的优先级要高于解引用运算符，运算符优先级表见 [运算符优先级表](https://github.com/piaoliangkb/CppPrimer#%E8%A7%A3%E5%BC%95%E7%94%A8%E5%92%8C%E9%80%92%E5%A2%9E%E8%BF%90%E7%AE%97%E7%AC%A6)

```cpp
cout << *begin++ << endl;
// 相当于
cout << *(begin++) << endl;
```

作用为输出 begin 开始指向的元素，并且将指针向前移动一个位置。

## 指针的引用

>p196 习题6.22

习题要求交换两个int指针，则需要将指针形参设置为指针的引用。

```cpp
void swap(const int* &p1, const int* &p2)
{
     auto temp = p1;
     p1 = p2;
     p2 = temp;
}
```

## 递归打印 vector

练习 6.47

```cpp
void output(vector<int> &v)
{
    if (!v.empty())
    {
        auto last = v.back();
        v.pop_back();
        output(v);
        cout << last << " ";
    }
}
```

练习 6.33

```cpp
void output(vector<int> &v, vector<int>::iterator it)
{
    if (it != v.end())
    {
    cout << *it << endl;
    output(v, ++it);  // or output(v, next(it));
    }
}
```

## 检查类型是否为字面值(literal type)

见练习7.55

```cpp
#include <type_traits>

std::is_literal_type<std::string>::value;
```
