#include "14.26_String.h"
#include <iostream>

int main()
{
    String s("cppprimer");
    std::cout << s[1] << " " << s[2] << std::endl;
    s[1] = s[2] = '+';
    std::cout << s << std::endl;

    return 0;
}