#include "14.26_StrVec.h"
#include <iostream>

int main()
{
    StrVec sv{"hello", "world", "cppprimer", "effective c++", "python"};
    std::cout << sv[1] << std::endl;
    sv[1] = "changed words";
    std::cout << sv[1] << std::endl;

    return 0;
}