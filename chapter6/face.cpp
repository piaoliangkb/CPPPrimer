#include "Chapter6.h"
#include <iostream>

int f(int n)
{
    int res = 1;
    while (n)
    {
        res *= n--;
        std::cout << "now res is " << res << std::endl;
    }
    return res;
}