#ifndef _BULK_QUOTE_H
#define _BULK_QUOTE_H

#include "Quote.h"

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;

    Bulk_quote(const std::string &bookNo, double p, std::size_t qty, double disc)
        : Quote(bookNo, p), min_qty(qty), discount(disc) {}

    double net_price(std::size_t n) const override;    

protected:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t n) const {
    if (n >= min_qty) {
        return n * (1 - discount) * price;
    }
    else {
        return n * price;
    }
}

#endif