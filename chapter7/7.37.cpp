#include "Sales_data_7_37.h"
#include <iostream>

using namespace std;

int main()
{
    Sales_data a;
    cout << a.isbn() << endl;

    Sales_data b("001");
    cout << b.isbn() << endl;

    return 0;

}