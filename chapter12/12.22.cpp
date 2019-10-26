#include <fstream>
#include <iostream>
#include "12.22_header.h"
#include <string>

int main()
{
    std::string line;
    const StrBlob sb({"from", "app", "models", "import", "db"});

    ConstStrBlobPtr pbeg = sb.begin();
    ConstStrBlobPtr pend = sb.end();
    while (pbeg != pend)
    {
        std::cout << pbeg.deref() << std::endl;
        pbeg.incr();
    }

    return 0;
}
