<!-- TOC -->

- [第十二章 动态内存](#第十二章-动态内存)
    - [12.1 动态内存与智能指针](#121-动态内存与智能指针)
        - [12.1.1 shared_ptr 类](#1211-shared_ptr-类)
            - [初始化方式：](#初始化方式)
            - [shared_ptr 和 unique_ptr 都支持的操作](#shared_ptr-和-unique_ptr-都支持的操作)
            - [shared_ptr 独有的操作](#shared_ptr-独有的操作)
            - [make_shared 函数](#make_shared-函数)
            - [shared_ptr 的拷贝和赋值](#shared_ptr-的拷贝和赋值)
            - [shared_ptr 自动销毁所管理的对象](#shared_ptr-自动销毁所管理的对象)
            - [shared_ptr 自动释放关联内存](#shared_ptr-自动释放关联内存)
            - [Classes with resources that have dynamic lifetime（类的资源具有动态生存期）](#classes-with-resources-that-have-dynamic-lifetime类的资源具有动态生存期)
            - [定义 StrBlob 类](#定义-strblob-类)
        - [12.1.2 直接管理内存](#1212-直接管理内存)
            - [使用 new 动态分配和初始化对象](#使用-new-动态分配和初始化对象)
                - [默认初始化](#默认初始化)
                - [直接初始化方式（构造，列表初始化）](#直接初始化方式构造列表初始化)
                - [值初始化](#值初始化)
            - [动态分配的 const 对象](#动态分配的-const-对象)
            - [内存耗尽](#内存耗尽)
            - [释放动态内存](#释放动态内存)
            - [内置指针管理的动态对象，生存期直到被释放](#内置指针管理的动态对象生存期直到被释放)
            - [delete 之后重置指针的值](#delete-之后重置指针的值)
        - [12.1.3 shared_ptr 和 new 配合使用](#1213-shared_ptr-和-new-配合使用)
            - [定义和改变 shared_ptr 的方法](#定义和改变-shared_ptr-的方法)
            - [智能指针的 get() 方法](#智能指针的-get-方法)
            - [reset() 和 unique() 方法](#reset-和-unique-方法)
        - [12.1.4 智能指针和异常](#1214-智能指针和异常)
            - [智能指针和哑类](#智能指针和哑类)
            - [使用自己的释放操作](#使用自己的释放操作)
            - [使用智能指针的基本规范](#使用智能指针的基本规范)

<!-- /TOC -->

# 第十二章 动态内存

C++ 程序中的多种对象：

- 全局对象：在程序启动时分配，程序结束时销毁

- 局部自动对象：进入其定义所在的程序块时被创建，离开块时销毁

- 局部 static 对象：第一次使用之前分配，程序结束时销毁

- 动态分配对象：C++ 支持动态分配对象，动态分配的对象的生存期与哪里创建无关，只有显式地被释放，这些对象才会销毁

不同对象使用的内存：

- 静态内存：保存局部 static 对象，类 static 数据成员，定义在任何函数之外的变量；

- 栈内存：定义在函数内的非 static 对象；

- 堆(heap)/自由空间(free store)：用来存储动态分配的对象(dynamically allocate)

分配在静态内存或者栈内存中的对象由编译器自动创建和销毁；栈对象仅在其定义的程序块运行时才存在；static 对象在使用之前分配，程序结束时候销毁。

程序使用动态内存的原因(p404)：

- 程序不知道自己使用多少对象（容器类）

- 程序不知道所需对象的准确类型（chapter15）

- 程序需要在多个对象间共享数据（允许多个对象共享相同的状态）

## 12.1 动态内存与智能指针

- `new` ：在动态内存中为对象分配空间并返回一个指向该对象的指针

- `delete` ：接受一个动态对象的指针，销毁该对象，并释放与之关联的内存。

C++11 在头文件 `memory` 提供了两种智能指针来管理动态对象，智能指针和常规指针的区别是 **自动释放所指向的对象**

- `shared_ptr` 允许多个指针指向同一个对象

- `unique_ptr` 独占所指向的对象

- `weak_ptr` 伴随类，是一种弱引用，指向 `shared_ptr` 所管理的对象

>ref: https://www.zhihu.com/question/26851369  
>智能指针一个很重要的概念是“所有权”，所有权意味着当这个智能指针被销毁的时候，它指向的内存（或其它资源）也要一并销毁。这技术可以利用智能指针的生命周期，来自动地处理程序员自己分配的内存，避免显示地调用delete，是自动资源管理的一种重要实现方式。为什么要引入“弱引用”指针呢？弱引用指针就是没有“所有权”的指针。有时候我只是想找个指向这块内存的指针，但我不想把这块内存的生命周期与这个指针关联。这种情况下，弱引用指针就代表“我指向这东西，但这东西什么时候释放不关我事儿……”


### 12.1.1 shared_ptr 类

智能指针也是模板，默认初始化的智能指针保存着一个空指针：

```cpp
shared_ptr<int> p1;
shared_ptr<vector<int>> p2;
```

#### 初始化方式：

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


#### shared_ptr 和 unique_ptr 都支持的操作

操作 | 含义
--- | ---
`shared_ptr<T> sp;` / `unique_ptr<T> up;` | 空智能指针
`p` | 条件判断，若 p 指向一个对象，返回 true
`*p` | 解引用 p，获得它指向的对象
`p->mem` | 等价于 (*p).mem
`p.get()` | 返回 p 中保存的指针；若智能指针释放了对象，则返回的指针所指向对象也消失
`swap(p, q)` / `p.swap(q)`| 交换 p 和 q 中的指针

#### shared_ptr 独有的操作

操作 | 含义
--- | ---
`make_shared<T>(args)` | 返回一个 shared_ptr，指向一个类型为 T 的对象，使用 args 对对象进行初始化
`shared_ptr<T>p(q)` | p 是 shared_ptr q 的拷贝：递增 q 的计数器，且 q 中所保存的指针必须能够转换为 T*
`p = q` | 要求 p 和 q 都是 shared_ptr ，且保存的指针能够互相转换。递增 q 的引用计数，递减 p 的引用计数
`p.use_count()` | 返回与 p 共享对象的智能指针的数量（速度可能很慢）
`p.unique()` | 若 p 是独占的，即 `p.use_count()` 为1，则返回 true，否则返回 false

#### make_shared 函数

该函数定义在头文件 `memory` 中。

最安全的分配和使用动态内存的方法是调用一个名为 `make_shared` 的标准库函数。此函数在动态内存中分配一个对象并初始化它，返回指向此对象的 `shared_ptr`。

```cpp
shared_ptr<int> p3 = make_shared<int>(42);
shared_ptr<string> p4 = make_shared<string>(10, '9');
shared_ptr<int> p5 = make_shared<int>(); // 值初始化的 int，默认值为0

// 可以使用 auto 来定义
auto p6 = make_shared<vector<string>>(); // p6 指向一个空 vector<string>
```

- `make_shared` 函数用其参数来 **构造** 给定类型的对象；例如：调用 `make_shared<string>` 时传递的参数必须与 `string` 的某个构造函数相匹配；调用 `make_shared<int>` 时传递的参数必须能用来初始化一个 `int`

- 如果不传递任何参数给 `make_shared` ，对象就会进行值初始化。

#### shared_ptr 的拷贝和赋值

每个 `shared_ptr` 都有一个引用计数 (reference count)，一旦计数变为 0，就会自动释放自己所管理的对象。

- 计数递增的情况：

1. 用一个 shared_ptr 初始化另一个 shared_ptr。

2. 将一个 shared_ptr 作为参数传递给一个函数。

3. 一个 shared_ptr 作为函数的返回值。

- 计数递减的情况：

1. 给 shared_ptr 赋予一个新值。

2. shared_ptr 被销毁（一个局部的 shared_ptr 离开其作用域）。

#### shared_ptr 自动销毁所管理的对象

当指向某一个对象的最后一个 shared_ptr 被销毁时，shared_ptr 类会自动销毁此对象，通过 **析构函数(destructor)** 来完成。

析构函数一般用来释放对象所分配的资源。例如，string 的构造函数会分配内存保存字符，析构函数负责释放内存。

shared_ptr 的析构函数会递减它所指向对象的引用计数，如果引用计数变为0，shared_ptr 的析构函数就会销毁对象，并释放它所占用的内存。

#### shared_ptr 自动释放关联内存

当动态对象不再被使用，shared_ptr 类会自动释放动态对象。

```cpp
// 该函数返回一个动态分配的 Foo 类型的对象
// 由于使用了 shared_ptr 保证了内存会被释放
shared_ptr<Foo> factory(T arg)
{
    // ...
    return make_shared<Foo>(arg);
}

// 定义一个函数，使用了 factory 返回的动态分配对象
// 当函数结束时，指针 p 离开了作用域，会递减 p 的引用计数
// 引用计数为 0 的时候，p 被销毁的同时，占用的内存也被释放
void use_factory(T arg)
{
    shared_ptr<Foo> p = factory(arg);
    // ...
}

// 若有其他的 shared_ptr 也指向这块内存，它就不会被释放
// 修改 use_factory 函数，让其返回 p
// 即使 p 离开了作用域，它指向的内存也不会被释放掉
shared_ptr<Foo> use_factory(T arg)
{
    shared_ptr<Foo> p = factory(arg);

    return p; // 向函数调用这返回一个 p 的拷贝，引用计数递增
}
```

- shared_ptr 在无用之后仍然保留的一种可能情况是：将 shared_ptr 存储在容器中，重排容器并且某些元素不被使用。这种情况下需要用 erase 删除不被使用的元素。

#### Classes with resources that have dynamic lifetime（类的资源具有动态生存期）

本节中定义的类使用动态内存是为了让多个对象能共享相同的底层数据。

#### 定义 StrBlob 类

对于一个 StrBlob 类，唯一的数据成员是 `std::shared_ptr<std::vector<std::string>> data;`

```cpp
class StrBlob {
public:
  using size_type = std::vector<std::string>::size_type;

  // 默认构造函数
  StrBlob();
  // 接受一个初始值列表的构造函数
  StrBlob(std::initializer_list<std::string> il);

  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const std::string &t) { data->push_back(t); }
  void pop_back();
  std::string &front() const;
  std::string &back() const;

private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string &msg) const;
};
```

当我们拷贝，赋值，销毁一个 StrBlob 对象时，它的 shared_ptr 成员会被拷贝，赋值和销毁。

即：

- 拷贝一个 shared_ptr 会递增其引用计数

- 将一个 shared_ptr 赋予另一个 shared_ptr 会递增赋值号右侧 shared_ptr 的引用计数，递减左侧 shared_ptr 的引用计数。

- 对于由 StrBlob 构造函数分配的 vector，当最后一个指向它的 StrBlob 对象被销毁时，它会随之被自动销毁。

### 12.1.2 直接管理内存

#### 使用 new 动态分配和初始化对象

几种方式：

默认初始化，直接初始化方式（直接构造，列表初始化），值初始化

##### 默认初始化

`new` 无法为其分配的对象命名，而是返回一个指向该对象的指针。

`int *pi = new int;`

默认情况下，动态分配的对象是 **默认初始化** 的，即：

- 内置类型或者组合类型的对象的值是未定义的； `int *pi = new int;` pi指向未初始化的 int

- 类类型的对象将用默认构造函数进行初始化； `string *ps = new string;` 初始化为空 string

##### 直接初始化方式（构造，列表初始化）

- 传统的构造方式：

```cpp
int *pi = new int(1024); // 传统的构造方式
string *ps = new string(10, '9');
```

- 列表初始化方式：

```cpp
vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6};
```

##### 值初始化

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

#### 动态分配的 const 对象

用 new 来分配 const 对象：

```cpp
const int *cpi = new const int(1024);
const string *cps = new const string;
```

一个动态分配的 const 对象必须进行初始化；若一个类类型定义了默认构造函数，则其 const 动态对象可以隐式初始化。

#### 内存耗尽

- `bad_alloc` 和 `nothrow` 都定义在头文件 `new` 中。

默认情况下，如果 new 不能分配所要求的内存空间，它会抛出一个类型为 `bad_alloc` 的异常。

可以给 new 传递标准库中名为 `nothrow` 的对象来阻止抛出异常：

```cpp
int *p1 = new int;           // 若分配失败，抛出 std::bad_alloc 异常
int *p2 = new (nothrow) int; // 若分配失败，返回空指针
```

这种形式的 new 叫做 **定位 new(placement new)**。

#### 释放动态内存

通过 `delete` 表达式将动态内存归还给系统。其接受一个指针，指向我们要释放的对象：

```cpp
delete p; // p 指向一个动态分配的对象或者空指针
```

`delete` 表达式执行的动作：

1. 销毁给定的指针指向的对象

2. 释放对应的内存

若释放一块并非 new 分配的内存，或者将相同的指针值释放多次，行为是未定义的。

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g88k0xra0jj20gr05zgmy.jpg)

对于上述错误的 delete 表达式，大多数编译器会编译通过。编译器不能分辨一个指针指向的是静态的还是动态分配的对象。也不能分辨一个指针所指向的内存是否已经释放。

#### 内置指针管理的动态对象，生存期直到被释放

若函数返回一个指针指向一个动态分配的对象（使用内置指针），则需要记住释放内存：

```cpp
Foo* factory(T arg)
{
    // ...
    return new Foo(arg);
}

void use_factory(T arg)
{
    Foo *p = factory(arg);
}
// 函数结束后，p离开了作用域
// 但是指向的内存没有被自动释放
```

#### delete 之后重置指针的值

delete 一个指针之后，指针的值变为无效。

虽然指针已经无效，但在很多机器上指针仍然保存着动态内存的地址。

delete 之后，指针就变成了 **空悬指针(dangling pointer)**，即一块曾经保存数据对象但现在已经无效的内存的指针。

避免空悬指针的方法：

- 指针即将离开作用于之前释放掉它关联的内存

- 如果需要保留指针，可以在 delete 之后将 `nullptr` 赋予指针

然而，当有多个指针指向相同的内存时，在 delete 之后重置指针只对当前指针有效，对其他任何指向已经释放内存的指针是没作用的：

```cpp
int *p(new int (42));
auto q = p;      // 指向相同的内存
delete p;        // 此时 p 和 q 都变得无效
p = nullptr;     // p 不再绑定到任何对象，该修改对 q 无效
```

### 12.1.3 shared_ptr 和 new 配合使用

如果我们不初始化一个智能指针，那么就会被初始化成空指针。

可以用 new 返回的指针来初始化智能指针。

```cpp
shared_ptr<double> p1;
shared_ptr<int> p2(new int(42));
```

- 接受指针的智能指针构造函数是 `explicit` 的，所以不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化的方式。

```cpp
shared_ptr<int> p1 = new int(1024);  // error，构造函数是 explicit 的
```

如上所示，右侧是一个内置指针，左侧是智能指针类型，不能转换。必须使用直接初始化方式：

```cpp
shared_ptr<int> p2(new int(1024));
```

#### 定义和改变 shared_ptr 的方法

- `shared_ptr<T> p(q)`：p 管理 **内置指针q** 所指向的对象；

- `shared_ptr<T> p(u)`：p 从 `unique_ptr u` 那里接管了对象的所有权；将 u 置空。

- `shared_ptr<T> p(q, d)`：p 接管了 **内置指针 q** 所指对象的所有权。q 必须能够转换成 `T*` 类型；p 使用可调用对象 d 来代替 `delete`。

- `shared_ptr<T> p(p2, d)`：p 是 **shared_ptr p2** 的拷贝；p 用可调用对象 d 来代替 `delete`。

- `p.reset()`：若 p 是唯一指向其对象的 `shared_ptr`，`reset` 方法会释放此对象。

- `p.reset(q)`：参数 q 是内置指针，将 p 指向 q。否则置为空。

- `p.reset(q, d)`：同上，但是调用 d 而不是 `delete` 来释放 q。

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g898cz3pfnj20qh07e0v4.jpg)

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g898d99b8cj20qh05tabw.jpg)

#### 智能指针的 get() 方法

智能指针类型定义了一个名为 get 的函数，返回一个内置指针，指向智能指针管理的对象。

此函数的目的是为了：向不能使用智能指针的代码传递一个内置指针。且使用 `get()` 返回的指针的代码不能 `delete` 该指针。

- 将一个智能指针绑定到 `get()` 返回的指针上是错误的：

```cpp
shared_ptr<int> p(new int(42)); // p 的引用计数为 1
int *q = p.get();               // 使用 get() 函数返回一个内置指针；不可以对 q 使用 delete
{
    shared_ptr<int> ptr(q);
} // 程序块结束，q 被销毁
int foo = *p;    // p 指向的内存已经被释放了
```

- `get()` 用来将指针的访问权限传递给代码，在确定代码不会 `delete` 指针的情况下使用 get。

```cpp
int main()
{
    auto sp = make_shared<int>(20);
    auto p = sp.get();
    delete p;
    
    // double free or corruption (out)
    // Aborted (core dumped)
    // 程序块结束之后，仍然会释放 sp -> double free

    return 0;
}
```

- 不要用 get 初始化另一个智能指针或者为另一个智能指针赋值。

#### reset() 和 unique() 方法

- 可以用 `reset` 将一个新的指针赋予一个 `shared_ptr`

```cpp
p = new int(1024);  // error
p.reset(new int(1024)); // true，p 指向一个新对象
```

- `reset` 和 `unique` 共用

```cpp
if (!p.unique()) {
    p.reset(new string(*p)); // p 不是所指向对象的唯一用户，为其重新分配一个新的拷贝。
}
*p *= 2;  // 对 p 进行新的操作而不影响之前指向的对象
```

例如：

```cpp
shared_ptr<int> p(new int(42));
auto q(p);

cout << q.use_count() << endl;  // 2
cout << *q << endl;             // 42

if (!q.unique()) {
    q.reset(new int(*q));
}

cout << q.use_count() << endl; // 1
cout << p.use_count() << endl; // 1
```

### 12.1.4 智能指针和异常

使用智能指针，即使程序块过早的结束（发生了异常），智能指针类也能确保在内存不再需要时将其释放：

```cpp
void f()
{
    shared_ptr<int> sp(new int(10));
    // 抛出异常，且没有在 f 中捕获
} // 函数结束时，shared_ptr 仍能自动释放内存
```

而直接管理的内存当发生异常时，管理的内存不会释放。

#### 智能指针和哑类

- 包括所有标准库类在内的C++类都定义了析构函数，负责清理对象使用的资源

- 有些类要求用户显式地释放所使用的资源

例如对于一个网络编程：

```cpp
struct destination;
struct connection;
connection connect(destination*);   // 建立连接
void disconnect(connect);           // 关闭指定的连接

void f(destination &d)
{
    connection c = connect(&d); // 建立一个连接

    // 使用连接，结束时没有关闭连接
}
```

如果 `connection` 类有一个析构函数，就可以在函数结束时，由析构函数自动关闭连接。若没有析构函数，就会发生类似内存泄露的事情。

#### 使用自己的释放操作

当一个 shared_ptr 被销毁时，默认地对自己管理的指针进行 delete 操作。

我们可以自定义一个 **删除器(deleter)** 并当作参数传递给 shared_ptr ，完成对 shared_ptr 中保存的指针进行释放。

`void end_connection(connection *p) { disconnect(*p); }`

将删除器 `end_connection` 当作参数传递给 shared_ptr:

```cpp
void f(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
}
```

当函数 f 推出的时候，p 被销毁，他不会对自己保存的指针执行 `delete`，而是调用 `end_connection`。

#### 使用智能指针的基本规范

- 不使用相同的内置指针值初始化（或者 reset）多个智能指针。

>ref: [知乎：智能指针的陷阱？](!https://www.zhihu.com/question/285728913)

当我们将一个原生指针交给智能指针的时候，这个智能指针被允许认为自己获得了这个原生指针指向资源的独占所有权。即用一个内置指针初始化一个 shared_ptr，会新建一个计数器。

```cpp
int *p = new int();
std::shared_ptr<int> sp1(p);        // sp1 认为自己独占了 p 指向的资源
std::shared_ptr<int> sp2(sp1);      // sp2 与 sp1 共享资源
std::shared_ptr<int> sp3(p);        // sp3 认为自己独占了 p 指向的资源
```

如上所示，当作用域结束之后，sp1, sp2, sp3 指向的资源相同。应当只销毁一次。

但是由于 sp3 的存在，该资源会被销毁两次。会产生未定义行为。

- 不 `delete` `get()` 返回的指针

`get()` 是为了向不能使用智能指针的方法传递一个内置指针，不能使用 `delete` 操作

```cpp
int main()
{
    auto sp = make_shared<int>(20);
    auto p = sp.get();
    delete p;
    
    // double free or corruption (out)
    // Aborted (core dumped)
    // 程序块结束之后，仍然会释放 sp -> double free

    return 0;
}
```

- 若使用 `get()` 返回的指针，当最后一个对应的智能指针销毁之后，你的指针就变为无效了。

- 如果使用智能指针管理的资源不是 `new` 分配的内存，记住传递给它一个删除器。

智能指针销毁的时候默认调用 `delete` 方法，若不是 `new` 分配的内存，没有对应的 `delete` 方法。