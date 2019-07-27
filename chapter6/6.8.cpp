#include "Chapter6.h"
#include <iostream>

using namespace std;

int f(int n)
{
    int res = 1;
    while (n)
    {
        res *= n--;
    }
    return res;
}

int main()
{
    cout << f(2) << endl;
    cout << f(3) << endl;
    cout << f(4) << endl;
}