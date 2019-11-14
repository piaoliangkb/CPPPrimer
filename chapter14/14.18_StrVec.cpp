#include "14.18_StrVec.h"
#include <iostream>

using std::cout;
using std::endl;

void cmp(const StrVec &lhs, const StrVec &rhs) {
    cout << std::boolalpha << "lhs > rhs : " << (lhs > rhs) << endl
         << "lhs >= rhs : " << (lhs >= rhs) << endl
         << "lhs < rhs : " << (lhs < rhs) << endl
         << "lhs <= rhs : " << (lhs <= rhs) << endl; 
}

int main()
{
    StrVec sv{"hello", "ab"};
    StrVec sv2{"hello", "ac"};
    cmp(sv, sv2);

}