#include "static_and_extern.h"
#include <iostream>
#include <string>


int main()
{
    static_s = Str(std::string("hello"));
    std::cout << static_s.getStr() << std::endl;

    return 0;
}