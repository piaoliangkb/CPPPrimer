#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    void Adddata(Sales_data data);
    void Print();

    // exercises 7.2 
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data &data);
    // end of exercises 7.2
};

void Sales_data::Adddata(Sales_data data)
{
    if (bookNo != data.bookNo) return ;
    units_sold += data.units_sold;
    revenue += data.revenue;
}

void Sales_data::Print()
{
    std::cout << "{" << std::endl;
    std::cout << "This book number is : " << bookNo << std::endl;
    std::cout << "This book has been sold " << units_sold << std::endl;
    std::cout << "All revenue is " << revenue << std::endl << "}" << std::endl;
}

// exercises 7.2
Sales_data& Sales_data::combine(const Sales_data &data)
{
    units_sold += data.units_sold;
    revenue += data.revenue;
    return *this;
}
// end of exercises 7.2

// exervises 7.6
Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    is >> item.bookNo >> item.units_sold >> item.revenue;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue;
    return os;
}
// end of exercises 7.6

#endif
