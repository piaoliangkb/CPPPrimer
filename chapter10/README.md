<!-- TOC -->

- [第十章 泛型算法](#第十章-泛型算法)
    - [10.1 概述](#101-概述)
    - [10.2 初识泛型算法](#102-初识泛型算法)
        - [10.2.1 只读算法](#1021-只读算法)
            - [accumulate](#accumulate)
            - [equal](#equal)
        - [10.2.2 写容器元素算法](#1022-写容器元素算法)
            - [fill_n](#fill_n)
            - [back_inserter](#back_inserter)
            - [copy](#copy)
            - [repalce && replace_copy](#repalce--replace_copy)
        - [10.2.3 重排容器元素的算法](#1023-重排容器元素的算法)
            - [sort](#sort)
            - [unique](#unique)
    - [10.3 定制操作](#103-定制操作)
        - [10.3.1 向算法传递参数](#1031-向算法传递参数)
            - [谓词](#谓词)
            - [stable_sort](#stable_sort)
        - [10.3.2 lambda 表达式](#1032-lambda-表达式)
            - [find_if](#find_if)
            - [lambda](#lambda)
            - [向 lanbda 传递参数](#向-lanbda-传递参数)
            - [使用捕获列表来捕获参数](#使用捕获列表来捕获参数)
        - [10.3.3 lambda 捕获和返回](#1033-lambda-捕获和返回)
            - [值捕获](#值捕获)
            - [引用捕获](#引用捕获)
            - [隐式捕获](#隐式捕获)
            - [lambda 修改值捕获参数](#lambda-修改值捕获参数)
            - [指定 lambda 返回类型](#指定-lambda-返回类型)
        - [10.3.4 参数绑定](#1034-参数绑定)
            - [bind 函数](#bind-函数)
                - [用 bind 重排函数顺序](#用-bind-重排函数顺序)
                - [使用 ref 传递给 bind 引用](#使用-ref-传递给-bind-引用)
    - [10.4 再探迭代器](#104-再探迭代器)
        - [10.4.1 插入迭代器](#1041-插入迭代器)
        - [10.4.2 iostream 迭代器](#1042-iostream-迭代器)
            - [istream_iterator](#istream_iterator)
            - [ostream_iterator](#ostream_iterator)
        - [10.4.3 反向迭代器](#1043-反向迭代器)
    - [10.5 泛型算法结构](#105-泛型算法结构)
        - [10.5.1 5类迭代器](#1051-5类迭代器)
        - [10.5.2 算法形参模式](#1052-算法形参模式)
    - [10.6 list, forward_list 特定容器算法](#106-list-forward_list-特定容器算法)
            - [splice 成员函数进行拼接操作](#splice-成员函数进行拼接操作)
            - [链表特有的操作会改变容器](#链表特有的操作会改变容器)

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
`stable_sort` | .. | 维持原有元素的顺序，根据谓词进行排序
`partition` | .. | 根据谓词将使得谓词为 true 的成员排在容器前半部分，其他后半部分，返回指向最后一个元素为 true 之后的位置
`stable_partition` | .. | 同 `partition` 重排元素，原始序列元素相对顺序不变
`find_if` | .. | 返回第一个使得谓词返回非0值的元素
`foe_each` | .. | 接受一个可调用对象，并对序列中的所有元素调用该对象
`transformer` | .. | 接受一个输入序列，一个目标位置和一个可调用对象，对输入序列每个元素调用最后一个参数并写结果到目标位置
`count_if` | .. | 接受一个输入序列和一个谓词，计算有多少使得谓词为真的元素
`unique_copy` | .. | 拷贝不重复的元素到目标地址
`reverse` | .. | 反转元素
`reverse_copy` | .. | 反转拷贝到目标地址
`remove_if` | .. | 根据谓词进行删除
`remove_copy_if` | .. | 根据谓词将删除元素后的结果拷贝到目标地址，原容器不变

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

一共有5种可调用对象：

- 函数

- 函数指针 (chapter6.7 p221)

- 重载了函数调用运算符的类 (chapter14.8 p506)

- bind 创建的对象

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

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g81c3vnfn7j20so0hejxn.jpg)

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

## 10.4 再探迭代器

头文件 `iterator` 中还定义了额外几种迭代器：

- 插入迭代器 `insert iterator`

- 流迭代器 `stream iterator`：被绑定到输入或者输出流，用来遍历它们。

- 反向迭代器 `reverse iterator`

- 移动迭代器 `move iterator`：这些迭代器不拷贝其中元素，而是移动他们。

### 10.4.1 插入迭代器

插入器是一个迭代器适配器，接受一个容器，生成一个迭代器。

插入迭代器的三个类型：

- `back_inserter` 使用 `push_back` 的迭代器

- `front_inserter` 使用 `push_front` 的迭代器，元素总是插入到第一个元素之前。

- `inserter` 使用 `insert` 的迭代器，第二个参数为指向给定容器的迭代器，插入到给定迭代器之前。

例如：

```cpp
list<int> lst = {1, 2, 3, 4}, lst1, lst2;
copy(lst.cbegin(), lst.cend(), front_inserter(lst1));  // 4 3 2 1
copy(lst.cbegin(), lst.cend(), inserter(lst2, lst2.begin()));  // 1 2 3 4 
```

为何 `inserter(lst2, lst2.begin())` 所有顺序都是正序？

>[知乎：插入迭代器inserter在copy函数的运行机制是什么？](https://www.zhihu.com/question/38316591)  
>`inserter` 相当于先调用容器的 `insert()` 函数，该函数指向被插入的新元素，然后递增 `insert()` 返回的迭代器，即指向初始给的迭代器。

假如 `it` 是由 `inserter` 生成的迭代器，则 `*it = val;` 与如下代码效果一样

```cpp
it = c.insert(it, val);  // 将 val 插入到 it 之前，将新元素位置赋值给 it
++it;                    // 递增 it 让它指向原来的元素
```

### 10.4.2 iostream 迭代器

#### istream_iterator

- `istream_iterator` 使用 `>>` 读取输入流，要求要读取的类型必须定义了输入运算符

```cpp
istream_iterator<int> int_it(cin); // 从 cin 读取 int
istream_iterator<int> eof;         // 默认初始化为空，可以当作尾后迭代器使用

ifstream in(filename);
istream_iterator<string> str_it(in); // 读取字符串
```

例如从 `cin` 读取数据并放入 `vector`：

```cpp
vector<int> v;
istream_iterator<int> int_it(cin), eof;
while (int_it != eof)
{
    v.push_back(*int_it++);
}
```

或者使用迭代器范围来构造 vector：

```cpp
istream_iterator<int> int_it(cin), eof;
vector<int> vec(int_it, eof);  
```

或者通过算法来对流迭代器读取内容进行求值：

```cpp
istream_iterator<int> int_it(cin), eof;
cout << accumulate(int_it, eof, 0) << endl;
```

- `istream_iterator` 的操作：

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g8282553rgj20sl0blgpd.jpg)

- `istream-iterator` 允许懒惰求值

当绑定迭代器到一个流时，标准库并不保证迭代器立即从流读取数据，当我们使用迭代器的时候才会读取。

标准库保证当我们第一次解引用迭代器之前，从流中读取数据的操作完成。

#### ostream_iterator

- `ostream_iterator` 使用 `<<` ，要求要读取的类型必须定义了输入运算符

- `ostream_iterator` 可选第二参数字符串，输出每个元素之后可以打印该字符串。**字符串必须是一个C风格字符串（字符串字面常量或者以空字符结尾的字符数组的指针）**

- `ostream_iterator` 必须绑定到一个指定的流，不允许空或者表示尾后位置。

- `ostream_iterator` 操作：

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g828ctezmaj20si0a6adc.jpg)

利用 `ostream_iterator` 来输出值的序列：

```cpp
ostream_iterator<int> out_it(cout, " ");
for (auto &i : v)
    *out_it++ = i; // or out_it = i;
cout << endl;
```

当我们向 `out_it` 赋值的时候，可以忽略递增和解引用运算符，因为它们不做任何事情。但是推荐协商，保持与其他迭代器一致。

用 `copy` 打印 vector 中的元素：

```cpp
ostream_iterator<int> out_it(cout, " ");
copy(v.cbegin(), v.cend(), out_it);
// or
copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
```

### 10.4.3 反向迭代器

除了 `forward_list` 之外，其他容器都支持反向迭代器，可以调用 `rbegin`, `rend`, `crbegin`, `crend` 来获得反向迭代器。

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g82alfpmw9j20n108g75k.jpg)

- 反向迭代器需要递减运算符，除了 `forward_list` 之外，标准容器上的其他迭代器都既支持递增运算和递减运算。

例如，逆序排列 vector：

```cpp
sort(vec.rbegin(), vec.rend());
```

对于一个 `,` 分隔的字符列表，查找最后一个元素

```cpp
auto comma = find(line.crbegin(), line.crend(), ',');
cout << string(line.crbegin(), comma) << endl;   // 错误，将逆序打出
```

若要正常打出内容，需要将 `comma` 转换成一个普通弄迭代器，能在容器 `line` 中正向移动。

- 可以通过调用 `reverse_iterator` 的 `base` 成员函数完成转换：

```cpp
cout << string(comma.base(), line.cend()) << endl;
```

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g82au0nicij20jk07dwfe.jpg)

## 10.5 泛型算法结构

### 10.5.1 5类迭代器

算法要求的迭代器操作可以分为5个迭代器类别(iterator category)

![image.png](https://tva1.sinaimg.cn/mw690/7e197809ly1g82bhsnaa5j20t407dac2.jpg)

### 10.5.2 算法形参模式

![image.png](https://tva1.sinaimg.cn/mw690/7e197809ly1g82bovy20qj20dz03sgm9.jpg)

## 10.6 list, forward_list 特定容器算法

通用版本的 `sort` 函数要求随机访问迭代器，但是 `list` 和 `forward_list` 分别提供双向迭代器和前向迭代器，所以不通用。

- `list` 和 `forward_list` 定义了独有的 `sort`, `merge`, `remove`, `unique`

- 对于这两个链表，应该优先使用成员函数版本的算法而不是通用算法，性能好。

`list` 和 `forward_list` 成员函数版本的算法：

- `lst.merge(lst2)` / `lst.merge(lst2, cmp)` 

将来自 lst2 的元素合并入 lst。 lst 和 lst2 都必须是有序的，元素将从 lst2 删除，合并之后 lst2 变为空。默认版本使用 `<` 运算符，第二个版本使用给定的比较操作。

- `lst.remove(val)` / `lst.remove(pred)`

调用 `erase` 删除与给定值相等(==) 的元素或者使得一元谓词成真的每个元素。

- `lst.reverse()`

反转链表

- `lst.sort()` / `lst.sort(cmp)`

使用 `<` 或者 给定的比较操作对元素进行排序

- `lst.unique()` / `lst.unique(pred)`

使用 `erase` 删除同一个值的连续拷贝，第一个版本使用 `==` ，第二个版本使用给定的二元谓词

#### splice 成员函数进行拼接操作

链表数据结构特有的 `splice` 算法

`list.splice(args)` 或者 `flse.splice_after(args)` 的参数：

![image.png](https://tva1.sinaimg.cn/mw690/7e197809ly1g82c51cl0fj20se0cxwjl.jpg)

#### 链表特有的操作会改变容器

链表特有版本的算法与通用算法的一个区别就是：链表版本会改变底层的容器。

>`std::remove` : 通过以满足不移除的元素出现在范围起始的方式，迁移（以移动赋值的方式）范围中的元素进行移除。保持剩余元素的相对顺序，且不更改容器的物理大小。指向范围的新逻辑结尾和物理结尾之间元素的迭代器仍然可解引用，但元素自身拥有未指定值（因为可移动赋值 (MoveAssignable) 的后置条件）。调用 remove 典型地后随调用容器的 erase 方法，它擦除未指定值并减小容器的物理大小，以匹配其新的逻辑大小。

- `remove` 的链表版本会删除指定的元素，`unique` 的链表版本会删除第二个和后继的重复元素。

- `merge` 和 `splice` 会销毁他们的参数。
