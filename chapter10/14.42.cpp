#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> vec{1088, 999, 8726, 9832, 199, 200, 10086};

    // bool std::greater::operator()( const T& lhs, const T& rhs ) const;
    auto res = std::count_if(
        vec.begin(), vec.end(),
        std::bind(std::greater<int>(), std::placeholders::_1, 1024));
    std::cout << res << std::endl;

    std::vector<std::string> v{"poch", "hello", "poch", "hi"};
    auto ret = std::find_if(v.begin(), v.end(),
                            std::bind(std::not_equal_to<std::string>(),
                                      std::placeholders::_1, "poch"));
    std::cout << *ret << std::endl;

    std::transform(vec.begin(), vec.end(), vec.begin(),
                   std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    for (const auto &i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}