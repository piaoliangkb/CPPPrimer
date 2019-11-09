#include <string>
#include <iostream>
#include <utility>

// 类值版本的 HasPtr

class HasPtr {
public:
    friend void swap(HasPtr&, HasPtr&);

    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}

    HasPtr& operator=(const HasPtr &rhs) {
        std::cout << "using copy-assignment operator." << std::endl;
        ps = rhs.ps;
        i = rhs.i;
        return *this;
    }

    HasPtr& operator=(HasPtr &&rhs) {
        std::cout << "using move-assignment operator." << std::endl;
        ps = std::move(rhs.ps);
        i = std::move(rhs.i);
        rhs.ps = nullptr;
        return *this;
    }

    ~HasPtr() { delete ps; }

    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    std::cout << "call function HasPtr's swap()" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

int main()
{
    HasPtr hp("hello"), hpp("hi"), hppp("cppprimer");

    hp = hppp;
    std::cout << *hp.ps << std::endl;
    std::cout << *hppp.ps << std::endl;

    hp = std::move(hpp);
    std::cout << *hp.ps << std::endl;
    if (!hpp.ps) {
        std::cout << "hpp.ps is nullptr" << std::endl;
    }

    return 0;
}