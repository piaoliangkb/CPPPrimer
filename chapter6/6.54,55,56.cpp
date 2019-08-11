#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int add(int a, int b)
{
    return a + b;
}

int minus(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b == 0) return 0;
    else return a / b;
}


int main()
{
    using pf = int (*)(int, int);
    vector<pf> v = {add, minus, mul, divide};

    // call function way1
    cout << v[0](1, 2) << endl;
    cout << v[2](1, 2) << endl;

    // call function way2
    for (auto func : v)
    {
        cout << func(1, 2) << endl;
    }

    //
    //----------------------------------------------------//
    //

    using pfunc1 = decltype(add) *;

    vector<decltype(add) *> v1 = {add, minus, mul, divide};
    vector<pfunc1> v2 = {add, minus, mul, divide};

    //
    //----------------------------------------------------//
    //

    using pfunc2 = int(int, int);
    using pfunc3 = decltype(add);

    vector<pfunc2 *> v3 = {add, minus, mul, divide};
    vector<pfunc3 *> v4 = {add, minus, mul, divide};

    //
    //----------------------------------------------------//
    //

    typedef decltype(add) *pfunc4;
    typedef int(*pfunc5)(int, int);

    vector<pfunc4> v5 = {add, minus, mul, divide};
    vector<pfunc5> v6 = {add, minus, mul, divide};

    return 0;
}