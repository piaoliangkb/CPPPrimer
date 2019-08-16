#include <iostream>
#include "Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Sales_data data;
    print(cout, data) << endl;

    Sales_data data1("001");
    print(cout, data1) << endl;

    Sales_data data2("002", 10, 5.0);
    print(cout, data2) << endl;

    Sales_data data3(cin); // need input
    print(cout, data3) << endl;
}

