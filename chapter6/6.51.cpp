#include <iostream>

using std::cout;
using std::endl;

void f()
{
    cout << "call of function f() without parameters" << endl;
}

void f(int)
{
    cout << "call of function f() with params {int}" << endl;
}

void f(int, int)
{
    cout << "call of function f() with params {int, int}" << endl;
}

void f(double, double = 3.14)
{
    cout << "call of function f() with params {double, double = 3.14}" << endl;
}

int main()
{
    f(2.56, 42);  // error: call of overloaded 'f(double, int)' is ambiguous
    f(42);        // call of function f() with params {int}
    f(42, 0);     // call of function f() with params {int, int}
    f(2.56, 3.14);// call of function f() with params {double, double = 3.14}
}