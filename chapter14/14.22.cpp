#include "14.20_21_22_Sales_data.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    Sales_data s;
    cin >> s;
    cout << s.isbn() << endl;
    s = std::string("10086");
    cout << s.isbn() << endl;

    return 0;
}