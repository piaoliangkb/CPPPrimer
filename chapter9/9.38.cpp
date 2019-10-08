#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::string s;
    std::vector<std::string> v;
    while (std::cin >> s)
    {
        v.push_back(s);
        std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
    }
    return 0;
}