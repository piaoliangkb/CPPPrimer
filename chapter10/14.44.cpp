#include <map>
#include <iostream>
#include <functional>
#include <string>

int add(int i, int j) { return i + j; }

auto mod = [](int i, int j) { return i % j; };

struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};

std::map<std::string, std::function<int(int, int)>> binops = {
    {"+", add},
    {"-", std::minus<int>()},
    {"*", [](int i, int j) { return i * j; }},
    {"/", divide()},
    {"%", mod}
};

int main()
{
    int lhs, rhs;
    std::string op;
    while (std::cin >> lhs >> op >> rhs) {
        std::cout << "res is " << binops[op](lhs, rhs) << std::endl; 
    }

    return 0;
}