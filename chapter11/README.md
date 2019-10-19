<!-- TOC -->

- [第十一章 关联容器](#%e7%ac%ac%e5%8d%81%e4%b8%80%e7%ab%a0-%e5%85%b3%e8%81%94%e5%ae%b9%e5%99%a8)
  - [11.1 使用关联容器](#111-%e4%bd%bf%e7%94%a8%e5%85%b3%e8%81%94%e5%ae%b9%e5%99%a8)
    - [map](#map)
    - [set](#set)

<!-- /TOC -->

# 第十一章 关联容器

- 关联容器：关联容器中的元素按照关键字来保存和访问。

- 顺序容器：按照元素在容器中的位置来顺序访问和保存。

两个主要的关联容器 `map`, `set`

标准库提供8个关联容器，8个容器的不同体现在三个维度上：

1. 一个 `set` 或者一个 `map`

2. 关键词是否允许重复 (加 `multi` 前缀)

3. 按照顺序保存或者无序保存 (加 `unordered` 前缀)

关联容器的类型如下：

容器名 | 内容 | 头文件
--- | --- | ---
`map` | 关联数组(associative array)：关键字键值对 | `map`
`multimap` | 关键字可重复的 `map` | ..
`set` | 只保存关键字的容器 | `set`
`multiset` | 关键字可重复出现的 `set` | ..
`unordered_map` | 用哈希函数组织的 `map` | `unordered_map`
`unordered_multimap` | 用哈希函数组织的 `map`，关键字可重复 | ..
`unordered_set` | 用哈希函数组织的 `set` | `unordered_set`
`unordered_multiset` | 用哈希函数组织的 `set`，关键字可重复 | ..


## 11.1 使用关联容器

### map

```cpp
map<string, size_t> word_count;
string word;
while (cin >> word) ++word_count[word];

for (const auto &w : word_count) {
    cout << w.first << " occurs " << w.second << " times" << endl;
}
```

上述我们从 `map` 中提取的对象是 `pair` 类型的，它是一个模板类型，保存两个名字为 `first` 和 `second` 的 `public` 成员。

### set

```cpp
set<string> exclude = {"the", "he", "she", "it"};
string word;
while (cin >> word) {
    if (exclude.find(word) != exclude.end()) 
    {
        cout << "found in the set" << endl;
    }
}
```

## 11.2 关联容器概述

- 关联容器都支持 9.2节 中介绍的普通容器操作。

- 不支持顺序容器的位置相关操作，例如 `push_front`, `push_back`。

- 不支持构造函数，或者插入一个元素值的操作。

- 关联容器的迭代器都是双向的。

### 11.2.1 定义关联容器

C++11 中可以将关联容器初始化为另一个同类型容器的拷贝，或者范围初始化。

```cpp
map<string, size_t> word_count = {
    {"hello", 1},
    {"hi", 2},
    {"world", 5}
}; // l列表初始化
set<string> st = {"the", "they", "it", "he"}; // 列表初始化

```

### 11.2.2 关键字类型的要求

- 无序容器关键字要求：chapter11.4 (p396)

- 有序容器关键字：关键字类型必须定义元素比较的方法。标准库使用关键字类型的 `<` 运算符来比较两个关键字。

#### 有序容器的关键字类型

可以向一个算法提供我们自己定义的比较操作：该操作必须定义一个 **严格弱序(strict weak ordering)**：

- 两个关键字不能同时小于对方。`k1 <= k2` 与 `k2 <= k1` 不能同时发生。

- 若 `k1 <= k2` ，`k2 <= k3` ，则 `k1 <= k3`。

- 如果存在两个关键字，任何一个都不小于等于另一个，则这两个关键字是等价的。如果 k1 等价于 k2，且 k2 等价于 k3，那么 k1 必须等价于 k3.

如果两个关键字等价，容器将他们视作相等。

#### 使用关键字类型的比较函数

为了使用自己定义的操作，在定义 `multiset` 的时候我们必须提供两个类型：关键字类型，比较操作类型(函数指针)

例如，对于 `Sales_data` 类，我们定义了比较操作：

```cpp
bool compareISBN(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() < rhs.isbn();
}

multiset<Sales_data, decltype(compareISBN)*> bookstore(compareISBN);
```

上述使用了 `compareISBN` 来初始化 `bookstore` 对象，表示当我们向 `bookstore` 添加元素的时候，通过调用 `compareISBN` 为这些元素进行排序。

### 11.2.3 pair 类型

`pair` 标准库类型定义在 **头文件 `utility`** 中。

- `pair` 的默认构造函数对数据成员进行值初始化。

`pair<string, vector<string>> line;` 

值初始化了空 string 和 空 vector

- 提供初始化器。

`pair<string, vector<string>> line{"first", {"hello", "world"}};`

#### pair 的操作

操作 | 含义
--- | ---
`pair<T1, T2> P;` | value initialized
`pair<T1, T2> p(v1, v2)` | 用 v1 v2 进行初始化
`pair<T1, T2> p = {v1, v2}` | 同上
`make_pair(v1, v2)` | 返回用 v1 v2 初始化的 pair，pair 类型从 v1 v2 推断出来
`p.first` / `p.second` | 返回数据成员
`p1 relop p2` | 关系运算符(<, >, <= , >=) 按照字典序定义
`p1 == p2`/ `p1 != p2` | 利用元素的 `==` 运算符比较

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g83utvololj20w80k2q9r.jpg)

#### 创建 pair 对象

- 若要一个函数返回一个 `pair` 对象，可以对返回值进行列表初始化：

```cpp
pair<string, int> process(vector<string>& v)
{
    if (!v.empty()) return {v.back(), v.back().size()}; // 列表初始化
    else return pair<string, int>();  // 隐式构造
}
```

- 或者显示构造：

`return pair<string, int> (v.back(), v.back().size());`

- 使用 `make_pair` 来生成 `pair` 对象

`return make_pair(v.back(), v.back().size());`

例如，习题11.12，创建 pair 的三种方法：

```cpp
std::string s;
int i;
std::vector<std::pair<std::string, int>> v;
while (std::cin >> s >> i)
{
    // 列表初始化
    v.push_back({s, i});  

    // 显式构造
    v.push_back(std::pair<std::string, int>(s, i));

    // make_pair 生成 pair 对象
    v.push_back(std::make_pair(s, i));

    // 直接构造，避免拷贝，效率高
    v.emplace_back(s, i);
}
```