#include "14.2_Sales_data.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    Sales_data item1, item2;
    cin >> item1 >> item2;

    cout << item1 + item2 << endl;
    
    item1 += item2;

    cout << item1 << endl;

    return 0;
}