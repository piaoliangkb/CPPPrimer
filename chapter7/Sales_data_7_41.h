#ifndef SALES_DATA_7_41_H
#define SALES_DATA_7_41_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Sales_data {
public:
    // 非委托构造函数
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(price*cnt) 
        {
            cout << "constructor func: Sales_data(std::string s, unsigned cnt, double prive)" << endl;
        }
    // 委托构造函数
    Sales_data(): Sales_data("", 0, 0) 
    {
        cout << "constructor func: Sales_data()" << endl;
    }
    Sales_data(std::string s): Sales_data(s, 0, 0) 
    {
        cout << "constructor func: Sales_data(std::string s)" << endl;
    }
    Sales_data(std::istream &is): Sales_data() 
    {
        cout << "constructor func: Sales_data(std::istream &is)" << endl; 
    }

private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};

#endif