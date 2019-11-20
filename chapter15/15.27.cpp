#include "15.27_Bulk_quote.h"
#include <iostream>

int main()
{
    Bulk_quote bq("cppprimer", 99.5, 20, 0.2);
    std::cout << bq.net_price(10) << std::endl;
    std::cout << bq.net_price(20) << std::endl;

    return 0;
}