#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

// this has been used in the declaration of func std::istream &read(...)
// must be declared before the declaration of function read(...)
// otherwise we will see the error :
// .\Sales_data.h:14:50: error: 'read' was not declared in this scope
struct Sales_data;

// this function has been used in struct {Salse_data}
// must be declared before definition
// otherwise an error occured :
// .\Sales_data.h:14:50: error: 'read' was not declared in this scope
std::istream &read(std::istream &is, Sales_data &item);

struct Sales_data {

    //execises 7.11
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p) {}
    
    // in exercises 7.12 we move the definition of the Salse_data constructor that takes an istream into the body of Sales_data class
    Sales_data(std::istream &is) { read(is, *this); }
    // end of ecercises 7.12

    // end of exercises 7.11

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    void Adddata(Sales_data data);
    void Print();

    // exercises 7.2 
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data &data);
    double avg_price() const { return revenue / units_sold; }
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

//exercises 7.11
//in exercises 7.12 this segment has to be commentted out, and move the definition into the body of Sales_data class
// Sales_data::Sales_data(std::istream &is)
// {
//     read(is, *this);
// }
//end of exercises 7.12
//end of exercises 7.11

#endif
