#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item item1, item2;
    std::cin >> item1 >> item2;
    if (item1.isbn() == item2.isbn())
    {
        std::cout << item1+item2 << std::endl;
    }
    else
    {
        std::cerr << "ISBN not match " << std::endl;
    }
    return 0;
}

/*
zl@LAPTOP-ZL:~/cppprimer/chapter1$ ./a.out
XXX 3 20.0
XXX 2 25.0
XXX 5 110 22

zl@LAPTOP-ZL:~/cppprimer/chapter1$ ./a.out
XXX 3 20
AAA 2 25
ISBN not match
*/