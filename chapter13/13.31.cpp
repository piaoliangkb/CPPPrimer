#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

    bool operator<(const HasPtr& rhs) const {
        if (*ps < *rhs.ps) return true;
        else return false;
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
    std::vector<HasPtr> vec;
    vec.emplace_back("hi");
    vec.emplace_back("hello");
    vec.emplace_back("cppprimer");

    std::cout << "before sort" << std::endl;
    for (const auto &item : vec) {
        std::cout << *item.ps << std::endl;
    }

    std::cout << "after sort" << std::endl;
    std::sort(vec.begin(), vec.end());
    for (const auto &item : vec) {
        std::cout << *item.ps << std::endl;
    }

}