#ifndef _15_27_BULK_QUOTE_H_
#define _15_27_BULK_QUOTE_H_

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;

    double net_price(std::size_t n) const override;

    void debug() const override;
};

double Bulk_quote::net_price(std::size_t n) const {
    if (n >= quantity) {
        return n * (1 - discount) * price;
    } else {
        return n * price;
    }
}

void Bulk_quote::debug() const {
    Quote::debug();

    std::cout << "no member in Bulk_quote, all members are in Disc_quote"
              << std::endl;
}

#endif