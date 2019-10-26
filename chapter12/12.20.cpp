#include <fstream>
#include <iostream>
#include "12.19_header.h"
#include <string>

int main()
{
    std::fstream fs("12.20_data.txt");
    std::string line;
    StrBlob sb;
    while (getline(fs, line))
    {
        sb.push_back(line);
    }

    StrBlobPtr pbeg = sb.begin();
    StrBlobPtr pend = sb.end();
    while (pbeg != pend)
    {
        std::cout << pbeg.deref() << std::endl;
        pbeg.incr();
    }

    return 0;
}
