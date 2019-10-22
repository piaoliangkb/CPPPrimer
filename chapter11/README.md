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

## 11.3 关联容器操作

如下类型表示关联容器关键字和值的类型：

类型别名 | 含义
--- | ---
`key_type` | 关键字类型
`mapped_type` | 每个关键字关联的类型，只适用于 map
`value_type` | `set` -> `key_type` / `map` -> `pair<const key_type, mapped_type>`

例如：

```cpp
map<string, int>::mapped_type v2;// v2 is int
map<string, int>::value_type v; // v is <const string, int>
set<string>::value_type v1;     // v1 is string
```

### 11.3.1 关联容器迭代器

- `map` 的迭代器解引用是一个 pair

解引用一个关联容器迭代器会得到一个类型为容器的 `value_type` 的值的引用，对 `map` 而言就是一个 `pair` 类型，`first` 成员为 `const` 的关键字，`second` 保存值。

- `set` 的迭代器是 `const` 的

`set` 类型同时定义了 `iterator` 和 `const_iterator` ，但是两种都行都允许只读访问 `set` 中的元素。

与不能改变 `map` 的关键字一样，`set` 的关键字也是 `const` 的。

#### 遍历关联容器

```cpp
auto map_it = word_cnt.cbegin();
while (map_it != word_cnt.cend())
{
    cout << map_it -> first << map_it -> second << endl;
    ++map_it;
}
```

#### 关联容器和算法

- 由于关联容器的关键字是 `const` 的，所以不能使用修改或者重排容器元素的算法。

- 可用于只读取元素的算法，但是这种算法大多都要搜索序列，关联容器中的元素不能通过他们的关键字进行快速查找，效果不好。例如：使用关联容器定义的专用 `find` 函数会比调用泛型函数 `find` 要快。

- 对关联容器使用算法的实际情况是：把他当作源序列，例如 `copy`；或者当作一个目标位置，例如将一个 `inserter` 绑定到一个关联容器。

### 11.3.2 添加元素

#### 向 set 添加元素

可以接受 **一对迭代器** 或者一个 **初始化器列表。**

```cpp
vector<int> v = {1, 2, 2, 2, 3, 4, 5, 5, 5};
set<int> st;
st.insert(v.cbegin(), v.cend());
st.insert({1, 2, 2, 2, 3, 3, 3, 4});
```

#### 向 map 添加元素

向 `map` 添加的元素类型必须是 `pair`。

可以通过 `insert` 添加元素，也可以通过 `emplace` 构造元素。

```cpp
word_cnt.insert({word, 1});
word_cnt.insert(make_pair(word, 1));
word_cnt.insert(pair<string, size_t>(word, 1));
word_cnt.insert(map<string, size_t>::value_type(word, 1));

// emplace
map<string, int> mp;
// mp.emplace(("jerry", 1)); error
// mp.emplace({"tom", 2});   error
mp.emplace(make_pair("tony", 3));
mp.emplace(pair<string, int>("didi", 4));
mp.emplace(map<string, int>::value_type("func", 5));
```

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g869f28g8fj20se0evafg.jpg)

- 返回值是一个 `pair`，首元素是一个迭代器，指向给定关键字的元素；第二个元素是一个 `bool` 值，指示插入是否成功。


#### 向 multiset, multimap 添加元素

例如：建立作者和其所著书籍的映射：

```cpp
multimap<string, string> authors;
authors.insert({"Jason", "the art of computer science"});
authors.insert({"Jason", "introduction to algorithm"});
```

- 对于允许重复关键字的容器，接受单个元素的 `insert` 操作返回一个指向新容器的迭代器。

### 11.3.3 删除元素

关联容器定义了三个版本的 `erase`：

