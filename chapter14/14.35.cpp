#include <string>
#include <iostream>

class returnString {
public:
    std::string operator()(std::istream &is) {
        std::string s;
        std::getline(is, s);
        if (!is) return std::string();
        else return s;
    }
};

int main()
{
    returnString func;
    std::cout << func(std::cin) << std::endl;

    return 0;
}