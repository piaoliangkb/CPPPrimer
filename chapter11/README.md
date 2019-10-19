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