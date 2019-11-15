#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>


int main()
{
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{2, 3, 4, 5};

    std::modulus<int> mod;
    auto predicator = [mod](int i) {return mod(12, i) == 0;};

    auto res = std::all_of(v1.begin(), v1.end(), predicator);

    std::cout << std::boolalpha << res << std::endl;

    auto res1 = std::all_of(v2.begin(), v2.end(), predicator);

    std::cout << std::boolalpha << res1 << std::endl;
}