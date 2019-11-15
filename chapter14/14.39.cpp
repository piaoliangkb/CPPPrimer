#include <fstream>
#include <iostream>
#include <map>
#include <string>

class is_length_equal {
public:
    is_length_equal(std::string::size_type l,
                    std::string::size_type u = 0xffffff)
        : lower(l), upper(u) {}

    bool operator()(const std::string &s) {
        return s.size() >= lower && s.size() <= upper;
    }

private:
    std::string::size_type lower, upper;
};

int main() {
    std::fstream fs("14.38_text.txt");
    std::string s;

    std::map<int, int> cnt;

    is_length_equal func19(1, 9);
    is_length_equal funcup10(10);

    int sum19 = 0, sumup10 = 0;

    while (fs >> s) {
        if (func19(s))
            ++sum19;
        else if (funcup10(s))
            ++sumup10;
    }

    std::cout << "string length of : 1~9"
              << " occurs " << sum19 << " times." << std::endl;

    std::cout << "string length equal and upper : 10"
              << " occurs " << sumup10 << " times." << std::endl;

    return 0;
}