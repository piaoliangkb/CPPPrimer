#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item item;
    if (std::cin >> item)
    {
        Sales_item cur;
        int count = 1;
        while (std::cin >> cur)
        {
            if (item.isbn() == cur.isbn())
            {
                count ++;
            }
            else
            {
                std::cout << "the isbn of " << item.isbn() << " has " << count << "items " << std::endl;
                item = cur;
                count = 1;
            }
        }
        std::cout << "the isbn of " << item.isbn() << " has " << count << "items" << std::endl;
    }
    return 0;
}

/*
zl@LAPTOP-ZL:~/cppprimer/chapter1$ ./a.out <1-20data.txt
the isbn of 0-201-78345-Xhas 2items
the isbn of 0-201-78346-Xhas 3items
*/