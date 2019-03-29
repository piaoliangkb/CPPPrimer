#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    const int i = 42;  // const int
    auto j = i;        // int
    const auto &k = i; // 对常量的引用
    auto *p =  &i;     // 对常量对象取地址是底层const，保存，const int*

    const auto j2 = i, &k2 = i; // const int, const int&
}