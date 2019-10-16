#include <algorithm>
#include <list>
#include <iostream>
#include <string>
int main()
{
    std::list<std::string> v;
    std::string s;
    while (std::cin >> s)
    {
        v.push_back(s);
    }

    std::string val = "hello";
    auto cnt = std::count(v.cbegin(), v.cend(), val);
    std::cout << "the string of \"hello\" in list has " << cnt << " times." << std::endl;

    return 0;
}