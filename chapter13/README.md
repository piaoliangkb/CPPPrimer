<!-- TOC -->

- [第十三章 拷贝控制](#第十三章-拷贝控制)
    - [13.2 拷贝、赋值、销毁](#132-拷贝赋值销毁)
        - [13.1.1 拷贝构造函数](#1311-拷贝构造函数)
            - [合成拷贝构造函数](#合成拷贝构造函数)
            - [拷贝初始化(copy initialization)](#拷贝初始化copy-initialization)
            - [拷贝初始化发生的情况](#拷贝初始化发生的情况)
            - [参数和返回值](#参数和返回值)
            - [拷贝初始化的限制](#拷贝初始化的限制)
            - [编译器可以跳过拷贝构造函数](#编译器可以跳过拷贝构造函数)
            - [练习 13.1 什么是拷贝构造函数，什么时候使用？](#练习-131-什么是拷贝构造函数什么时候使用)
            - [练习13.3 拷贝 StrBlob StrBlobPtr 的时候都会发生什么](#练习133-拷贝-strblob-strblobptr-的时候都会发生什么)
            - [练习13.4 哪里使用了拷贝构造函数](#练习134-哪里使用了拷贝构造函数)
        - [13.1.2 拷贝赋值运算符(copy-assignment operator)](#1312-拷贝赋值运算符copy-assignment-operator)
            - [重载赋值运算符](#重载赋值运算符)
            - [合成拷贝赋值运算符](#合成拷贝赋值运算符)
            - [什么时候调用拷贝构造函数，什么时候调用拷贝赋值运算符](#什么时候调用拷贝构造函数什么时候调用拷贝赋值运算符)
            - [练习13.6 拷贝赋值运算符是什么？什么时候使用？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？](#练习136-拷贝赋值运算符是什么什么时候使用合成拷贝赋值运算符完成什么工作什么时候会生成合成拷贝赋值运算符)
        - [13.1.3 析构函数](#1313-析构函数)
            - [析构函数完成什么工作](#析构函数完成什么工作)
            - [什么时候效用析构函数](#什么时候效用析构函数)
            - [合成析构函数(synthesized destructor)](#合成析构函数synthesized-destructor)
            - [练习13.9 析构函数是什么？合成析构函数完成什么工作？什么时候会生成合成析构函数？](#练习139-析构函数是什么合成析构函数完成什么工作什么时候会生成合成析构函数)
        - [13.1.4 三/五法则](#1314-三五法则)
            - [需要析构函数的类，同时也需要拷贝和赋值操作](#需要析构函数的类同时也需要拷贝和赋值操作)
            - [需要拷贝操作的类也需要赋值操作，反之亦然](#需要拷贝操作的类也需要赋值操作反之亦然)
        - [13.1.5 使用=default](#1315-使用default)
        - [13.1.6 阻止拷贝](#1316-阻止拷贝)
            - [定义删除的函数](#定义删除的函数)
            - [析构函数不能是删除的成员](#析构函数不能是删除的成员)
            - [合成的拷贝控制成员可能是删除的](#合成的拷贝控制成员可能是删除的)
            - [private 拷贝控制](#private-拷贝控制)
    - [13.2 拷贝控制和资源管理](#132-拷贝控制和资源管理)
        - [13.2.1 行为像值的类](#1321-行为像值的类)
            - [拷贝赋值运算符](#拷贝赋值运算符)
        - [13.2.2 定义行为像指针的类](#1322-定义行为像指针的类)
            - [引用计数](#引用计数)
            - [定义一个引用计数的 HasPtr 类](#定义一个引用计数的-hasptr-类)
    - [13.3 交换操作](#133-交换操作)
        - [编写我们自己的 swap 函数](#编写我们自己的-swap-函数)
        - [swap 函数应该调用 swap，而不是 std::swap](#swap-函数应该调用-swap而不是-stdswap)
        - [赋值运算符中使用 swap](#赋值运算符中使用-swap)
    - [13.4 拷贝控制实例](#134-拷贝控制实例)
        - [Message 类](#message-类)
        - [save 和 remove 成员](#save-和-remove-成员)
        - [Message 类的拷贝控制成员](#message-类的拷贝控制成员)
        - [Message 的析构函数](#message-的析构函数)
        - [Message 的拷贝赋值运算符](#message-的拷贝赋值运算符)
        - [Message 的 swap 函数](#message-的-swap-函数)
    - [13.5 动态内存管理类](#135-动态内存管理类)
        - [练习13.43 用 for_each 和 lambda 代替 for 循环](#练习1343-用-for_each-和-lambda-代替-for-循环)

<!-- /TOC -->


# 第十三章 拷贝控制

当定义一个类的时候，我们可以显式或者隐式地指定此类型的对象拷贝，移动，赋值，销毁时做什么。

通过5类特殊的成员函数来控制（称为拷贝控制操作(copy control)）：

- 拷贝构造函数(copy constructor)

- 拷贝赋值运算符(copy-assignment operator)

- 移动构造函数(move constructor)

- 移动赋值运算符(move-assignment operator)

- 析构函数(destructor)

拷贝和移动构造函数定义了用同类型对象初始化另外一个对象的操作。

拷贝和移动赋值运算符定义了将一个对象赋予另一个对象时做什么。

析构函数定义了此类型对象销毁时的操作。

若一个类没定义这些拷贝控制成员，编译器会自动为它提供缺失的操作。

## 13.2 拷贝、赋值、销毁

介绍拷贝构造函数，拷贝赋值运算符，析构函数。

### 13.1.1 拷贝构造函数

如果一个构造函数的第一个参数是自身类型的引用，且任何额外参数都有默认值，则此构造函数是 **拷贝构造函数**：

```cpp
class Foo {
public:
    Foo();           // 默认构造函数
    Foo(const Foo&); // 拷贝构造函数
    // ...
}
```
- 可以定义一个接受非 const 引用的拷贝构造函数，但此参数通常是一个 const 引用。

- 拷贝构造函数通常不是 explicit 的，因为几种情况会被隐式地使用。

#### 合成拷贝构造函数

与合成默认构造函数不同，即使我们定义了其他构造函数，编译器也会为我们合成一个拷贝构造函数。

**合成拷贝构造函数(synthesized copy constructor)用途:**

- 有些类用来阻止我们拷贝该类类型的对象。

- 一般情况，合成的拷贝构造函数会将其参数的成员逐个拷贝到正在创建的对象中（非 static 成员）。

**每个成员的类型决定如何拷贝：**

- 类类型的成员使用拷贝构造函数。

- 内置类型成员直接拷贝。

- 不能直接拷贝数组，但是合成拷贝构造函数会逐元素地拷贝一个数组类型的成员；若元素为类类型，则使用元素的拷贝构造函数进行拷贝。

**例子：**

Sales_data 类的合成拷贝构造函数等价于：

```cpp
class Sales_data {
public:
    Sales_data(const Sales_data&); // 拷贝构造函数
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
}

Sales_data::Sales_data(const Sales_data& orig):
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue) {}
```

上述 `bookNo` 使用了 `string` 的拷贝构造函数，其他内置类型直接拷贝。

#### 拷贝初始化(copy initialization)

- 直接初始化：要求编译器使用普通的函数匹配，选择与我们提供参数最匹配的构造函数

```cpp
string dots(10, '.');
string s(dots);
```

- 拷贝初始化：将右侧运算对象拷贝到正在创建的对象中，可能需要类型转换

```cpp
string s2 = dots;
string null_book = "999-9999-999";
string nines = string(100, '9');
```

拷贝初始化通常使用拷贝构造函数来完成。例外是：如果一个类有一个移动构造函数，则拷贝初始化有时会使用移动构造函数而非拷贝构造函数(chapter13.6.2 p473)。

#### 拷贝初始化发生的情况

- 使用 `=` 定义变量时

- 将一个对象作为实参，传递给一个非引用类型的形参（非引用类型的参数传递）

- 从一个返回类型为非引用类型的函数返回一个对象（函数返回值为非引用类型）

- 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员

- 标准库容器使用 `insert` 或者 `push` 成员，容器对其元素使用拷贝初始化；用 `emplace` 创建的元素进行直接初始化。

#### 参数和返回值

若一个函数返回类型为非引用类型，返回值用来初始化调用方的结果。

拷贝构造函数被用来初始化非引用类类型参数，这一特性解释了为什么拷贝构造函数自己的参数必须是引用类型：

- 若拷贝构造函数的参数不是引用类型，当我们调用拷贝构造函数时，必须拷贝它的实参；

- 为了拷贝实参，我们必须调用拷贝构造函数。

#### 拷贝初始化的限制

有些构造函数是 explicit 的，不能使用拷贝初始化而是使用直接初始化。

```cpp
vector<int> v1(10);  // 直接初始化
vector<int> v1 = 10; // 错误，接受大小参数的构造函数是 explicit 的
```

当传递一个实参或者从函数返回一个值时，因为他们都进行拷贝初始化，所以不能隐式使用一个 explicit 构造函数：

```cpp
void f(vector<int>);

f(10);  // 错误
f(vector<int>(10)); // 正确
```

#### 编译器可以跳过拷贝构造函数

拷贝初始化过程中，编译器可以跳过拷贝/移动构造函数，直接创建对象：

即，允许将代码：

```cpp
string null_book = "999-999-999";
```

改写为：

```cpp
string numm_book("999-999-999");
```

但是，拷贝/移动构造函数必须是存在且可以访问的（不能是 private 的）。

#### 练习 13.1 什么是拷贝构造函数，什么时候使用？

- 什么是拷贝构造函数：

拷贝构造函数 (copy constructor) 是：第一个参数为自身类类型的引用，其他参数都有默认值的构造函数。

- 拷贝构造函数的使用：

发生拷贝初始化的时候，可能会用到拷贝构造函数(copy constructor)或者移动构造函数(move constructor):

1. 使用 `=`

2. 将一个对象传递给一个非引用类型的参数(pass an object as an argument to a parameter of non-reference type)

3. 从一个函数返回一个非引用类型的对象(return an object from a function that has a non-reference returned type)

4. 列表初始化一个数组中的元素或者聚合类(brace initializa the elements in an array or the members of an aggregate class)

5. 一些类类型也使用拷贝初始化初始对象。

#### 练习13.3 拷贝 StrBlob StrBlobPtr 的时候都会发生什么

```cpp
class StrBlob {
    // ...
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr {
    // ...
private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<std::string>> check(size_type,
                                                    const std::string &) const;
};
```

拷贝 StrBlob 的时候，增加 data 的引用计数，因为为 shared_ptr；

拷贝 StrBlobPtr 的时候，不会增加 wptr 的引用计数，因为为 weak_ptr。

#### 练习13.4 哪里使用了拷贝构造函数

```cpp
Point global;
Point foo_bar(Point arg) { // 1
    Point local = arg, *heap = new Point(global); // 2, 3
    *heap = local;  // 使用拷贝赋值运算符
    Point pa[4] = {local, *heap};  // 4, 5
    return *heap;  // 6
}
```

### 13.1.2 拷贝赋值运算符(copy-assignment operator)

类可以控制其对象如何赋值：

```cpp
Sales_data trans, accum;
trans = accum;  // 使用了 Sales_data 的拷贝赋值运算符
```

如果类没有定义自己的拷贝赋值运算符，编译器会为它合成一个。

#### 重载赋值运算符

重载运算符(overloaded operator) 本质上是函数，名字由 `operator` 关键字后接表示要定义的运算符号组成。

所以赋值运算符就是一个名为 `operator=` 的函数，其左侧运算对象绑定到隐式的 `this` 参数。

对于赋值运算符这样的二元运算符来说，其右侧对象作为显式参数传递。

赋值运算符接受一个与其类类型相同的参数，返回类型为指向左侧运算对象的引用：

```cpp
class Foo {
public:
    Foo& operator=(const &Foo);
}
```

标准库通常要求保存在容器中的类型要具有赋值运算符，且其返回值是左侧运算对象的引用。

#### 合成拷贝赋值运算符

如果一个类未定义自己的拷贝赋值运算符，编译器会为它生成一个合成拷贝赋值运算符(synthesized copy-assgnment operator)。

**合成拷贝赋值运算符的作用：**

- 对于某些类，用来禁止该类型对象的赋值

- 将右侧运算对象的每个非 static 成员赋予左侧运算对象的对应成员。通过成员类型的拷贝赋值运算符完成；对于数组类型的成员，逐个赋值数组元素。

Sales_data 的合成拷贝赋值运算符等价于如下：

```
Sales_data& Sales_data::operator=(const Sales_data &rhs) {
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}
```

#### 什么时候调用拷贝构造函数，什么时候调用拷贝赋值运算符

>https://www.zhihu.com/question/30726582

1. 调用拷贝构造函数的时候，是对象不存在的时候：

下面的 b, c 都调用了拷贝构造函数

```cpp
numberd a = numberd(10);
numberd b = a;
numberd c(a);
```

2. 如果是已经存在的对象，则调用拷贝赋值运算符：

```cpp
numberd a(10);
a = numberd(20);
```

#### 练习13.6 拷贝赋值运算符是什么？什么时候使用？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

- 什么是拷贝赋值运算符：

叫做 `operator=` 的函数

- 什么时候使用：

拷贝发生的时候

- 合成拷贝赋值运算符：

合成拷贝赋值运算符将右侧运算对象的每个非 static 成员赋予左侧运算对象的对应成员；对每个成员来说使用成员类型的拷贝赋值运算符来完成；对数组类型的成员，逐个赋值数组元素。

- 什么时候生成合成拷贝赋值运算符：

当一个类没自己定义的时候会生成

### 13.1.3 析构函数

析构函数执行与构造函数相反的操作：

- 构造函数：初始化对象的非 static 数据成员，并可执行其他操作。

- 析构函数：释放对象使用的资源，销毁对象的非 static 成员。

析构函数是类的成员函数，名字为 `~` + 类名 组成，没有返回值，不接受参数，所以也不能重载，一个给定类只有一个析构函数。

```cpp
class Foo {
public:
    ~Foo(); // 析构函数
}
```

#### 析构函数完成什么工作

- 构造函数：成员初始化在函数体执行之前完成，且按照他们在类中出现的顺序初始化

- 析构函数：首先执行函数体，然后销毁成员。成员按照初始化的顺序逆序销毁。通常，析构函数释放对象在生存期分配的所有资源。

析构部分是隐式的，成员销毁时发生的事情依赖于成员类型：

- 类类型：执行类自己的析构函数。

- 内置类型：没有西沟含糊，什么也不需要做。

- 内置指针类型：隐式销毁不会自动 delete 它所指的对象。

- 智能指针：析构阶段被自动销毁。

#### 什么时候效用析构函数

一个对象被销毁时调用：

- 变量离开作用域

- 一个对象被销毁，它的成员被销毁

- 容器（标准库容器或者数组）被销毁时，它的元素被销毁

- 动态分配的对象(dynamically allocated objects)，当指向它的指针使用了 delete 运算符时

- 临时对象，当创建它的完整表达式结束时被销毁

```cpp
{ // this is a new scope
    Sales_data *p = new Sales_data; // p is a build-in pointer
    auto p2 = make_shared<Sales_data>();  // p2 is a shared_ptr
    Sales_data item(*p);  // 使用了拷贝构造函数(copy constructor)
    vector<Sales_data> vec; // local object
    vec.push_back(*p2);  // copy the object which p2 points
    delete p;  // destructor called on the object pointed to by p
} // leave local scope
  // p2 item vec 调用析构函数
  // p2 减少引用计数
  // vec 的元素被销毁
```

- 当指向一个对象的引用或者指针离开作用域时，析构函数不会执行

#### 合成析构函数(synthesized destructor)

对于某些类来说，合成析构函数用来阻止该类型的对象被销毁。否则，合成析构函数的函数体为空。

- 析构函数体自身不直接销毁成员

- 成员在析构函数体之后隐含的析构阶段中被销毁(members are destroyed as part of the implicit destruction phase that follows the destructor body.)

Sales_data 的合成析构函数等价于：

```cpp
Sales_data {
public:
    ~Sales_data() { }
}
```

#### 练习13.9 析构函数是什么？合成析构函数完成什么工作？什么时候会生成合成析构函数？

- 析构函数是什么？

和构造函数相对，析构函数是用来释放类的非 static 对象所拥有的资源的函数。首先执行析构函数的函数体，随后按照成员初始化的逆序销毁对象，释放资源。

- 合成析构函数完成什么工作？

某些类用来阻止该类型的对象被销毁。

某些类函数体为空，用来释放类的非 static 对象的资源。

- 什么时候生成合成析构函数？

没自己定义析构函数的时候。

### 13.1.4 三/五法则

有三个基本方法来控制类的对象的拷贝：拷贝构造函数，拷贝赋值运算符，析构函数。

C++ 新标准可以定义 **移动构造函数** 和 **移动赋值运算符**。

这些操作通常看作一个整体，只定义一个操作，而不需要定义其他操作的情况是很少见的。

#### 需要析构函数的类，同时也需要拷贝和赋值操作

如果一个类需要一个析构函数，它几乎一定需要拷贝构造函数和一个拷贝赋值运算符。

例如：

对于一个 `HasPtr` 类，需要定义一个析构函数来释放 `string *ps` 的内存。

如果我们使用默认的拷贝构造函数和拷贝赋值运算符，那么拷贝一个 HasPtr 类的时候，两个指针会指向相同的地址：

```cpp
HasPtr f(HasPtr hp) {
    HasPtr ret = hp;

    return ret;
}
```

当函数 `f()` 调用结束的时候，ret 和 hp 两个对象都会调用析构函数，导致指针指向的地址被 delete 两次。会发生未定义错误。又例如：

```cpp
HasPtr p("hello");
f(p); // 此时 p 指向的内存不再有效
HasPtr q(p); // p 和 q 都指向无效内存
```

#### 需要拷贝操作的类也需要赋值操作，反之亦然

有些类可以只需要拷贝或者赋值操作，不需要析构函数。

如果一个类需要一个拷贝构造函数，几乎可以确定其也需要一个拷贝赋值运算符。反之亦然。

例子：

![image.png](https://ws1.sinaimg.cn/large/7e197809ly1g8n6vzjacsj20rh03zacb.jpg)

### 13.1.5 使用=default

可以通过将拷贝控制成员定义为 `=default` 来显式的要求编译器生成合成的版本。

```cpp
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const Sales_data&) = default;
    Sales_data& operator=(const Sales_data&);
    ~Sales_data() = default;
}
```

- 当我们在类内用 `=default` 修饰成员的声明时，合成的函数将隐式地声明为 **内联的**。

- 如果我们不希望合成的成员是内联函数，应该只对成员的类外定义使用 `=default`。

### 13.1.6 阻止拷贝

iostream 类阻止了拷贝，以避免多个对象写入或者读取相同的 IO 缓冲。

#### 定义删除的函数

C++ 新标准下，我们可以将拷贝构造函数和拷贝赋值运算符定义为 **删除的函数(deleted function)** 来阻止拷贝。

- 删除的函数(deleted function)：虽然声明了但是不能以任何方式使用的函数。

- 在函数的参数列表 `=delete` 来指出我们希望将他们定义为删除的：

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete; // 阻止拷贝(拷贝构造函数)
    NoCopy &operator=(const NoCopy&) = delete;  // 阻止赋值(拷贝赋值运算符)
    ~NoCopy() = default;
}
```

- `delete` 必须出现在函数第一次声明的时候，`=default` 不一定出现在第一次声明的地方。

- 可以对任何函数指定 `=delete`，但是只能对编译器可以合成的默认构造函数或拷贝控制成员使用 `=default`。删除函数有时可以用来引导函数匹配过程。

#### 析构函数不能是删除的成员

- 如果析构函数被删除，就无法销毁此类型的对象。

- 对于删除了析构函数的类型，不能定义这种类型的变量或成员，但是可以动态分配这种类型的对象，但是不能释放这些对象。

#### 合成的拷贝控制成员可能是删除的

如果一个类有数据成员不能默认构造、拷贝、赋值、销毁，则对应的成员函数将定义为删除的。

1. 一个 **成员** 有 **删除** 的或者 **不可访问的析构函数**，会导致合成的 **默认和拷贝构造函数** 被定义为删除的。否则可能会创建出无法销毁的对象。

2. 具有 **引用成员** 或 **无法默认构造的 const 成员的类**，编译器不会为其合成默认构造函数。如果一个类有 const 成员，则它不能使用合成的拷贝赋值运算符。（我们可以将一个新值赋予一个引用成员，但是这样做的结果改变的是引用的对象的值，而不是引用本身）

#### private 拷贝控制

新标准发布之前，类是通过将其拷贝构造函数和拷贝赋值运算符声明为 private 来组织拷贝：

```cpp
class PrivateCopy {
    // 第一个访问说明符之前的成员是 private 的
    PrivateCopy(const PrivateCopy&);
    PrivateCopy& operator=(const PrivateCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
}
```

上述拷贝构造函数和拷贝赋值运算符是 private 的，用户代码不能拷贝该对象，但是友元和成员函数仍然可以拷贝对象。

为了防止友元和成员函数进行拷贝，我们将拷贝控制成员声明为 private，但是不定义他们。

声明但是不定义一个成员函数是合法的，通过声明但是不定义一个 private 的拷贝构造函数：

1. 试图拷贝对象的用户代码将在编译阶段被标记为错误。

2. 成员函数或者友元函数中的拷贝操作将会导致链接时错误。

## 13.2 拷贝控制和资源管理

通常，管理类外资源的类必须定义拷贝控制成员。

一旦一个类需要析构函数，那么它几乎肯定也需要一个拷贝构造函数和一个拷贝赋值运算符。

可以使类的行为看起来像一个值或者像一个指针：

- 类的行为像一个值：它应有自己的状态，当我们拷贝一个像值的对象时，副本和原对象是完全独立的。改变副本不会改变原对象的状态。

- 类的行为像一个指针：类之间共享状态，当拷贝一个像指针的类时，副本和原对象使用相同的底层数据。改变副本也会改变原对象。

### 13.2.1 行为像值的类

为了提供类值的行为，对于类管理的资源，每个对象都应该拥有一份自己的拷贝。

对于 HasPtr 类：

```cpp
class HasPtr {
public:
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}

    HasPtr& operator=(const HasPtr& rhs) {
        auto temp = new std::string(*rhs.ps); // 先拷贝右侧的值，可以处理自赋值情况
        delete ps;
        ps = temp;
        i = rhs.i;
        
        return *this;
    }

    ~HasPtr() { delete ps; }

    std::string *ps;
    int i;
};
```

#### 拷贝赋值运算符

为了处理自赋值情况，并能确保异常发生时代码也是安全的，需要先拷贝右侧对象。完成拷贝之后，释放左侧运算对象的资源。即：

```cpp
HasPtr& operator=(const HasPtr& rhs) {
    auto temp = new std::string(*rhs.ps); // 先拷贝右侧的值，可以处理自赋值情况
    delete ps;
    ps = temp;
    i = rhs.i;
    
    return *this;
}
```

**编写赋值运算符时需要注意的两点：**

- 如果将一个对象赋予它自身，赋值运算符必须能正常工作。

一个好的模式是先将右侧运算对象拷贝到一个局部临时对象中。拷贝完成后，销毁左侧运算对象的现有成员就是安全的了。

- 大多数赋值运算符组合了析构函数和拷贝构造函数的工作。

一个错误的编写赋值运算符的方法：

```cpp
HasPtr& operator=(const HasPtr& rhs) {
    delete ps;
    ps = new std::string(*rhs.ps);
    i = rhs.i;
    
    return *this;
}
```

如果 rhs 和左侧运算对象相同，那么 `delete ps;` 会释放 `*this` 和 `rhs` 指向的 string。所以接下来的访问 `*rhs.ps` 的行为是未定义的。

### 13.2.2 定义行为像指针的类

对于行为类似指针的类，需要定义拷贝构造函数和拷贝赋值运算符，来拷贝指针成员本身而不是它指向的内容。

此外，仍然需要析构函数来释放构造函数分配的内存。而且，必须是最后一个指向对应内存的对象被销毁之后，才可以释放内存。

- 可以使用 shared_ptr 来管理类中的资源，类的析构函数负责释放资源。

- 直接管理资源，需要使用引用计数。

#### 引用计数

引用计数的工作方式：



计数器不能直接作为 HasPtr 的成员，例如：

```cpp
HasPtr p1("hiya!");
HasPtr p2(p1);
HasPtr p3(p1);
```

执行结束后，p1, p2, p3 都指向相同的 string。若计数器作为 HasPtr 的成员，那么当 p1 赋值给 p3 时，可以递增 p1 中的计数器并将其拷贝到 p3 中，但是无法更新 p2 中的计数器。

解决方法是将计数器保存在动态内存中。创建一个对象时，分配一个新的计数器。拷贝或者赋值对象时，拷贝指向计数器的指针。

#### 定义一个引用计数的 HasPtr 类

```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    
    HasPtr(const HasPtr& rhs)
        : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++(*use); }
    
    HasPtr& operator=(const HasPtr& rhs) {
        ps = rhs.ps;
        i = rhs.i;
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        use = rhs.use;
        ++(*use);

        return *this;
    }

    ~HasPtr() {
        if (--*use == 0) { // 递减本对象的引用计数，若递减之后等于0，则调用 delete
            delete ps;
            delete use;
        }
    }

private:
    std::string *ps;
    int i;
    std::size_t *use;
}
```

其中参数 `std::size_t *use` 记录多少个对象共享相同的 string。

## 13.3 交换操作

与重排元素顺序的算法一起使用的类，定义 swap 很重要，这类算法在需要交换两个元素的时候会调用 swap。

如果一个类定义了自己的 swap，那么算法将使用类自定义版本，否则，算法将使用标准库定义的 swap。

### 编写我们自己的 swap 函数

可以在我们的类上定义一个自己版本的 swap 来重载 swap 的默认行为，swap 的典型实现如下：

```cpp
class HasPtr {
    friend void swap(HasPtr&, HasPtr&);

private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr& lhs, HasPtr& rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps); // 交换指针，而不是 string
    swap(lhs.i, rhs.i);   // 交换 int
}
```

### swap 函数应该调用 swap，而不是 std::swap

在本例中，数据成员是内置类型的，内置类型没有特定版本的 swap，所以会调用标准库 std::swap.

若一个类的成员有自己类型特定的 swap 函数，那么调用 std::swap 就是错误的。

例如有一个类 `Foo`，有一个类型为 `HasPtr` 的成员 h。如果未定义 Foo 版本的 swap，那么就会使用标准库版本的 swap。标准库版本的 swap 会对 HasPtr 管理的 string 进行不必要的拷贝。

此时，正确的 swap 函数为：

```
void swap(Foo &lhs, Foo &rhs)
{
    using std::swap;
    swap(lhs.h, rhs.h); // 使用 HasPtr 版本的 swap
}
```

上述代码的行为可以解释为：如果存在类型特定的 swap 版本，其匹配优先程度会优于 std 中定义的版本（假定作用域中有 using 声明）。（chapter18.2.3 详细解释）

### 赋值运算符中使用 swap

定义了 swap 的类通常用 swap 来定义它们的赋值运算符。使用了一种被称为 **拷贝并交换(copy and swap)** 的技术，将左侧运算对象与右侧运算对象的一个副本进行交换。当赋值运算符结束时，这个副本被销毁。

```cpp
// 注意这里的右侧运算对象是值传递的，而不是传递引用
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs); // 交换左侧运算对象和局部变量 rhs 的内容，rhs 现在指向本对象曾经使用的内存
    return *this;
} // rhs 被销毁，HasPtr 的析构函数执行，delete 掉 rhs 现在指向的内存
```

这个赋值运算符自动处理了自赋值情况，且天然是异常安全的。它通过改变左侧运算对象之前拷贝右侧运算对象保证了自赋值的正确。

## 13.4 拷贝控制实例

设计两个类，名为 Message 和 Folder，分别表示电子邮件的消息和消息目录。

- 每个 Message 可以出现在多个 Folder 中，但是任意 Message 的内容只有一个副本。用一个包含 Folder* 的 set 来记录 Message 都出现在了哪些 Folder 中。

- 每个 Folder 都保存一个包含 Message* 的 set 来记录都有哪些 Message 出现在这个 Folder 中。

- Message 类提供 save 和 remove 操作向给定的 Folder 添加或删除 Message。

- 拷贝 Message 的时候，副本和原对象是不同的 Message 对象，但是两个 Message 都出现在相同的 Folder 中。需要拷贝 Message 的消息内容，以及出现的 Folder 的指针(set<Folder*>)。在包含此 Message 的 Folder 中也需要添加一个指针指向新创建的 Message。

- 销毁 Message 的时候，包含 Message 的 Folder 的对应指针也应该删除。

- 将一个 Message 对象赋予另一个 Message 对象的时候，需要更新 Folder 集合。指向左侧对象的指针从对应 Folder 删除，并添加到包含右侧 Message 的 Folder 中。

### Message 类

```cpp
class Folder;

class Message {
    friend class Folder;
public:
    explicit Message(const std::string &s = std::string())
        : contents(s) {}

    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    // 从给定 Folder 集合中添加/删除本 Message
    void save(Folder&);
    void remove(Folder&);
    
private:
    std::string contents;
    std::set<Folder*> folders;

    // 拷贝构造函数，拷贝赋值运算符使用的工具函数
    void add_to_folders(const Message&);

    // 从当前类的 folders 中的每个 Folder 删除当前 Message
    void remove_fron_folders();
};
```

### save 和 remove 成员

Message 的两个 public 成员：save 和 remove

- save：将本 Message 存放在给定的 Folder 中：

```cpp
void Message::save(Folder &f)
{
    folders.insert(&f); // message.folders 添加对应 folder
    f.addMsg(this);     // 对应 folder 添加本 message
}
```

- remove：从给定 Folder 删除本 Message：

```cpp
void Message::remove(Folder &f)
{
    folders.erase(&f);  // message.folders 删除指定 folder
    f.remMsg(this);     // 指定 folder 删除本 message
}
```

### Message 类的拷贝控制成员

当拷贝一个 Message 的时候，得到的副本应该与原副本出现在相同的 Folder 中。

所以需要遍历被拷贝 Message 的 folders 成员，将其中所有的 Folder 都添加指向新的 Message 的指针：

```cpp
// m 是被拷贝的 Message
// 将当前 message 添加到所有包含被拷贝元素的 folders 中去
void Message::add_to_folders(const Message& m)
{
    for (auto f: m.folders)
        f->addMsg(this);
}
```

Message 的拷贝构造函数如下：

```cpp
Message::Message(const Message& m)
    : contents(m.contents), folders(m.folders)
{
    add_to_folders(m);
}
```

### Message 的析构函数

当一个 Message 被销毁的时候，必须从指向此 Message  的 Folder 中删除它。拷贝赋值运算符也要执行此操作：

```cpp
// 从当前所有包含该对象的 Folder 中移除该对象
// 为析构函数和复制构造运算符的左侧运算对象准备
void Message::remove_from_folders()
{
    for (auto f : folders)
        f->remMsg(this);
}
```

所以析构函数可以编写为：

```cpp
Message::~Message()
{
    remove_from_folders();
}
```

### Message 的拷贝赋值运算符

为了处理自赋值情况，先从左侧对象的 folders 中删除此 Message 的指针，然后将指针添加到右侧运算对象的 folders 中.

若先添加左侧对象的 Message 指针到右侧对象的 folers 中(`add_to_folders(rhs) 实现`)，然后再删除。在自赋值的情况下，由于 folders 为 set，所以会将此 Message 从所有包含它的 folder 中删除。

```cpp
Message& Message::operator=(const Message &rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.contents;
    add_to_Folders(rhs);
    return *this;
}
```

### Message 的 swap 函数

通过定义 Message 特定版本的 swap，我们可以避免对 contents 和 folders 成员进行不必要的拷贝。

由于 Folder 保存的是 Message 的地址，若只交换 folders 和 contents 成员，Message 的地址不变，Folder 中保存的地址就会有误。

所以先从 Folder 中删除对应的 Message，交换完成之后，重新添加对应的 Message 的地址。

```cpp
void swap(Message &lhs, Message &rhs)
{
    using std::swap;

    // 将每个指针从原来的 Folder 中删除
    for (auto f : lhs.folders) // 左侧 Message 的所有 Folder 移除左侧 Message
        f->remMsg(&lhs);
    for (auto f : rhs.folders) // 右侧 Message 的所有 Folder 移除右侧 Message
        f->remMsg(&rhs);
    
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    // 将新的指针添加到 Folder 中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
```

## 13.5 动态内存管理类

有些类需要自己进行内存分配。

### 练习13.43 用 for_each 和 lambda 代替 for 循环

```cpp
std::for_each(elements, first_free, [this](std::string& elem) { alloc.destroy(&elem); });
```

疑惑点：`elements`, `first_free` 都是 `std::string*` 类型，为何 `lambda` 参数列表为 `std::string` 类型的引用？ 

```cpp
void f(std::string &s)
{
    cout << s << endl;
    cout << *(&s) << endl;
}

int main()
{
    string* sp = new string("hello");
    cout << *sp << endl;
    f(*sp);
    auto ff = [](std::string& s) { cout << s << endl; };
    ff(sp);
}
```

上述代码会发生错误：

```cpp
candidate function not viable: no known conversion from 'std::__cxx11::string *'
      (aka 'basic_string<char> *') to 'std::string &' (aka 'basic_string<char> &') for 1st argument; dereference the argument with *
    auto ff = [](std::string& s) { cout << s << endl; };
```