#include <iostream>
#include "12.19_header.h"

using std::cout;
using std::endl;

int main() 
{ 
    StrBlob str{"hahaha", "xixiix", "heiheihei"}; 
    auto p = str.begin();
    cout << p.deref() << endl;
    
}