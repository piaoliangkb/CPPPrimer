#include "14.23_StrVec.h"
#include <iostream>

int main()
{
    StrVec sv{"hello", "world"};
    sv.printElems();

    sv = {"cppprimer", "effective c++", "algorithms"};
    sv.printElems();

    return 0;
}