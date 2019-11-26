#include "static_and_extern.h"
#include <iostream>

int main()
{
    std::cout << extern_s.getStr() << std::endl;
    return 0;
}

/*
$ clang++ static_and_extern.h sae_test1.cpp sae_test2.cpp -std=c++11
$ ./a.out
$ Frozen

extern_s has been defined in sar_test1.cpp
it can be seen a global variable.
*/