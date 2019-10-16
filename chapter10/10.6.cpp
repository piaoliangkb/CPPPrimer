#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v = {10, 9, 8, 7, 6, 5};
    std::fill_n(v.begin(), v.size(), 0);
    for (auto &i: v) std::cout << i << " ";
    std::cout << std::endl;
}