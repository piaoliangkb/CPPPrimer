#include "StrVec.h"
#include <utility>
#include <iostream>
#include <memory>
#include <string>

std::allocator<std::string> StrVec::alloc;

int main()
{
    StrVec sv1{"hello", "world", "this", "that"};
    StrVec sv2 = std::move(sv1);

    sv2.printElems();
    sv1.printElems();

    std::cout << sv1.size() << std::endl;
    std::cout << sv1.capacity() << std::endl;

    std::cout << sv2.size() << std::endl;
    std::cout << sv2.capacity() << std::endl;

    sv2.push_back("add another one to test allocator");
    std::cout << sv2.size() << std::endl;
    std::cout << sv2.capacity() << std::endl;
    sv2.printElems();

    return 0;
}