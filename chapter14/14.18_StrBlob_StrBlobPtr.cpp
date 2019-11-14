#include "14.18_StrBlob_StrBlobPtr.h"
#include <iostream>

using std::endl;
using std::cout;

int main()
{
    StrBlob sb{"abc", "abb"}, sb1{"abbc", "abb", "abb"};
    cout << std::boolalpha << (sb1 < sb) << " " << 
    (sb1 <= sb) << " " << (sb1 > sb) << " " << (sb1 >= sb) << endl;

    return 0;
}