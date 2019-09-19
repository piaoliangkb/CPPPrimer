#include <iostream>
#include <string>
#include <sstream>

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
    std::istringstream iss("hello");
    read(iss);
}