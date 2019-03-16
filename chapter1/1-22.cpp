#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item total;
    if (std::cin >> total)
    {
        Sales_item item;
        while (std::cin >> item)
        {
            if (item.isbn() == total.isbn())
            total += item;
            else
            {
                std::cout << total << std::endl;
                total = item;
            }
        }
        std::cout << total << std::endl;
    }
    else
    {
        std::cerr << "nothing data here" << std::endl;
    }
    return 0;

}

/*
data:
0-201-78345-X 3 20
0-201-78345-X 2 25
0-201-78346-X 1 100
0-201-78346-X 2 99.9
0-201-78346-X 6 89.9

output:
zl@LAPTOP-ZL:~/cppprimer/chapter1$ ./a.out <1-20data.txt
0-201-78345-X 5 110 22
0-201-78346-X 9 839.2 93.2444
*/