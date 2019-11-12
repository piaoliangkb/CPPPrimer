#include "String.h"
#include <iostream>

int main() {
    String a;
    std::cout << a.size() << std::endl;

    String b("111222");
    a = b;
    std::cout << a.size() << std::endl;
    
    return 0;
}