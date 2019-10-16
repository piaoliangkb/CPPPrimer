#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

int main()
{
    const char a[20] = "hello, world";
    const char b[20] = "hello, world";

    // not the same address
    cout << &a << endl;
    cout << &b << endl;

    cout << a << endl;
    cout << b << endl;

    // 把指针指向地址进行了比较
    cout << (a==b) << endl;

    vector<const char*> v1{a};
    list<const char*> v2{b};

    cout << equal(v1.cbegin(), v1.cend(), v2.cbegin()) << endl;
}