
<!-- TOC -->

- [第十六章 模板与泛型编程](#第十六章-模板与泛型编程)
    - [16.1 定义模板](#161-定义模板)
        - [16.1.1 函数模板](#1611-函数模板)
            - [实例化函数模板](#实例化函数模板)

<!-- /TOC -->

# 第十六章 模板与泛型编程

## 16.1 定义模板

### 16.1.1 函数模板

一个函数模板(function template) 就是一个公式，可以用来生成特定类型的函数版本。

例如，一个 compare 的模板版本：

```cpp
templace <typaname T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}
```

- 模板定义以 **关键字 template** 开始。

- 后跟一个 **模板参数列表 template parameter list**：这是一个逗号分隔的一个或多个 **模板参数(template parameter)** 的列表，使用 `<>` 包围起来。

在定义模板中，模板参数列表不能为空。

- 模板参数表示在类或函数定义中用到的类型或者值，当使用模板时，我们隐式或者显式地指定 **模板实参(template argument)**，将其绑定到 **模板参数** 上。

我们的函数 compare 声明了一个名为 T 的类型参数，在 compare 中，我们用 T 表示一个类型。T 表示的实际类型在 **编译时** 根据 compare 的使用情况来确定。

#### 实例化函数模板

编译器用推断出的模板参数来为我们 **实例化(instantiate)** 一个特定版本的参数。