操作 | 含义 | 返回值
--- | --- | ---
`c.erase(k)` | 删除每个关键字为 k 的元素 | 一个 `size_type` 值，被删除的元素的个数
`c.erase(p)` | 删除迭代器 p 指定的元素 | c++11后返回一个指向 p 之后元素的迭代器，若 p 为尾元素，返回 `c.end()` / c++11前返回 `void`
`c.erase(b, e)` | 删除指定范围内的元素 | 返回 e

### 11.3.4 map 的下标操作

`map` 和 `unordered_map` 提供了下标运算符和一个对应的 `at` 函数。

- 对于下标运算符，若关键字不在容器中，会创建一个元素并插入到 `map` 中，关联值则进行值初始化。不适用于 `const map`

- 对于 `at` 运算符，若关键字不在容器中，会抛出一个 `out_of_range` 异常。`const map` 可用

```cpp
map<string, size_t> word_cnt;
word_cnt["Anna"] = 1;
// or word_cnt.at("Anna") 
// at 版本会对参数进行检查，若参数不在 map 中，则抛出一个 out_of_range 异常
```

上述运算过程为：

1. 在 `word_cnt` 这个 `map` 中查找关键字为 `"Anna"` 的元素，没有找到。

2. 将这个新的 `pair` 插入到 `map` 中。关键字是一个 `const string`，为 `"Anna"`；值进行值初始化，本例子中值初始化为 0；

3. 提取出新插入的元素，将值 1 赋予它。

此外：

`set` 不支持下标运算，没含义。

`multimap` 不支持，因为可能有多个值于一个关键字相关联。

#### 使用下标操作的返回值

对一个 `map` 进行下标操作时，会得到一个 `mapped_type` 的对象。

**`map` 的下标运算符返回一个左值**，可以对元素进行读写：

```cpp
cout << word_cnt["Anna"];
++word_cnt["Anna"];
```

### 11.3.5 访问元素

关键容器中进行查找元素的操作：

操作 | 含义 | 适用性
--- | --- | ---
`c.find(k)` | 返回一个迭代器指向第一个关键字为 k 的元素，否则返回尾后迭代器 | ..
`c.count(k)` | 返回关键字等于 k 的元素的数量 | ..
`c.lower_bound(k)` | 返回一个迭代器，指向第一个关键字不小于等于 k 的元素 | 不适用于无序容器
`c.upper_bound(k)` | 返回一个迭代器，指向第一个关键字大于 k 的元素 | 不适用于无序容器
`c.equal_range(k)` | 返回一个迭代器 pair ，表示关键字等于 k 的元素的范围。若 k 不存在，则 pair
 的两个成员均等于 `c.end()` | ..
`c.at(k)` / `c[k]` | 对 map 来说返回对应的 mapped_type 的值 | 下标操作不适用于 `const map` 或 `const unordered_map`

#### 使用 find 代替下标操作

```cpp
if (word_cnt.find("football") == word_cnt.end())
{
    cout << "football not occurs " << endl;
}
```

#### multiset 和 multimap 中查找元素

使用 `find` 和 `count` 来遍历所有具有相同关键字的元素：

```cpp
multimap<string, string> authors = {
    {"Jason", "book1"},
    {"Jason", "book2"},
    {"Jason", "book3"}
};

auto entris = authors.count("Jason");
auto iter = authors.find("Jason");

while (entris--) {
    cout << iter->second << endl;
    ++iter;
    // --entris;
}
```

#### lower_bound 和 upper_bound

- `lower_bound` 返回的迭代器可能指向第一个具有给定关键字的元素；若关键字不在容器中，返回关键字的第一个安全插入点（容器的尾后迭代器）——不影响容器中元素顺序的插入位置。

- `upper_bound` 若查找的元素在容器中关键字最大，返回该容器的尾后迭代器。

使用 `lower_bound` 和 `upper_bound` 实现查找和遍历操作：

```cpp
for (auto beg = authors.lower_bound("Jason"), end = authors.upper_bound("Jason");
beg != end; ++beg)
{
    cout << beg -> second << endl;
}
```

