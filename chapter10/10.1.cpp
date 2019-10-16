#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v;
    int i;
    while (std::cin >> i)
    {
        v.push_back(i);
    }

    int val = 5;
    auto cnt = std::count(v.cbegin(), v.cend(), val);
    std::cout << "the number of 5 in vector has " << cnt << " times." << std::endl;

    return 0;
}