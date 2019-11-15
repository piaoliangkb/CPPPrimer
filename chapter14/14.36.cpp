#include <string>
#include <iostream>
#include <vector>

class returnString {
public:
    std::vector<std::string> operator()(std::istream &is) {
        std::string s;
        std::vector<std::string> v;
        while (std::getline(is, s)) {
            if (!is) v.push_back(std::string());
            else v.push_back(s);
        }
        return v;
    }
};

int main()
{
    returnString func;
    auto res = func(std::cin);

    for (const auto &item : res) {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    return 0;
}