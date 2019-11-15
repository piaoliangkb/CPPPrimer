#include <iostream>
#include <vector>
#include <algorithm>

class equals {
public:
    bool operator()(const int i1, const int i2 = 2) {
        return i1 == i2;
    }
};

int main() 
{
    std::vector<int> v{1, 2, 2, 2, 3, 4, 5};

    std::replace_if(v.begin(), v.end(), equals(), 888);

    for (const auto &item : v) {
        std::cout << item << " ";
    }

    std::cout << std::endl;
}