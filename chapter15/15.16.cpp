#include "Quote.h"
#include "Bulk_quote.h"
#include <iostream>

int main()
{
    Quote q("cppprimer", 99.5);
    Bulk_quote bq("effective c++", 100, 20, 0.3);

    print_total(std::cout, q, 10);

    print_total(std::cout, bq, 10);

    print_total(std::cout, bq, 20);

    return 0;
}