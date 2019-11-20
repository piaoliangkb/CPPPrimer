#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <iostream>
#include <string>

class Quote {
public:
    Quote() { std::cout << "[call func] Quote()" << std::endl; }

    Quote(const std::string &book, double sales_price)
        : bookNo(book), price(sales_price) {
        std::cout << "[call func] Quote(const std::string&, double)"
                  << std::endl;
    }

    Quote(const Quote &rhs) {
        std::cout << "[call func] Quote(const Quote&)" << std::endl;

        bookNo = rhs.bookNo;
        price = rhs.price;
    }

    Quote(Quote &&rhs) {
        std::cout << "[call func] Quote(Quote&&)" << std::endl;

        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
    }

    Quote &operator=(const Quote &rhs) {
        std::cout << "[call fnuc] Quote &operator=(const Quote&)" << std::endl;

        bookNo = rhs.bookNo;
        price = rhs.price;
        return *this;
    }

    Quote &operator=(Quote &&rhs) {
        std::cout << "[call func] Quote &operaotr=(Quote&&)" << std::endl;

        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
        return *this;
    }

    virtual Quote* clone() const & {
        return new Quote(*this);
    }

    virtual Quote* clone() && {
        return new Quote(std::move(*this));
    }

    std::string isbn() const { return bookNo; }

    // 派生类负责不同的折扣计算方法
    virtual double net_price(std::size_t n) const { return n * price; }

    virtual void debug() const {
        std::cout << "std::string bookNo, double price" << std::endl;
    }

    // 虚构函数动态绑定
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0; // 普通状态下不打折的价格
};

double print_total(std::ostream &os, const Quote &item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret
       << std::endl;
    return ret;
}

#endif