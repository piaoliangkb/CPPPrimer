<!-- TOC -->

- [第十二章 动态内存](#第十二章-动态内存)
    - [12.1 动态内存与智能指针](#121-动态内存与智能指针)
        - [12.1.1 shared_ptr 类](#1211-shared_ptr-类)
            - [初始化方式](#初始化方式)
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
        - [12.1.5 unique_ptr](#1215-unique_ptr)
            - [unique_ptr 的操作](#unique_ptr-的操作)
            - [初始化 unique_ptr](#初始化-unique_ptr)
            - [unique_ptr 不支持拷贝或赋值](#unique_ptr-不支持拷贝或赋值)
            - [传递 unique_ptr 参数和返回 unique_ptr](#传递-unique_ptr-参数和返回-unique_ptr)
            - [向 unique_ptr 传递删除器](#向-unique_ptr-传递删除器)
        - [12.1.6 weak_ptr](#1216-weak_ptr)
            - [weak_ptr 的操作](#weak_ptr-的操作)
            - [初始化和访问](#初始化和访问)
            - [检查指针类](#检查指针类)
    - [12.2 动态数组](#122-动态数组)
        - [12.2.1 new 和数组](#1221-new-和数组)
            - [定义数组](#定义数组)
            - [初始化动态分配对象的数组](#初始化动态分配对象的数组)
            - [动态分配一个空数组是合法的](#动态分配一个空数组是合法的)
            - [释放静态数组](#释放静态数组)
            - [智能指针和动态数组](#智能指针和动态数组)
            - [指向数组的 unique_ptr 的操作](#指向数组的-unique_ptr-的操作)
            - [用 shared_ptr 管理动态数组](#用-shared_ptr-管理动态数组)
        - [12.2.2 allocator 类](#1222-allocator-类)
            - [allocator 类](#allocator-类)
            - [allocator 类的操作](#allocator-类的操作)
            - [allocator 分配未构造的内存](#allocator-分配未构造的内存)
            - [拷贝和填充未初始化的内容](#拷贝和填充未初始化的内容)
            - [练习 12.26：使用 allocator](#练习-1226使用-allocator)
    - [12.3 文本查询程序](#123-文本查询程序)
        - [12.3.1 文本查询程序设计](#1231-文本查询程序设计)

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

#### 初始化方式

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

### 12.1.5 unique_ptr

`unique_ptr` 拥有它所指向的对象，且它只能指向一个给定的对象。所以当 `unique_ptr` 被销毁的时候，它所指向的对象也被销毁。

#### unique_ptr 的操作

操作 | 含义
--- | ---
unique_ptr<T> u1 | 空的 uniquel_ptr，使用 delete 来释放指针
unique_ptr<T, D> u2 | 空的 unique_ptr，使用一个类型为 D 的可调用对象来释放它的指针
unique_ptr<T, D> u(d) | 空的 unique_ptr，用类型为 D 的对象 d 来代替 delete
u = nullptr | 释放 u 指向的对象，将 u 置为空
u.release() | 放弃对指针的控制权，返回指针，将 u 置为空，但是不会释放 u 指向的对象
u.reset() | 释放 u 指向的对象，将 u 置为空
u.reset(q) | 释放 u 指向的对象，令 u 指向内置指针 q
u.reset(nullptr) | 释放 u 指向的对象，置为 nummptr

#### 初始化 unique_ptr

与 `shared_ptr` 不同，没有类似 `make_shared` 的标准库函数返回一个 `unique_ptr`。

- 定义一个 `unique_ptr`，需要将其绑定到一个 `new` 返回的指针上，必须采用直接初始化：

```cpp
unique_ptr<double> p1; // 指向一个 double 的 unique_ptr
unique_ptr<int> p2(new int(42)); // 指向一个值为 42 的 int
```

#### unique_ptr 不支持拷贝或赋值

`unique_ptr`拥有它指向的对象，所以不支持普通的拷贝或者赋值操作。（例外在下一个部分）

可以调用 `release()` 或者 `reset()` 方法将指针的所有权从一个 `unique_ptr` 转移给另一个：

```cpp
// p1.release() 方法将 p1 置空，返回指向的对象
unique_ptr<string> p2(p1.release()); 

// p2 释放了自身所指向的对象，并指向参数的返回值
// 参数为 p3.release()，p3 放弃对指针的控制权，返回指针，并将 p3 置为空
unique_ptr<string> p3(new string("text"));
p2.reset(p3.release());
```

- `release` 返回的指针通常用来初始化另一个智能指针或给另一个智能指针赋值。如果我们不用另一个智能指针来保存 `release` 返回的指针，我们的程序就要负责资源的释放：

```cpp
auto p = p2.release();
delete p;
```

#### 传递 unique_ptr 参数和返回 unique_ptr

不能拷贝 `unique_ptr` 有一个例外，就是我们 **可以拷贝或者赋值一个将要被销毁的 `unique_ptr`**。

- 最常见的例子是从函数返回一个 `unique_ptr`:

```cpp
unique_ptr<int> clone(int p){
    return unique_ptr<int>(new int(p));
}
```

- 返回一个局部对象的拷贝：

```cpp
unique_ptr<int> clone(int p) {
    unique_ptr<int> ret(new int(p));

    return ret;
}
```

#### 向 unique_ptr 传递删除器

默认情况下 `unique_ptr` 使用 `delete` 释放它指向的对象。

重载一个 `unique_ptr` 中的删除器会影响到 `unique_ptr` 类型以及如何构造该类型的对象。

必须在尖括号中的指向类型之后提供删除器类型：

```cpp
unique_ptr<objT, delT> p(new objT, func);
```

上述定义含义为：

- p 指向一个类型为 objT 的对象，并使用一个类型为 delT 的对象释放 objT 对象；

- 销毁时会调用一个名为 `func` 的 delT 类型对象。

例如：

```cpp
connection c = connect(&d);
unique_ptr<connection, decltype(end_connection)*>
    p(&c, end_connection);

// 当出作用域时，connection 会被正常关闭
```

### 12.1.6 weak_ptr

`weak_ptr` 是一种不控制所指对象生存期的智能指针，指向由一个 `shared_ptr` 管理的对象。

- 将一个 `weak_ptr` 绑定到一个 `shared_ptr` 不会改变其引用计数。

#### weak_ptr 的操作

操作 | 含义
--- | ---
weak_ptr<T> w | 空 weak_ptr
weak_ptr<T> w(sp) | 该 weak_ptr 指向与 sp 指向对象相同；T必须能够转换为 sp 指向的类型
w = p | p 可以是一个 shared_ptr 或者 weak_ptr
w.reset() | 将 w 置空
w.use_count() | 与 w 共享对象的 shared_ptr 的数量
w.expired() | 检查此 weak_ptr 是否过期；若 w.use_count() 为 0，返回 true，否则 false
w.lock() | 若 expired 为 true，返回一个空的 shared_ptr；否则返回一个指向 w 的对象的 shared_ptr

#### 初始化和访问

使用 `shared_ptr` 来初始化一个 `weak_ptr`：

```cpp
auto p = make_shared<int>(20);
weak_ptr<int> wp(p);
```

使用 `weak_ptr` 时，由于对象可能不存在，不能直接访问，需要使用 `w.lock()` 检查对象是否存在：

```cpp
if (shared_ptr<int> np = wp.lock())
{
    // 如果 np 不为空，则进入循环
    // 循环中可以使用 np 访问共享对象
}
```

```cpp
auto p = make_shared<int>(20);
weak_ptr<int> wp(p);

if (auto np = wp.lock())
{
    cout << np.use_count() << endl; // 2
    cout << *np << endl;            // 20
}
```

#### 检查指针类

为 StrBlob 类定义一个伴随指针类，指针类将命名为 StrBlobPtr，保存一个 weak_ptr，指向 StrBlob 的 data 成员。

见练习 12.19 - 12.22

## 12.2 动态数组

C++ 提供了两种一次性分配一个对象数组的方法：

- 使用 `new` 表达式

- 使用标准库的 `allocator` 类，将内存分配和初始化分离

使用容器的类可以使用默认版本的拷贝、赋值、析构操作。分配动态数组的类必须定义自己版本的操作，在拷贝、复制、销毁对象时管理所关联的内存。

### 12.2.1 new 和数组

#### 定义数组

使用 `new` 分配一个数组，需要在类型名之后跟一对方括号，方括号中的大小必须是整形，不必是常量：

```cpp
int *arr = new int[20];
```

或者使用类型别名代表数组类型：

```cpp
typedef int arr[24];
// or
using arr = int[24];

int *p = new arr;
```

此处 `p`, `arr` 都是数组元素类型的指针。

若 `new` 表达式失败，不会分配任何内存，会抛出一个 `bad_array_new_length` 的异常，定义在头文件 `new` 中。

不能用 `auto` 分配数组。

#### 初始化动态分配对象的数组

- 默认情况下，`new` 分配的对象都是默认初始化：

```cpp
int *pia = new int[10];    // 10 个未初始化的 int
int *psa = new string[10]; // 10 个空 string
```

- 值初始化，在数组大小之后跟一对空括号：

```cpp
int *pia2 = new int[10]();   // 10 个值初始化为 0 的int
int *psa2 = new string[10]();// 10 个空 string
```

- C++11 中的列表初始化

前几个给定的元素使用初始化器初始化，剩余的值初始化

```cpp
int *pia3 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
string *psa3 = new string[10]{"a", "an", "the", string(3, 'x')};
```

#### 动态分配一个空数组是合法的

- 不能创建一个大小为 0 的静态数组对象，但当 n 等于 0 时，调用 `new[0]` 是合法的：

用 `new` 分配一个大小为 0 的数组时，`new` 返回一个合法的非空指针：

- 可以像使用尾后迭代器一样使用这个指针

- 可以用指针进行比较操作

- 可以向此指针加上 0，或者从此指针减去自身从而得到 0.

- 不能对指针解引用，因为不指向任何元素。

```cpp
size_t n = get_size();
int *p = new int[n];
for (int *q = p; q != p+n; ++q)
{
    // ...
}
```

如上所示，若 `get_size()` 返回0，循环体不会执行。

#### 释放静态数组

为了释放静态数组，我们使用一种特殊形式的 `delete`——在指针前加上一个空方括号对：

```cpp
delete p;    // p 指向一个动态分配的对象或为空
delete [] p; // p 指向一个动态分配的数组或为空
```

其中，数组中的元素按照 **逆序销毁**。

若：

1. `delete` 一个指向数组的指针时忽略了方括号；

2. `delete` 一个指向单一对象的指针时使用了方括号：

则行为是未定义的。（编译器可能不会给出警告）

#### 智能指针和动态数组

可以用一个 `unique_ptr` 管理动态数组：

```cpp
unique_ptr<int[]> up(new int[10]);
up.release();  // 自动调用 delete[] 销毁其指针
```

当 up 销毁它管理的指针时，会自动使用 `delete[]` 。指向普通对象的 `release()` 操作不会归还对应的内存。

- unique_ptr 指向一个数组时，不能使用点和箭头运算符。因为指向的是数组而不是单个对象

- 可以使用下标运算符来访问数组中的元素 ： `auto i = up[1];`

#### 指向数组的 unique_ptr 的操作

指向数组的 unique_ptr 不支持成员访问运算符（点和箭头），其他 unique_ptr 的操作不变。

操作 | 含义
--- | ---
unique_ptr<T[]> u | u 指向一个可以动态分配的数组
unique_ptr<T[]> u(p) | u 指向内置指针 p 所指向的动态分配的数组。p 必须能够转换为类型 T*
u[i] | 下标访问对象

#### 用 shared_ptr 管理动态数组

shared_ptr 不直接支持管理动态数组，若要使用 shared_ptr，必须提供自己定义的删除器：

```cpp
shared_ptr<int> sp(new int[10], [](int *p) { delete[] p;});
sp.reset();  // 若 sp 是唯一的指向该内存的 shared_ptr ，则释放这块内存
```

若未提供删除器，则 shared_ptr 使用 delete 方法销毁它指向的对象，行为是未定义的。

shared_ptr 不支持下标运算符，也不支持指针的算术运算，访问数组的方法：

```cpp
for (size_t i = 0; i != 10; ++i)
{
    *(sp.get() + i) = i;
}
```

需要用 `get()` 方法获取内置指针。

### 12.2.2 allocator 类

- `new` 方法将内存分配和对象构造组合在了一起。`delete` 方法将对象析构和内存释放组合在一起。

- 标准库 `allocator类` 定义在头文件 `memory` 中，它帮助我们将内存分配和对象构造分离开来。

#### allocator 类

allocator 是一个模板，必须知名这个 allocator 可以分配的对象类型：

```cpp
allocator<string> alloc;
auto const p = alloc.cllocate(n);  // 分配 n 个未初始化的 string
```

#### allocator 类的操作

操作 | 含义
--- | ---
allocator<T> a | 定义一个名为 a 的 allocator 对象，可以为类型为 T 的对象分配内存
a.allocate(n) | 分配一段为构造的内存，保存 n 个 T 对象
a.deallocate(p, n) | 释放从 p 中地址开始的内存，这块内存保存了 n 个类型为 T 的对象；p 是由 allocate 返回的指针，且 n 必须是 p 创建时候的大小；调用 deallocate 之前，必须对内存中创建的对象调用 destroy
a.construct(p, args) | p 指向一块原始内存：arg 被传递给类型为 T 的构造函数，用来在 p 指向的内存中构造一块对象
a.destroy(p) | 对 p 指向的对象执行析构函数

#### allocator 分配未构造的内存

```cpp
auto q = p;  // q 指向最后的构造的元素之后的位置
alloc.construct(q++);  // *q 为空字符串
alloc.construct(q++, 10, 'c');  // *q 为 cccccccccc
alloc.construct(q++, "hi");     // *q 为 hi
```

- 为了使用 `allocate` 返回的内存，必须用 `construct` 构造对象。使用未构造的内存，行为是未定义的。

当使用完对象后，必须对每个构造的元素调用 `destroy` 来销毁他们：

```cpp
while (q != p)
    alloc.destroy(--q);
```

销毁元素之后才可以释放内存：

```cpp
alloc.deallocate(p, n);
```

#### 拷贝和填充未初始化的内容

标准库为 `allocator` 定义了两个伴随算法，都定义在 memory 中，用来在未初始化内存中创建对象：

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g8c21f8u24j20p40botc8.jpg)

例如，将一个 vector<int> 的内容拷贝到两倍大小的动态内存中，后半部分使用某个元素填充：

```cpp
auto p = alloc.allocate(vec.size() * 2);
auto q = uninitialized_copy(vec.cbegin(), vec.cend(), p); // 返回填充元素之后一个元素的位置
uninitialized_fill_n(q, vec.size(), 20)；  // 后半部分使用 20 填充
```

#### 练习 12.26：使用 allocator

```cpp
int main()
{
    allocator<string> alloc;
    string s;
    int n;

    cout << "allocate size : ";
    cin >> n;
    
    auto const p = alloc.allocate(n);
    auto q = p; 
    
    while (cin >> s && q != p + n)
    {
        alloc.construct(q++, s);
    }

    cout << "initial pointer points to : " << *p << endl;

    while (q != p)
    {
        cout << *(--q) << endl;
        alloc.destroy(q);
    }

    alloc.deallocate(p, n);

    return 0;
}
```

## 12.3 文本查询程序

我们需求是做一个单词查找程序：

1. 在一个给定文件中查询单词

2. 查询结果为单词在文件中出现的次数，以及所在行的列表

3. 结果按照行数升序打印，打印行号和当前行的内容。

### 12.3.1 文本查询程序设计

1. 程序读取文件到一个 vector<string>，文件中的每行保存为 vector 中的一个元素。

2. 使用 istringstream 处理每一行的单词

3. 使用 set 保存单词在文本中出现在哪一行，set 保证有序

4. 使用 map 将一个单词和保存它出现位置的行号 set 关联起来

#### 数据结构

定义一个保存输入文件的类：`TextQuery`

其中包含 `vector` 和 `map`

定义一个查询结果的类： `QueryResult`

#### 类之间共享数据

我们使用 `QueryResult` 类表达查询的结果：包含出现行号的 set 和 这些行对应的文本。

`QueryResult` 和 `TextQuery` 类共享了数据，可以使用 `shared_ptr`。

#### 使用 TexyQuery 类

我们假定查询函数编写为如下形式，则可以大概了解我们的类需要的操作：

```cpp
void runQueries(ifstream &infile)
{
    TextQuery tq(infile);

    while (true) {
        cout << "Please enter word you want to search: ";
        string s;
        cin >> s;
        print(cout, tq.query(s)) << endl;
    }
}
```