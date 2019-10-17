<!-- TOC -->

- [第十章 泛型算法](#%e7%ac%ac%e5%8d%81%e7%ab%a0-%e6%b3%9b%e5%9e%8b%e7%ae%97%e6%b3%95)
  - [10.1 概述](#101-%e6%a6%82%e8%bf%b0)
  - [10.2 初识泛型算法](#102-%e5%88%9d%e8%af%86%e6%b3%9b%e5%9e%8b%e7%ae%97%e6%b3%95)
    - [10.2.1 只读算法](#1021-%e5%8f%aa%e8%af%bb%e7%ae%97%e6%b3%95)
      - [accumulate](#accumulate)
      - [equal](#equal)
    - [10.2.2 写容器元素算法](#1022-%e5%86%99%e5%ae%b9%e5%99%a8%e5%85%83%e7%b4%a0%e7%ae%97%e6%b3%95)
      - [fill_n](#filln)
      - [back_inserter](#backinserter)
      - [copy](#copy)
      - [repalce && replace_copy](#repalce--replacecopy)
    - [10.2.3 重排容器元素的算法](#1023-%e9%87%8d%e6%8e%92%e5%ae%b9%e5%99%a8%e5%85%83%e7%b4%a0%e7%9a%84%e7%ae%97%e6%b3%95)
      - [sort](#sort)
      - [unique](#unique)
  - [10.3 定制操作](#103-%e5%ae%9a%e5%88%b6%e6%93%8d%e4%bd%9c)
    - [10.3.1 向算法传递参数](#1031-%e5%90%91%e7%ae%97%e6%b3%95%e4%bc%a0%e9%80%92%e5%8f%82%e6%95%b0)
      - [谓词](#%e8%b0%93%e8%af%8d)
      - [stable_sort](#stablesort)
    - [10.3.2 lambda 表达式](#1032-lambda-%e8%a1%a8%e8%be%be%e5%bc%8f)
      - [find_if](#findif)
      - [lambda](#lambda)
      - [向 lanbda 传递参数](#%e5%90%91-lanbda-%e4%bc%a0%e9%80%92%e5%8f%82%e6%95%b0)
      - [使用捕获列表来捕获参数](#%e4%bd%bf%e7%94%a8%e6%8d%95%e8%8e%b7%e5%88%97%e8%a1%a8%e6%9d%a5%e6%8d%95%e8%8e%b7%e5%8f%82%e6%95%b0)
    - [10.3.3 lambda 捕获和返回](#1033-lambda-%e6%8d%95%e8%8e%b7%e5%92%8c%e8%bf%94%e5%9b%9e)
      - [值捕获](#%e5%80%bc%e6%8d%95%e8%8e%b7)
      - [引用捕获](#%e5%bc%95%e7%94%a8%e6%8d%95%e8%8e%b7)
      - [隐式捕获](#%e9%9a%90%e5%bc%8f%e6%8d%95%e8%8e%b7)
      - [lambda 修改值捕获参数](#lambda-%e4%bf%ae%e6%94%b9%e5%80%bc%e6%8d%95%e8%8e%b7%e5%8f%82%e6%95%b0)
      - [指定 lambda 返回类型](#%e6%8c%87%e5%ae%9a-lambda-%e8%bf%94%e5%9b%9e%e7%b1%bb%e5%9e%8b)
    - [10.3.4 参数绑定](#1034-%e5%8f%82%e6%95%b0%e7%bb%91%e5%ae%9a)
      - [bind 函数](#bind-%e5%87%bd%e6%95%b0)
        - [用 bind 重排函数顺序](#%e7%94%a8-bind-%e9%87%8d%e6%8e%92%e5%87%bd%e6%95%b0%e9%a1%ba%e5%ba%8f)

<!-- /TOC -->


# 第十章 泛型算法

## 10.1 概述

标准库没有给每个容器类型都定义成员函数来实现查找，替换，排序等操作，而是定义了一组泛型算法(generic algorithm)。

大多数算法都定义在头文件 `algorithm` 中，标准库还在头文件 `numeric` 中定义了一组数值泛型算法。

例如 `find` 函数：

```cpp
string val = "hello";
auto res = find(lst.cbegin(), lst.cend(), val);

int ia[] = {27, 210, 12, 47, 109, 83};
int val = 83;
int *res = find(begin(ia), end(ia), val);
auto res = find(ia+1, ia+4, val);
```

例如，string 查找返回指向第一个等于给定值元素的迭代器，否则返回第二个参数 `lst.cend()`；

内置数组通过 `begin`, `end` 函数来获得指向首元素和尾元素之后位置的指针，或者传递给 find 函数首尾地址，返回指向等于指定值元素的指针。

- 算法本身不会执行容器操作，只会运行于迭代器之上，执行迭代器操作。

- 算法不会改变容器的大小，不会直接添加或者删除元素。

- 特殊类型的迭代器 `inserter` 插入其可以向容器添加元素。

## 10.2 初识泛型算法

除了少数例外，标准库算法都对一个范围内的元素进行操作。总是使用前两个参数表示此范围，分别指向要 **处理的第一个元素** 和 **尾元素之后位置** 的迭代器。

### 10.2.1 只读算法

算法 | 头文件 | 作用
--- | --- | ---
`find` | `algorithm` | 返回指向第一个与给定值相等的迭代器，否则返回第二个参数
`count` | `algorithm` | 返回给定值在序列中出现的次数
`accumulate` | `numeric` | 对序列求和，第三个参数可以指定和的初始值
`equal` | `algorithm` | 确保两个序列是否存有相同的值，第三个参数表示第二个序列的首元素


#### accumulate

- `accumulate` 将第三个参数作为求和初始值，那么有着一个设定：序列范围内的元素类型加到和的类型上的操作必须可行。

例如，可以进行字符串的连接：

```cpp
string num = accumulate(v.cbegin(), v.cend(), stirng(""));
```

初始和的类型必须和元素类型相同：

```cpp
cout << accumulate(v.cbegin(), v.cend(), 0) << endl;   // 9
cout << accumulate(v.cbegin(), v.cend(), 0.0) << endl; // 9.42
```

第三个参数不能是字符串字面值，因为 `const char*` 类型没有 `+` 运算符。

#### equal

- `equal` 将序列中的每个元素与第二个序列中的对应元素进行比较。第三个参数表示第二个序列的首元素。

- 假定第二个序列至少与第一个序列一样长（必须有对应元素）。

- `equal` 可以对不同类型容器，不同类型元素进行比较。只要两个元素可以进行 `==` 运算符比较。例如：`vector<string>` 和 `list<const char*>` 可以进行比较。

>返回值
5-8) 如果范围 [first1, last1) 的长度不等于范围 [first2, last2) 的长度则返回 false 。
如果两个范围内的元素都相等，则返回 true 。
否则返回 false 。

```cpp
int main()
{
    vector<string> v = {"wo", "he", "wo", "de", "zu"};
    list<const char*> lst = {"wo", "he", "wo", "de"};
    if (std::equal(v.cbegin(), v.cend(), lst.cbegin())) {
        cout << "equals" << endl;
    }
    else {
        cout << "not equals" << endl;
    }
}
```

### 10.2.2 写容器元素算法

算法 | 头文件 | 作用
--- | --- | ---
`fill` | `algorithm` | 将给定值赋予序列中每个元素
`fill_n` | `algorithm` | 接受单迭代器，一个计数值，一个值；将单迭代器开始n个值赋值为给定值
`copy` | `algorithm` | 将给定序列拷贝到目标地址
`replace` | `algorithm` | 将序列中所有给定值改为新值，在原序列上操作
`replace_copy` | `algorithm` | 将序列中所有给定值换为新值，并且全部拷贝到目标迭代器位置，原序列不变

使用写算法，必须确保序列原大小至少不小于我们要写入的元素数目。

#### fill_n

`fill_n` 接受一个单迭代器，一个计数值，一个要赋的值。该函数假定写入指定个元素是安全的：

`fill_n(dest, n, val)` 要求从 `dest` 开始的序列至少包含 `n` 个元素。

- 在空容器中调用 `fill_n`

```cpp
vector<int> v;
fill_n(v.begin(), 10, 0); // 赋值10个0
```

这个语句的结果是未定义的。

#### back_inserter

插入迭代器是一种向容器中添加元素的迭代器，当我们通过一个插入迭代器赋值时，该值被添加到容器中。

- 定义在头文件 `iterator` 。

- `back_inserter` 接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。

- 赋值运算符会调用 `push_back` 操作将元素添加到容器中。

```cpp
vector<int> v;
auto it = back_inserter(v);
*it = 128;
```

- 使用 `back_inserter` 作为算法的目标位置：

```cpp
vector<int> v;
fill_n(back_inserter(v), 10, 2); 
```

上述相当于使用 `v.push_back()` 操作添加了10个元素2.

#### copy

- `copy` 前两个参数接受一个输入范围，第三个参数表示目标序列的起始位置。

- `copy` 返回目的位置迭代器递增之后的值，即拷贝的尾元素之后的元素的位置。 

```cpp
int a1[] = {1, 2, 3, 4, 5};
int a2[sizeof(a1)/sizeof(*a1)];
auto ret = copy(begin(a1), end(a1), a2);
```

#### repalce && replace_copy

- `replace` 接受一对范围，要替换的值，新值。

`replace(lst.begin(), lst.end(), old_val, new_val);`
  
- `replace_copy` 包括上述，还接受第三个迭代器参数，指出调整之后序列保存的位置。

`replace_copy(lst.cbegin(), lst.cend(), back_inserter(v), old_val, new_val);`

注意上述分别使用了迭代器的非常量版本和常量版本。

### 10.2.3 重排容器元素的算法

算法 | 头文件 | 作用
--- | --- | ---
`sort` | `algorithm` | 重排序列中的元素，默认使用元素的 `<` 运算符，可选一元谓词
`unique` | `algorithm` | 将重复元素放到队列的尾部，返回不重复区域之后一个位置的迭代器

#### sort

如下所示将 `vector<string>` 内的元素按照字典序进行排序：

```cpp
std::vector<std::string> v = {"fox", "jumps", "over", "quick", "red", "red", "slow", "the", "the", "turtle"};
std::sort(v.begin(), v.end()); 
// v = {fox jumps over quick red red slow the the turtle}
```

#### unique

为了使用 `unique` 首先要将容器排序，使得重复的元素相邻出现。

随后使用 `unique` 方法，让不重复出现的元素出现在 `vector` 的开始部分，重复出现的元素移动到末尾：

```cpp
auto end_unique = std::unique(v.begin(), v.end());
// v = {fox jumps over quick red slow the turtle the red}
```

`unique` 方法会返回 **指向不重复区域之后一个位置的迭代器**.

>根据 C++ Primer 第五版343页所说，该位置后的元素仍然存在，但我们不知道他们的值是什么。  
>根据 [cppreference](https://en.cppreference.com/w/cpp/algorithm/unique)，通过以使要擦除的元素被覆盖的方式移动范围内的元素来完成删除。(Removing is done by shifting the elements in the range in such a way that elements to be erased are overwritten.)

## 10.3 定制操作

默认情况下很多算法使用元素类型的 `<` 或者 `==` 运算符来进行比较序列中的元素，标准库允许我们自定义操作来代替默认运算符。

算法 | 头文件 | 作用
--- | --- | ---
`sort` | `algorithm` | 根据谓词进行排序
`stable_sort` | `algorithm` | 维持原有元素的顺序，根据谓词进行排序
`partition` | `algorithm` | 根据谓词将使得谓词为 true 的成员排在容器前半部分，其他后半部分，返回指向最后一个元素为 true 之后的位置
`stable_partition` | `algorithm` | 同 `partition` 重排元素，原始序列元素相对顺序不变
`find_if` | `algorithm` | 返回第一个使得谓词返回非0值的元素
`foe_each` | `algorithm` | 接受一个可调用对象，并对序列中的所有元素调用该对象
`transformer` | `algorithm` | 接受一个输入序列，一个目标位置和一个可调用对象，对输入序列每个元素调用最后一个参数并写结果到目标位置
`count_if` | `algorithm` | 接受一个输入序列和一个谓词，计算有多少使得谓词为真的元素


### 10.3.1 向算法传递参数

#### 谓词

`sort` 的第二个版本接受第三个参数 **谓词(predicate)**。谓词是一个可调用的表达式，其返回结果是一个能用作条件的值。

标准库算法使用的谓词：

- 一元谓词 (unary predicate) 只接受单一参数。

- 二元谓词 (binary predicate) 有两个参数。

接受谓词参数的算法对输入序列中的元素调用谓词，因此元素类型必须能转换成谓词的参数类型。

例如：

```cpp
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

sort(v.begin(), v.end(), isShorter);
```

#### stable_sort

`stable_sort` 排序算法维持了相等元素的原有顺序：

```cpp
struct Employee {
    int age;
    std::string name;  // 不参与比较
};

bool operator<(const Employee &lhs, const Employee &rhs) {
    return lhs.age < rhs.age;
}

int main()
{
    std::vector<Employee> v = {
        {108, "Zaphod"},
        {32, "Arthur"},
        {108, "Ford"},
    };  

    std::stable_sort(v.begin(), v.end());

    for (const auto &e : v) {
        std::cout << e.age << ", " << e.name << '\n';
    }
}
/*
32, Arthur
108, Zaphod
108, Ford
*/
```

如上所示，相等元素为 `{108, "Zaphod"}` 和 `{108, "Ford"}`，排序之后仍然维持了他们的原有顺序。

### 10.3.2 lambda 表达式

有些算法只接受一元谓词，所以函数参数受到了限制。

#### find_if

可以使用 `find_if` 算法来查找第一个具有特定大小的元素。

`find_if` 算法接受一对迭代器，表示一个范围，第三个参数是一个谓词；返回第一个使谓词返回非0值的元素，否则返回尾迭代器。

- `find_if` 只接受一元谓词

```cpp
vector<string> v = { "de", "hua", "woqueyao", "daitahuijia", "zaina", "shen", "yejiuba"};
auto pos = find_if(v.cbegin(), v.cend(), longer_than_4);
if (pos != v.end()) cout << *pos << endl; // woqueyao
```

#### lambda

- 我们可以向任何一个算法传递任何类别的可调用对象(callable object)。

- 如果一个对象或者表达式，可以对其使用调用运算符，则称它为可调用的。

一共有四种可调用对象：

- 函数

- 函数指针 (chapter6.7 p221)

- 重载了函数调用运算符的类 (chapter14.8 p506)

- lambda 表达式

一个 `lambda` 表达式的形式：

`[capture list] (params) -> return type { func body }`

- `capture list` 捕获列表是一个获取 `lambda` 所在函数中定义的局部变量的列表。

- `params`, `return type`, `func body` 和普通函数相同。

一个简单的定义：

`auto f = [] { return 42; };`

上述忽略的参数列表和返回类型，但是一定要有捕获列表和函数体。

完整定义：

`auto f = [] (const int i) -> int { return i+1; };`

**若 `lambda` 的函数体包含任何单一 `return` 语句之外的内容，且未指定返回类型，则返回 `void`**

#### 向 lanbda 传递参数

- 与普通函数不同，`lambda` 不能有默认参数。

- 空捕获列表表明 `lambda` 不适用其所在函数中的任何局部变量。

`auto f = [] (const int i) -> int { return i+1; };`

上述表示捕获列表为空，参数为 `const int`

#### 使用捕获列表来捕获参数

一个 `lambda` 只有在其捕获列表中捕获它所在函数中的局部变量，才能在 `lambda` 函数体中使用该变量。

```cpp
auto f = [sz] (const string &a) { return a.size() > sz; };
```

- 我们只对 `lambda` 所在函数中定义的非 `static` 变量使用捕获列表，一个 `lambda` 可以直接使用定义在当前函数之外的名字。

- 局部 `static` 变量和所在函数之外名字可以直接使用。

### 10.3.3 lambda 捕获和返回

当定义一个 `lambda` 时，编译器生成一个与 `lambda` 对应的新的未命名的类类型。即：

- 当向一个函数传递一个 `lambda` 时，同时定义了一个新的类型和该类型的一个对象：即传递的参数就是此编译器生成的类类型的未命名对象。

- 当使用 `auto` 定义一个用 `lambda` 初始化的变量时，定义了一个从 `lambda` 生成的类类型的对象。

默认情况下，从 `lambda` 生成的类都包含一个所捕获变量的数据成员。

#### 值捕获

值捕获的变量在 `lambda` 函数被创建时拷贝，而不是调用时拷贝。

```cpp
int val = 42;
auto f = [val] { return val; };
val = 3;
int i = f(); // i = 42
```

#### 引用捕获

需要保证调用 `lambda` 函数的时候被引用捕获的对象是存在的。

我们不能拷贝 `istream` 或者 `ostream` 对象，所以捕获 `is` 或者 `os` 的唯一方法就是捕获其引用。

例如：

```cpp
for_each(v.cbegin(), v.cend(), [&os](const string &s){ os << s << " "; });
```

如果函数返回一个 `lambda`，与函数不能返回一个局部变量的引用类似，`lambda` 也不能包含引用捕获。

一般来说，应尽量减少捕获的数据量，尽可能的避免捕获指针或者引用。

#### 隐式捕获

可以让编译器中根据 `lambda` 中的代码来推断我们使用哪些变量。

在捕获列表中写一个 `&` 或者 `=` 来告诉编译器捕获方式：

```cpp
auto it = find_if(v.cbegin(), v.cend(), [=](const string& s) { return s.size() > sz; });
// sz 为隐式捕获，采用值捕获的方式
```

可以混合使用显式捕获和隐式捕获，捕获列表中第一个元素必须是 `=` 或者 `&`：

```cpp
for_each(v.begin(), v.end(), [=, &os](const string& s) { os << s << " ";});
```

此外必须要求显式捕获的变量和隐式捕获的变量采用不同的方式（值捕获，引用捕获）

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g81c3vnfn7j20so0hejxn.jpg)

#### lambda 修改值捕获参数

如果要改变一个被捕获的变量的值，需要在参数列表后加上关键字 `mutable`：

```cpp
int val = 42;
auto f = [val]() mutable { return ++val; };
cout << f() << endl; // 43
f();
cout << f() << endl; // 45
cout << val << endl; // 42
```

#### 指定 lambda 返回类型

默认情况下，如果一个 `lambda` 函数体包含 `return` 之外的任何语句，则编译器假定此 `lambda` 返回 `void`。

例如，对于 `transformer` 将序列中的每个复数替换成其绝对值

```cpp
transformer(v.begin(), v.end(), v.begin(), [](int i) { return i<0 ? -i : i; });
```

若改为等价的 if 语句，则产生编译错误，编译器推断返回类型为 `void`，实际却返回了一个 `int`

```cpp
transformer(v.begin(), v.end(), v.begin(), [](int i) {
    if (i < 0) return -i;
    else return i;
});
```

若要指定返回类型，必须使用 **尾置返回类型**：

```cpp
transformer(v.begin(), v.end(), v.begin(),
            [](int i) -> int {
                if (i < 0) return -i;
                else return i;
            });
```

### 10.3.4 参数绑定

对于只在一两个地方使用的简单操作，`lambda` 表达式是最后用的。

- 如果 `lambda` 的捕获列表为空，我们通常可以用函数替代他。

- 如果捕获了局部变量，则不容易被函数替换，有些函数只接受一元谓词。

#### bind 函数

标准库 `bind` 函数定义在头文件 `functional` 中，可以将它看作一个通用的函数适配器，接受一个可调用对象，生成一个新的可调用对象来适配原对象的参数列表。

一般形式：

`auto new_callable = bind(callable, arg_list);`

当我们调用 `new_callable` 的时候，会调用 `callable` 并传递给它 `arg_list` 中的参数。

其中 `arg_list` 中可能包含 `(_1, ..., _2, ..., _5, ..., _3)` 其中 `_n` 代表 `new_callable` 的第n个参数。

例子：

```cpp
bool check_size(const string &s, string::size_type sz)
{
    return s.size() > sz;
}

auto check_str_than4 = bind(check_size, placeholders::_1, 4);
string s1 = "hello";
cout << boolalpha << check_str_than4(s1) << endl; // true
```

如上所示，`bind` 函数将 `check_size` 函数转换为只有一个参数，第二个参数设置为4，可以当作一元谓词调用。

此外，`_n` 定义在 `std::placeholders` 命名空间中。

##### 用 bind 重排函数顺序

例如对于函数 `isShorter`:

```cpp
bool isShorter(const string& s1, const string& s2)
{
    return s1.size() < s2.size();
}

sort(words.begin(), words.end(), isShorter;  // 按照字符串从短到长排序
sort(words.begin(), words.end(), bind(isShorter, _2, _1)); // 按字符串从长到短排序
// 比较两个元素 A B 的时候，调用 isShorter(B, A)
```

##### 使用 ref 传递给 bind 引用

`bind` 对参数进行拷贝，若要传递给 `bind` 函数一个 `ostream`，需要使用标准库 `ref` 函数：

```cpp
ostream& print(ostream &os, const string& s, char c)
{
    os << s << c;
    return os;
}

for_each(words.begin(), words.end(), bind(print, ref(cout), _1, ' '));
```