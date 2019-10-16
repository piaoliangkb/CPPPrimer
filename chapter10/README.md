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

