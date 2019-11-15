#include "14.26_StrBlob_StrBlobPtr.h"
#include <iostream>

int main()
{
    StrBlob sb{"hello", "hi", "cpp", "python"};
    std::cout << sb[1] << " " << sb[2] << std::endl;

    sb[1] = "java";
    std::cout << sb[1] << " " << std::endl;

    auto beg = sb.begin();
    std::cout << beg.deref() << std::endl;
    std::cout << beg[1] << " " << beg[2] << std::endl;

    return 0;
}