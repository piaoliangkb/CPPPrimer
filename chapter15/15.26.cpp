#include "Quote.h"
#include "15.26_Bulk_quote.h"

int main()
{
    Quote q1, q2("cppprimer", 97.5);
    q1 = q2;
    Quote q3 = std::move(q2);
    Quote q4;
    q4 = std::move(q3);

    std::cout << "-------------------------------" << std::endl;

    Bulk_quote bq1, bq2("algorithms", 88.5, 10, 0.2);
    bq1 = bq2;
    Bulk_quote bq3 = std::move(bq2);
    Bulk_quote bq4;
    bq4 = std::move(bq3);

    return 0;
}