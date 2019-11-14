#ifndef _14_2_SALES_DATA_H_
#define _14_2_SALES_DATA_H_

#include <iostream>
#include <string>

struct Sales_data {

    friend std::istream &operator>>(std::istream &, Sales_data &);
    friend std::ostream &operator<<(std::ostream &, const Sales_data &);

public:
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p) {}

    Sales_data(std::istream &is) { is >> *this; }

    Sales_data operator+(const Sales_data &rhs);

    Sales_data &operator+=(const Sales_data &rhs);

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    std::string isbn() const { return bookNo; }
    Sales_data &combine(const Sales_data &data);
    double avg_price() const { return revenue / units_sold; }
};

Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data Sales_data::operator+(const Sales_data &rhs) {
    auto ret = *this;
    ret += rhs;
    return ret;
}

Sales_data &Sales_data::combine(const Sales_data &data) {
    units_sold += data.units_sold;
    revenue += data.revenue;
    return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream &operator>>(std::istream &is, Sales_data &item) {
    is >> item.bookNo >> item.units_sold >> item.revenue;
    if (is)
        return is;
    else {
        item = Sales_data();
        return is;
    }
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
    os << item.bookNo << " " << item.units_sold << " " << item.revenue;
    return os;
}

#endif