#### equal_range

- `equal_range` 返回一个迭代器 `pair`，若要查找的元素存在，第一个迭代器指向第一个与关键字匹配的位置，第二个迭代器返回最后一个匹配元素之后的位置。

```cpp
for (auto pos = authors.equal("Jason"); pos.first != pos.second; ++pos.first)
{
    cout << pos.first -> second << endl;
}
```

## 11.4 无序容器

C++11 定义了四个无序关联容器，分别为：`unordered_map`, `unordered_set`, `unordered_multmap`, `unordered_multiset`

无序容器使用 **哈希函数** 和关键字类型的 **==** 运算符。

#### 使用无序容器

无序容器的使用和有序容器相同。

#### 桶

无序容器在存储上组织为一组桶，每个桶保存多个元素。

无序容器使用一个哈希函数将元素映射到桶。为了访问一个元素，容器首先计算元素的哈希，指出应该搜索哪个桶。

容器将具有一个特定哈希值的所有元素都保存在相同的桶中。若容器允许重复关键字，那么关键字相同的元素也都在一个桶中。

无序容器的性能依赖于哈希函数的质量，以及桶的数量和大小。

理想情况下，哈希函数将每个特定的值映射到唯一的桶。将不同的关键字映射到相同的桶也是允许的。当一个桶保存多个元素的时候，需要顺序搜索这些元素来进行查找。

#### 无序容器提供的操作

桶的接口

函数 | 功能
--- | ---
c.bucket_count() | 正在使用的桶的数目
c.max_bucket_count() | 容器能容纳的最多的桶的数量
c.bucket.size(n) | 第 n 个桶有多少个元素
c.bucket(k) | 关键字为 k 的元素在哪个桶

桶迭代

操作 | 简介
--- | ---
local_iterator | 用来访问桶中元素的迭代器
const_local_iterator | const 版本
c.begin(n), c.end(n) | 桶 n 的首元素迭代器和尾后迭代器
c.cbegin(n), c.cend(n) | 同上，返回 const_local_iterator

哈希策略

函数 | 功能
--- | ---
c.load_factor() | 每个桶的平均元素数量，返回 float
c.max_load_factor() | 容器试图维护的平均桶的大小，当每个桶的平均元素数量大于当前值时，会添加新的桶
c.rehash(n) | 重组存储，使得 bucket_count >= n, bucket_count > size/max_load_factor
c.reserve(n) | 重组存储，使得容器可以保存 n 个元素而不必 rehash

#### 无序容器对关键字类型的要求

默认情况下，无序容器使用关键字类型的 `==` 运算符来比较怨怒是，还使用一个 `hash<key_type>` 类型的对象来生成每个元素的哈希值。

标准库为内置类型（包括指针），string，智能指针类型提供了哈希模板。

对于自定义类类型，不能直接定义关键字为自定义的类类型的无序容器，我们必须提供自己的 hash 模板版本。

为了能将 `Sales_data` 用作关键字，我们必须提供函数来替代 `==` 运算符和哈希值计算函数：

```cpp
size_t hasher(const Sales_data& item)
{
    return hash<string>() (item.isbn());
}
bool equalOp(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() == rhs.isbn();
}
```

用上述函数来定义一个 `unordered_multiset`

```cpp
using Sales_data_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(equalOp)*>;

// 参数分别为 桶的大小，哈希函数指针，判断`==`函数的指针
Sales_data_multiset bookstore(42, hasher, equalOp);
```

若某个类定义了 `==` 运算符，则可以只重载哈希函数：

```cpp
unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);
```

#### 练习11.37 无序容器有序容器比较

- 无序容器：通过哈希函数和==运算符来组织元素。在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的。在某些应用中，维护元素的序代价非常高，此时无序容器也很有用。使用无序容器通常会有更好的性能。

- 有序容器：通过<运算符来组织元素。定义起来比较简单。根据关键字的顺序访问元素。