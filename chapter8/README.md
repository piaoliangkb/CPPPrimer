<!-- TOC -->

- [第八章 IO类](#第八章-io类)
    - [8.1 IO类](#81-io类)
        - [IO 类型库和头文件](#io-类型库和头文件)
        - [IO 类型间的关系](#io-类型间的关系)
        - [8.1.1 IO对象不能进行拷贝或者赋值](#811-io对象不能进行拷贝或者赋值)
        - [8.1.2 条件状态](#812-条件状态)
            - [查询流的状态](#查询流的状态)
            - [管理条件状态](#管理条件状态)

<!-- /TOC -->

# 第八章 IO类

## 8.1 IO类

### IO 类型库和头文件

头文件 | 类型
---|---
iostream | istream, wistream, ostream, wostream, iostream, wiostream
fstream | ifstream, wifstream, ofstream, wofstream, fstream, wfstream（向文件读写数据）
sstream | istringstream, wistringstream, ostringstream, wostringstream, stringstream, wstringstream（从string读写数据）

- 标准库定义了一组类型和对象来操作 `wchar_t` 类型的数据。

- 宽字符版本的类型和函数的名称都以一个 `w` 开始，例如 `wcin`, `wcout`, `wcerr`。

### IO 类型间的关系

标准库使我们能够忽略不同类型的流之间的差异，这是通过继承机制 (inheritance) 实现的。

例如：

类型 ifstream 和 istringstream 都继承自 istream。我们如何使用 cin getline，就可以如何使用这些对象。

### 8.1.1 IO对象不能进行拷贝或者赋值

进行 IO 操作的函数通常以引用方式传递和返回流，读写一个 IO 对象会改变其状态，因此传递和返回的引用不能是 const 的。

### 8.1.2 条件状态

我们可以控制和访问流的条件状态。

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7442iquh6j20n605dab7.jpg)

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g7442ynphyj20n50au0w5.jpg)

确定一个流对象状态最简单的方法是将它作为一个条件来使用：

```cpp
while (cin >> word) {
    // 进入循环则读取成功
}
```

#### 查询流的状态

将流作为条件使用，我们无法知道具体发生了什么。IO 库定义了一个与机器无关的 iostate 类型，提供了表达流状态的完整功能。

- IO 库定义了4个 iostate 类型的 constexpr 值，表示特定的位模式。可以与位运算符一起来使用一次性检测或者设置多个标志位。

- badbit 系统及错误，例如不可恢复的读写错误。一般 batbit 被置位，流就无法使用了。

- failbit 可恢复错误，例如希望读 int ，但是读到了 char。这种问题可以修正。

- eofbit 到达文件结束位置，eofbit 被置位。此时 failbit 也同时被置位。

- goodbit 的值为0，表示流未发生错误。如果 badbit，failbit，eofbit 任意一个被置位，检测流状态的条件会失败。

标准库还定义了一组函数来查询这些标志位的状态。操作 good 在所有错误位均未置位的情况下返回 true，而 bad，fail，eof 在对应错误位被置位时返回 true。

此外，在 badbit 被置位时，fail 也会返回 true。即：good 和 fail 是确定流的状态的整体方法。

#### 管理条件状态

对于如下一段代码：

```cpp
auto old_state = cin.rdstate();
cin.clear();
process_input(cin);
cin.setstate(old_state);
```

1. 流对象的 rdstate() 成员返回一个 iostate 值，对应流的当前状态。

2. clear 成员是一个重载的成员：不接受参数的版本清楚所有错误标志位（good 返回 true），接受 iostate 参数的版本表示流的新状态。

3. setstate 操作将给定的条件位置位。

带参数的 clear 版本的实例：

```cpp
// 复位 failbit 和 badbit，保持其他标志位不变
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
```