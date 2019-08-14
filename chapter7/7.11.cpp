#include <iostream>
#include "Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Sales_data data;
    cout << data.isbn() << " " << data.units_sold << " " << data.revenue << endl;

    Sales_data data1("001");
    cout << data1.isbn() << " " << data1.units_sold << " " << data1.revenue << endl;

    Sales_data data2("002", 10, 5.0);
    cout << data2.isbn() << " " << data2.units_sold << " " << data2.revenue 
         << " " << data2.avg_price() << endl;

    Sales_data data3(cin); // need input
    cout << data3.isbn() << " " << data3.units_sold << " " << data3.revenue << endl;
}

