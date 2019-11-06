#include <string>
#include <iostream>

// 类值版本的 HasPtr

class HasPtr {
public:
    friend void swap(HasPtr&, HasPtr&);

    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}

    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
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

    swap(hp, hpp);
    std::cout << *hp.ps << std::endl;
    std::cout << *hpp.ps << std::endl;

    hp = hppp;
    std::cout << *hp.ps << std::endl;

}