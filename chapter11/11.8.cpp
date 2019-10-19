#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> exclude = {"the", "that", "this"};
    std::string s;

    while (std::cin >> s)
    {
        if (std::find(exclude.cbegin(), exclude.cend(), s) == exclude.end())
            exclude.push_back(s);
    }
    
    for (const auto& s: exclude) std::cout << s << std::endl;

    return 0;
}