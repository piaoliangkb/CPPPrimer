#include "Bulk_quote.h"
#include <iostream>

class My_quote : public Bulk_quote {
public:
    My_quote() = default;

    My_quote(const std::string &bookNo, double p, std::size_t qty, double disc, std::size_t dismqty)
        : Bulk_quote(bookNo, p, qty, disc), max_qty(dismqty) {}

    double net_price(std::size_t n) const override;

private:
    std::size_t max_qty;
};

double My_quote::net_price(std::size_t n) const {
    if (n >= Bulk_quote::min_qty && n < max_qty) {
        return n * (1 - discount) * price;
    }
    else if (n >= max_qty) {
        return max_qty * (1 - discount) * price + (n - max_qty) * price;
    }
    else {
        return n * price;
    }
}

int main()
{
    // 5 到 10 件打 8 折
    // 10 件以上的原价
    My_quote mq("cpp primer", 100, 5, 0.5, 10);

    print_total(std::cout, mq, 5);

    print_total(std::cout, mq, 10);

    print_total(std::cout, mq, 20);

    return 0;
}