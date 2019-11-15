#include "14.27_28_30_StrBlob_StrBlobPtr.h"
#include <iostream>

int main()
{
    StrBlob sb{"hello", "didi", "cpp", "python"};
    for (auto iter = sb.begin(); iter != sb.end(); ++iter) {
        std::cout << iter.deref() << std::endl;
    }

    auto beg = sb.begin();
    std::cout << (beg + 3).deref() << std::endl;

    std::cout << *beg << std::endl;
    *beg = "changed words";
    std::cout << sb.begin().deref() << std::endl;

    std::cout << beg->size() << std::endl;

    return 0;
}