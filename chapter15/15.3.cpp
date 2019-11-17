#include "Quote.h"
#include <iostream>

int main()
{
    Quote q("cppprimer", 97.5);
    print_total(std::cout, q, 10);

    return 0;
}