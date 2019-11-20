#ifndef _BULK_QUOTE_DERIVED_FROM_QUOTE_H_
#define _BULK_QUOTE_DERIVED_FROM_QUOTE_H_

#include "Quote.h"
#include <iostream>

class Bulk_quote : public Quote {
public:
    Bulk_quote() { std::cout << "[call func] Bulk_quote()" << std::endl; }

    Bulk_quote(const std::string &bookNo, double p, std::size_t qty,
               double disc)
        : Quote(bookNo, p), quantity(qty), discount(disc) {

        std::cout << "[call func] Bulk_quote(const std::string&, double, "
                     "std::size_t, double)"
                  << std::endl;
    }

    Bulk_quote(const Bulk_quote &rhs)
        : Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) 
    {
        // Quote(rhs); error
        quantity = rhs.quantity;
        discount = rhs.discount;
        std::cout << "[call func] Bulk_quote(const Bulk_quote&)" << std::endl;
    }

    Bulk_quote(Bulk_quote &&rhs)
        : Quote(std::move(rhs)), quantity(std::move(rhs.quantity)),
          discount(std::move(rhs.discount)) {
        std::cout << "[call func] Bulk_quote(Bulk_quote&&)" << std::endl;
    }

    Bulk_quote &operator=(const Bulk_quote &rhs) {
        std::cout << "[call func] Bulk_quote &operator=(const Bulk_quote&)" << std::endl;

        Quote::operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
        return *this;
    }

    Bulk_quote &operator=(Bulk_quote &&rhs) {
        std::cout << "[call func] Bulk_quote &operator=(Bulk_quote&&)" << std::endl;

        Quote::operator=(std::move(rhs));
        quantity = std::move(quantity);
        discount = std::move(discount);
        return *this;
    }

    Bulk_quote* clone() const & override {
        return new Bulk_quote(*this);
    }

    Bulk_quote* clone() && override {
        return new Bulk_quote(std::move(*this));
    }

    double net_price(std::size_t n) const override;

    void debug() const override;

private:
    std::size_t quantity = 0;
    double discount = 0.0;
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