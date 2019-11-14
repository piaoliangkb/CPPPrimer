#include "14.16_StrBlob_StrBlobPtr.h"
#include <iostream>

int main()
{
    StrBlob sb{"cppprimer", "fluentpython", "algorithms"};

    for (auto iter = sb.begin(), end = sb.end(); iter != end; iter.incr()) {
        std::cout << iter.deref() << std::endl;
    }

    return 0;
}