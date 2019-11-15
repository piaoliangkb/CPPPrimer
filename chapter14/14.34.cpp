#include <iostream>

class if_then_else {
public:
    int operator()(const int i1, const int i2, const int i3) {
        return i1 ? i2 : i3;
    }
};

int main()
{
    if_then_else func;
    std::cout << func(0, 1, 2) << std::endl;
    std::cout << func(1, 2, 3) << std::endl;

    return 0;
}