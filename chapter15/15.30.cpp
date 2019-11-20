#include "Basket.h"
#include "Quote.h"
#include "Bulk_quote_derived_from_Quote.h"

#include <vector>
#include <memory>
#include <iostream>

int main()
{
    Basket bk;
    for (int i = 0; i < 10; ++i) {
        bk.add_item(Quote("cppprimer", 97.5));
        bk.add_item(Quote("algorithms", 100));

        Bulk_quote bq1("effective c++", 100, 10, 0.5);
        bk.add_item(bq1);
    }

    bk.total_receipt(std::cout);

    return 0;
}