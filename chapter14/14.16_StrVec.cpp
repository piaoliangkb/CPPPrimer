#include "14.16_StrVec.h"
#include <iostream>

int main()
{
    StrVec sv{"hello", "world"};
    StrVec sv1(sv);
    if (sv == sv1) {
        std::cout << "sv1 equals to sv." << std::endl;
    } 
    else {
        std::cout << "sv1 not equals to sv." << std::endl;
    }

    StrVec sv2{"hello", "world", "didi"};
    if (sv == sv2) {
        std::cout << "sv2 equals to sv." << std::endl;
    } else {
        std::cout << "sv2 not equals to sv." << std::endl;
    }

    return 0;
}