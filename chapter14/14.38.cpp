#include <fstream>
#include <iostream>
#include <map>
#include <string>

class is_length_equal {
public:
    is_length_equal(std::string::size_type n) : sz(n) {}

    bool operator()(const std::string &s) { return s.size() == sz; }

private:
    std::string::size_type sz;
};

int main() {
    std::fstream fs("14.38_text.txt");
    std::string s;

    std::map<int, int> cnt;

    while (fs >> s) {
        for (int i = 1; i <= 10; ++i) {
            is_length_equal func(i);
            if (func(s)) ++cnt[i];
        }
    }

    for (const auto &item : cnt) {
        std::cout << "string length of : " << item.first << " occurs "
                  << item.second << " times." << std::endl;
    }

    return 0;
}