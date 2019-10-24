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
- [处理string对象中的字符(such as `isdigit`, `isalpha`..)](#处理string对象中的字符such-as-isdigit-isalpha)
- [使用 std::boolalpha 在标准输出打印 true, false](#使用-stdboolalpha-在标准输出打印-true-false)
- [从数组向 vector 拷贝元素](#从数组向-vector-拷贝元素)
- [迭代器运算符 和 迭代器支持的算术运算](#迭代器运算符-和-迭代器支持的算术运算)
- [使用 cout 输出 float, double 指定的精度](#使用-cout-输出-float-double-指定的精度)
- [sizeof 求数组大小](#sizeof-求数组大小)
- [remove_if + erase 删除容器中符合要求的元素](#remove_if--erase-删除容器中符合要求的元素)
- [动态分配对象初始化（`new`）](#动态分配对象初始化new)
- [shared_ptr 初始化方式](#shared_ptr-初始化方式)

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

## 处理string对象中的字符(such as `isdigit`, `isalpha`..)

>3.2.3 p82

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

## 使用 std::boolalpha 在标准输出打印 true, false

>p305 练习9.15等

```cpp
bool isOk()
{
    if(...) return true;
    else return false;
}

std::cout << std::boolalpha << isOk() << std::endl; // 可以打印出 true or false 而不是 0 1
```

## 从数组向 vector 拷贝元素

>p312 练习9.26

可以提供数组首地址，和使用 std::end() 函数获得数组尾地址。

```cpp
int ia[] = {0, 1, 2, 3, 4, 5};
std::vector<int> v(ia, std::end(ia));
// 判断是否为2的倍数使用位运算
if (*iter2 & 0x1) iter2 = lst.erase(iter2);
```

## 迭代器运算符 和 迭代器支持的算术运算

>p96 标准迭代器支持的运算符

| 运算符                          | 含义                                                                                             |
| ------------------------------- | ------------------------------------------------------------------------------------------------ |
| *iter                           | 返回迭代器iter所指元素的引用                                                                     |
| iter->name                      | 解引用iter并获取该元素名为name的成员，等价于(*iter).name                                         |
| ++iter                          | 令iter指向容器中的下一个元素                                                                     |
| --iter                          | 令iter指向容器中的上一个元素                                                                     |
| iter1 == iter2 / iter1 != iter2 | 判断两个迭代器是否相等，如果两个迭代器指示的是同一个元素或者同一个容器的尾后迭代器，那么他们相等 |

特别注意：forward_list 迭代器不支持递减运算符。

>p99 string, vector, deque, array 支持的算术运算

| 运算符        | 含义                                                                                                  |
| ------------- | ----------------------------------------------------------------------------------------------------- |
| iter + n      | 迭代器指示的新位置比原来的位置向前移动n个元素，结果为指向容器内的一个元素或者容器结尾元素的下一个位置 |
| iter - n      | 同上                                                                                                  |
| iter += n     | 将iter+n的结果赋给iter                                                                                |
| iter -= n     | 将iter-n的记过赋给iter                                                                                |
| iter1 - iter2 | 同一个容器中两个迭代器之间的距离                                                                      |
| \>, >=, <, <= | 指向同一个容器中迭代器前后位置的比较                                                                  |

## 使用 cout 输出 float, double 指定的精度

>p327 9.5.5 string 和 double 类型数值转换

在使用 cout 输出 float, double 的时候，默认会输出一定精度的数值，（6位）：

```cpp
double d = 3.1415909988;
std::cout << d << std::endl; // 3.14159
double d1 = 3.1415;
std::cout << d1 << std::endl;// 3.1415
```

我们若要输出所有的精度，需要通过 `cout.precision(n)` 进行设定。


>https://stackoverflow.com/questions/45084317/what-is-the-role-of-stdsetprecision-without-stdfixed-in-c  stackoverflow 问题1
>http://www.cplusplus.com/reference/ios/ios_base/precision/

>Using the default floating-point notation, the precision field specifies the maximum number of meaningful digits to display in total counting both those before and those after the decimal point.  
使用默认的 float-point 表达方式，precision 制定了小数点前后表达数字的最大值。

```cpp
double d = 3.1415909988;
std::cout.precision(11);
std::cout << d << std::endl; // 3.1415909988


std::cout.precision(10);
std::cout << std::fixed << d << std::endl; // 3.1415909988
```

注意是否使用 `std::fixed` 是有区别的。

>In both the fixed and scientific notations, the precision field specifies exactly how many digits to display after the decimal point, even if this includes trailing decimal zeros.  
使用 std::fixed 之后，precision 指定了小数点之后显式的位数。不足则补0

```cpp
double item1 = 0.01;
std::cout << std::fixed << item1 << std::endl;
```

## sizeof 求数组大小

>p341 拷贝算法

对于数组 `int a[] = {1, 2, 3, 4, 5}`

- `sizeof(a) = 20;` sizeof 数组名表示数组占用字节大小。

- `sizeof(*a) = 4;` 表示元素占用字节大小。

所以 `sizeof(a)/sizeof(*a)` 代表数组大小。

对于指针 `int *aa = new int[5]`

- `sizeof(aa) = 8;` sizeof 指针名计算指针的大小，8字节，64位。

- `sizeof(*aa) = 4;` 求元素占用字节大小。

## remove_if + erase 删除容器中符合要求的元素

>ex11.4

>ref: https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom

`std::remove_if` 函数可以接受一个谓词，将容器中使得谓词为真的元素放到容器的末尾，返回最后一个使得谓词为假的元素的后一个元素迭代器。

`erase` 为容器特有的操作，可以删除范围内的元素。

两个函数配合可以删除容器中符合要求的元素：

```cpp
word.erase(remove_if(word.begin(), word.end(), 
                            [](const char c){return ispunct(c);}), word.end());
```

上述删除了 `word` 这个字符串中的标点符号。

## 动态分配对象初始化（`new`）

>chapter 12.1.2 直接管理内存

几种方式：

默认初始化，直接初始化方式（直接构造，列表初始化），值初始化

- 默认初始化

`new` 无法为其分配的对象命名，而是返回一个指向该对象的指针。

`int *pi = new int;`

默认情况下，动态分配的对象是 **默认初始化** 的，即：

- 内置类型或者组合类型的对象的值是未定义的； `int *pi = new int;` pi指向未初始化的 int

- 类类型的对象将用默认构造函数进行初始化； `string *ps = new string;` 初始化为空 string

- 直接初始化方式（构造，列表初始化）

- 传统的构造方式：

```cpp
int *pi = new int(1024); // 传统的构造方式
string *ps = new string(10, '9');
```

- 列表初始化方式：

```cpp
vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6};
```

- 值初始化

在类型名之后跟一对括号，即对动态分配的对象值初始化：

```cpp
string *ps1 = new string;  // 默认初始化
string *ps2 = new string();// 值初始化为空 string

int *pi1 = new int;        // 默认初始化，*pi1未定义
int *pi2 = new int();      // 值初始化，*pi2 = 0
```

- 对于定义了自己构造函数的类类型来说(string)，值初始化没有意义：对象都会通过默认构造函数来初始化。

- 对于内置类型：值初始化的内置类型对象有着良好定义的值，默认初始化对象的值是未定义的。

使用括号包围的 **初始化器**：

若提供了一个括号包围的初始化器，就可以使用 auto 来推断我们想要分配对象的类型。

当括号中仅有单一初始化器时才可以使用 auto。

```cpp
auto p1 = new auto(obj);  // p 指向一个与 obj 类型相同的对象

auto p2 = new auto{a, b, c}; // error，括号中只能有单一初始化器
```

## shared_ptr 初始化方式

>chapter 12.1.1 shared_ptr 类 / 12.1.3 shared_ptr 和 new 结合使用

1. 不初始化，默认为空指针

```cpp
shared_ptr<int> p1;
```

2. 使用 `std::make_shared` 函数

```cpp
shared_ptr<string> s1 = make_shared<string>("hello"); // s1 指向一个 string 对象，值为"hello"
shared_ptr<int> s2 = make_shared<int>();  // 值初始化的 string，默认值为 0
```

3. 直接初始化（使用 new 返回的指针初始化智能指针）

```cpp
shared_ptr<int> pi(new int(42));
```

4. 此外：

- `shared_ptr<T> p(q)`：p 管理 **内置指针q** 所指向的对象；

- `shared_ptr<T> p(u)`：p 从 `unique_ptr u` 那里接管了对象的所有权；将 u 置空。

- `shared_ptr<T> p(q, d)`：p 接管了 **内置指针 q** 所指对象的所有权。q 必须能够转换成 `T*` 类型；p 使用可调用对象 d 来代替 `delete`。

- `shared_ptr<T> p(p2, d)`：p 是 **shared_ptr p2** 的拷贝；p 用可调用对象 d 来代替 `delete`。