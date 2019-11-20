#include "Quote.h"
#include "Bulk_quote.h"
#include <vector>
#include <memory>

int main()
{
    std::vector<std::shared_ptr<Quote>> vec;
    vec.push_back(std::make_shared<Bulk_quote>("cppprimer", 80, 10, 0.2));
    vec.push_back(std::make_shared<Bulk_quote>("algorithms", 50, 10, 0.2));

    double sum = 0.0;
    for (const auto& item : vec) {
        sum += item->net_price(10);
    }

    std::cout << sum << std::endl;

    return 0;
}