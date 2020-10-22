<!-- TOC -->

- [第八章 IO类](#第八章-io类)
    - [8.1 IO类](#81-io类)
        - [IO 类型库和头文件](#io-类型库和头文件)
        - [IO 类型间的关系](#io-类型间的关系)
        - [8.1.1 IO对象不能进行拷贝或者赋值](#811-io对象不能进行拷贝或者赋值)
        - [8.1.2 条件状态](#812-条件状态)
            - [查询流的状态](#查询流的状态)
            - [管理条件状态](#管理条件状态)
        - [8.1.3 管理输出缓冲](#813-管理输出缓冲)
            - [刷新输出缓冲区](#刷新输出缓冲区)
            - [unitbuf 操纵符号](#unitbuf-操纵符号)
            - [程序崩溃缓冲区不会刷新](#程序崩溃缓冲区不会刷新)
            - [关联输入和输出流](#关联输入和输出流)
    - [8.2 文件输入输出](#82-文件输入输出)
        - [fstream 的操作](#fstream-的操作)
        - [8.2.1 使用文件流对象](#821-使用文件流对象)
            - [用 fstream 代替 iostream&](#用-fstream-代替-iostream)
            - [成员函数 open 和 close](#成员函数-open-和-close)
            - [自动析构和构造](#自动析构和构造)
        - [8.2.2 文件模式](#822-文件模式)
            - [指定文件模式的限制](#指定文件模式的限制)
            - [以 out 方式打开文件会丢弃已有数据](#以-out-方式打开文件会丢弃已有数据)
    - [8.3 string 流](#83-string-流)
        - [stringstream 的操作](#stringstream-的操作)
        - [使用 istringstream](#使用-istringstream)
        - [使用 ostringstream](#使用-ostringstream)

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

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7442iquh6j20n605dab7.jpg)

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g7442ynphyj20n50au0w5.jpg)

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

其中 `~cin.failbit` 对 failbit 位取反 并与 rdstate() 结果做与运算。结果将 failbit 位置零。

`~cin.badbit` 操作同理。

### 8.1.3 管理输出缓冲

每个输出流都管理一个缓冲区，用来保存程序读写的数据。

对于如下输出语句 `os << "please enter a velue";` 来说，程序可能将其立即打印出来，也可能被操作系统保存在缓冲区中，随后再打印。有了缓冲机制，操作系统就可以将程序的多个输出操作组合成单一的系统级写操作。

导致缓冲刷新的原因：

- 程序正常结束，缓冲刷新作为 main 函数的 return 操作的一部分，程序正常结束时被执行。

- 缓冲区满时。

- 每个输出操作之后，我们可以使用 unitbuf 来设置流的内部状态来清空缓冲区。 cerr 自动设置 unitbuf，所以写到 cerr 的内容都是立即刷新的。

- 一个输出流可能会被关联到另一个流。这种情况下，当读写被关联的流时，关联到的流的缓冲区会被刷新。例如：默认情况下，cin 和 cerr 都关联到 cout。因此读 cin 或写 cerr 都会导致 cout 的缓冲区被刷新。

```c
cin.tie(&cout);   // cin 和 cout 关联

cin.tie(0);    // 解除该流上已存在的捆绑
```

#### 刷新输出缓冲区

- endl ：换行并刷新输出缓冲区

- flush ：刷新缓冲区，不输出额外字符

- ends ：向缓冲区插入一个空字符，然后刷新缓冲区

#### unitbuf 操纵符号

如果每次输出之后都刷新缓冲区，我们可以使用 unitbuf 操纵符号。

nounitbuf 操纵符则重置流，使其恢复正常的系统管理和缓冲区刷新机制。

```cpp
cout << unitbuf;  // 所有输出操作之后都立刻刷新缓冲区
cout << nounitbuf;  // 回归正常的缓冲方式
```

#### 程序崩溃缓冲区不会刷新

一个程序崩溃之后，它所输出的内容很可能停留在输出缓冲区中等待打印。

#### 关联输入和输出流

当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作d都会先刷新关联的输出流。

标准库将 cin 和 cout 关联在一起，所以 cin 读取数据会先刷新 cout 的缓冲区。

tie 函数的两个版本：

- 参数接收一个指向 ostream 的指针，将自己关联到这个 ostream。

```cpp
cin.tie(&cout);     // 标准库自动地将 cin 和 cout 关联在一起

cin.tie(&cerr);     // 将 cin 和 cerr 关联
```

- 不带参数的版本，返回指向输出流的指针

```cpp
ostream *old_tie = cin.tie(nullptr);   // cin 不再与其他流关联
cin.tie(old_tie);         // cin 重新与 cout 关联
```

我们可以将一个 istream 对象关联到 ostream，也可以将一个 ostream 对象关联到另一个 ostream。

每个流同时最多关联一个流，但多个流可以同时关联到一个流上。

## 8.2 文件输入输出

头文件 fstream 定义了三个类型来支持文件 IO：

- ifstream ：从一个给定文件读取数据

- ofstream ：向一个文件写数据

- fstream ：读写给定文件

### fstream 的操作

操作 | 含义
--- | ---
fstream f; | 创建一个未绑定的文件流
fstream f(s); | 创建一个 fstream 并打开名为 s 的文件(s可以是string类型或者指向C风格字符串的指针)，且构造函数是 explicit 的。
fstream f(s, mode); | 按照 mode 方式打开
f.open(s); | 打开名为 s 的文件，并将文件与文件流 f 绑定
f.close(); | 关闭与文件流 f 绑定的文件，返回 void
f.is_open() | 检查与 f 绑定的文件是否成功打开且尚未关闭

### 8.2.1 使用文件流对象

在新 C++ 标准中，文件名既可以是库类型 string 对象，也可以是 C 风格字符数组。

#### 用 fstream 代替 iostream&

在要求使用基类型对象的地方，我们可以使用继承类型的对象来替代。即：接受一个 iostream 类型引用或指针的函数，可以用一个对应的 fstream 或者 stringstream 来代替。

#### 成员函数 open 和 close

open 调用失败，failbit 会被置位。进行 open 是否成功的检测是一个好习惯。

```cpp
ofstream out;
out.open(filename);

if (out) {
    //...
}
```

- open 打开失败，failbit 会被置位。

- open 打开成功，会设置流的状态，good() 变为 true。

#### 自动析构和构造

当一个 fstream 对象离开其作用域的时候，与之关联的文件会自动关闭。

即当一个 fstrem 对象被销毁时，会自动调用 clsoe() 方法。

```cpp
for (auto p = argv + 1; p != argv + argc; ++p)
{
    ifstream input(*p);
    if (input) {
        // process something
    }
    else {
        // ...
    }
}
```

### 8.2.2 文件模式

每个文件流都有一个关联的文件模式(file mode)，用来指出如何使用文件。

文件模式 | 含义
--- | ---
in | 以读方式打开
out | 以写方式打开
app | 每次写操作之前均定位到文件末尾
ate | 打开文件后立即定位到文件末尾
trunc | 截断文件
binary | 以二进制方式进行 IO

每个文件流都有默认的打开方式：

- 与 ifstream 关联的文件使用 in 模式打开。

- 与 ofstream 关联的文件使用 out 模式打开。

- 与 fstream 关联的文件使用 in 和 out 模式打开。

#### 指定文件模式的限制

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g74ymvmvz5j20tj0e0gr9.jpg)

#### 以 out 方式打开文件会丢弃已有数据

默认情况下，我们打开一个 ofstream 时，文件的内容会被丢弃。

阻止清空的方法是同时指定 app 模式：

```cpp
ofstream ofs(filaname, ofstream::app); // 隐含了 ofstream::out 模式
// or
ofstream ofs(filanem, ofstream::app | ofstream::out);
```

- 保留被 ofstream 打开文件中内容的方法是显示指定 app 或者 in 模式。

## 8.3 string 流

ssstream 头文件定义了三个类型来支持内存 IO，这些类型可以向 string 写入数据，从 string 读取数据。

- istringstream 从 string 读取数据

- ostringstream 向 string 写入数据

- stringstream 既可以从 string 读数据也可以向 string 写数据

### stringstream 的操作

操作 | 含义
--- | ---
sstream strm; | strm 是一个未绑定的 stringstream 对象
sstream strm(s); | strm 是一个 sstream 对象，保存 string s 的一个拷贝。该构造函数是explicit的
strm.str() | 返回 strm 保存的 string 的拷贝
strm.str(s) | 将 string s 拷贝到 strm 中。返回 void

- tips: 清空 stringstream 的方法 `ss.str("")`

### 使用 istringstream

考虑这样的数据：

![image.png](https://tva1.sinaimg.cn/large/7e197809ly1g754waa0wgj20gi03kdgb.jpg)

我们如果从 cin 中逐行读取这样的数据，可以使用 istringstream 处理每一行的字符串：

```cpp
struct PersonInfo {
    string name;
    vector<string> phones;
};

string line, word;
vector<PersonInfo> people;
while (getline(cin, line)) {
    PersonInfo info;
    istringstream record(line);
    // 将输入流的值写入到 info.name
    record >> info.name;
    while (record >> word) {
        // 将输入流的值循环写入到 word
        // 即一个用户可能有多个电话号码
        info.phones.push_back(word);
    }
    people.push_back(info);
}
```

### 使用 ostringstream

逐步构造输出并一起打印。

我们可以将输出内容先写入到 ostringstream 中。

如下判断电话号码是否全部合规之后，再打印出来。

```cpp
for (const auto &item: people) {
    ostringstream rightnums, badnums;
    for (const auto &phone: item.phones) {
        if (!valid(phone)) {
            // 将后续的空格和 phone 添加到输出流
            badnums << " " << phone;
        }
        else {
            // 添加到输出流
            rightnums << " " << format(phones);
        }
    }

    if (badnums.str().empty()) {
        cout << item.name << " " << rightnums.str() << endl;
    }
    else {
        cerr << "input error: " << item.name
        << " invalid nums: " << badnums.str() << endl;
    }
}
```