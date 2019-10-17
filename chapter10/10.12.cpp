#include "Sales_data_10_12.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool compareISBN(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() > rhs.isbn();
}

int main()
{
    vector<Sales_data> v;
    for (int i=0; i<10; ++i)
    {
        string thisis = "isbn_this_" + to_string(i);
        v.push_back(Sales_data(thisis));
    }
    sort(v.begin(), v.end(), compareISBN);
    for (const auto &item: v)
    {
        cout << item.isbn() << endl;
    }

    return 0;
}