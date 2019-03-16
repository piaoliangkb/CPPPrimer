# 第一章 开始

## 1.1 编写一个简单的C++程序

### 1.1.1 编译、运行程序

#### 系统返回值

在Unix和Windows系统中，执行完一个程序之后，都可以通过<code>echo</code>命令获得返回值。

- 在Unix系统中，通过命令<code>echo $?</code>
- 在Windows系统中，可以在CMD中通过命令<code>echo %ERRORLEVEL%</code>获得返回值，且powershell中此命令无效

关于返回值的练习请看**练习1.2**

- Windows中，<code>echo %ERRORLEVEL%</code>返回return后的数值
- Unix中，<code>echo $?</code>返回:
    - return -1 -> 255
    - return a(a>255)  -> a%256 

#### 编译器命令

运行GNU编译器的命令是<code>g++</code>

```
$ g++ -o prog1 prog1.cpp
```
其中，<code>-o prog1</code>是编译器参数，指定了可执行文件的文件名。在Unix系统中，可执行文件没有后缀；在Windows系统中，可执行文件的后缀是exe。

## 1.2 初识输入输出

iostream包含了输入流和输出流，术语"stream"表达的是：随着时间的推移，字符是顺序生成或消耗的。

### 标准输入输出对象

- cin是istream类型的对象，这个对象也被称为标准输入。
- cout是ostream类型的对象，这个对象也被称为标准输出。

此外，标准库还定义了两个ostream对象

- cerr用来输出警告和错误信息
- clog用来输出程序运行时的一般性信息（日志）

### 向流写入数据

1. 输出运算符<<左侧运算对象必须是一个ostream对象，右侧是要输出的内容。
   输出运算符的运算结果是其左侧对象，即ostream对象。
   
   对于表达式
   ```cpp
   std::cout << "Enter two numbers" << std::endl; 
   ```
   相当于
   ```cpp
   (std::cout << "Enter two numbers" ) << std::endl;
   ```

2. endl是一个被称为操纵符的特殊值。写入endl的作用是结束当前行，并将与设备关联的缓冲区中的内容刷到设备中。
   
   缓冲刷新的操作可以保证所有的输入输出都真正的写入到输出流，而不是停留在内存中。

### 从流读取数据

1. 输入运算符>>接受一个istream作为左侧运算对象，接受一个对象作为右侧运算对象。输入运算符返回左侧运算对象作为其计算结果。
   
   对于表达式
   ```cpp
   std::cin >> v1 >> v2;
   ```
   相当于
   ```cpp
   (std::cin >> v1 ) >> v2;
   ```

## 1.3 注释介绍

### 注释界定符不能嵌套

我们通常需要在调试期间注释掉一些代码，这些代码可能包含界定符对形式的注释，可能导致注释嵌套错误，所以最好的方式是用单行注释方式注释掉代码段的每一行。

## 1.4 控制流

### 1.4.2 for语句

每个for语句都包含两部分，循环头和循环体。

- 循环头：循环头控制循环的执行次数，由三部分组成
  
    - 初始化语句(init-statement)
    - 循环条件(condition)
    - 表达式(expression)

### 1.4.3 读取数据量不定的输入数据

数据读取操作在while循环中完成

```cpp
while (std::cin >> val)
```

当我们使用一个<code>istream</code>对象作为while的检测条件时，它的效果就是检测流的状态。

- 如果流是有效的，那么检测成功。
- 如果遇到文件结束符(end-of-file)，或遇到一个无效输入时（例如读取的数不是一个整数）,<code>istream</code>对象的状态会变为无效。处于无效状态的对象会使条件为false。

文件结束符

- Windows操作系统中是<code>CTRL+Z</code>，然后按enter或者return
- Unix和MacOS操作系统中是<code>CTRL+D</code>

## 1.5 类简介

### 使用文件进行重定向

格式为<code> $./a.out \<inputfilename \>outputfilename </code>

```bash
zl@LAPTOP-ZL:~/cppprimer/chapter1$ ./a.out <1-20data.txt
0-201-78345-X 3 60 20
0-201-78345-X 2 50 25
0-201-78346-X 1 100 100
0-201-78346-X 2 199.8 99.9
0-201-78346-X 6 539.4 89.9
```

一点问题:

Ubuntu18.04LTS输入outputfilename时，出现Perssion Denied

```bash
zl@LAPTOP-ZL:~/cppprimer/chapter1$ sudo ./a.out <1-20data.txt >output.txt
-bash: output.txt: Permission denied
```

解决方法：切换到root权限

Windows cmd可正常使用。

### 1.5.2 初识成员函数

成员函数是定义为类的一部分函数，有时也被称为方法。