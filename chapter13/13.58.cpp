#include <vector>
#include <iostream>
#include <algorithm>

class Foo {
public:
    Foo() : data(0) {}

    Foo(std::initializer_list<int> il) : data(il) {}

    Foo sorted() &&;

    Foo sorted() const &;

    void print() {
        for (const auto i : data) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> data;
};

// ex13.56
// Foo Foo::sorted() const & {
//     std::cout << "[call func] Foo sorted() const &" << std::endl;

//     Foo ret(*this);
//     return ret.sorted();
// }
// recursion and stackoverflow

// ex13.57
Foo Foo::sorted() const & {
    std::cout << "[call func] Foo sorted() const &" << std::endl;

    return Foo(*this).sorted();
}
// [call func] Foo sorted() const &
// [call func] Foo sorted() && 3 4 5 6 7 8

    Foo Foo::sorted() && {
    std::cout << "[call func] Foo sorted() &&" << std::endl;

    std::sort(data.begin(), data.end());
    return *this;
}

int main() {
    Foo f({8, 7, 6, 5, 4, 3});

    auto temp = f.sorted();
    temp.print();

    return 0;
}

