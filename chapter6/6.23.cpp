#include <iostream>

using namespace std;

// 数组的引用，数组大小必须为2
void print(const int (&a)[2])
{
    for (auto i : a) cout << i << " ";
    cout << endl;
}

// 打印每个字符
void print(const char *c)
{
    if (*c)
    {
        while (*c) cout << *c++ << " ";
    }
    cout << endl;
}

// 使用标准库首元素和尾元素
void print(const int *begin, const int *end)
{
    while (begin != end)
    {
        cout << *begin++ << " ";
    }
    cout << endl;
}

// 传入数组大小
void print(const int a[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

// 实参为指向某个int的指针
void print(const int *const i)
{
    cout << *i << endl;
}

int main()
{
    int j[2] = {10, 9}, i = 99;
    print(j);
    print("hello");
    print(begin(j), end(j));
    print(j, end(j) - begin(j));
    print(&i);
}