#include <iostream>
#include <string>

std::istream& read(std::istream &is) {
    std::string s;
    while (is >> s) {
        std::cout << s << std::endl;
    }
    is.clear();

    return is;
}

int main()
{
    std::istream &is = read(std::cin);
    std::cout << is.rdstate() << std::endl;
}