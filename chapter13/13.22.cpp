#include <string>
#include <iostream>

// 类值版本的 HasPtr

class HasPtr {
public:
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}

    HasPtr& operator=(const HasPtr& rhs) {
        auto temp = new std::string(*rhs.ps); // 先拷贝右侧的值，可以处理自赋值情况
        delete ps;
        ps = temp;
        i = rhs.i;
        
        return *this;
    }

    ~HasPtr() { delete ps; }

    std::string *ps;
    int i;
};

int main()
{
    HasPtr hp("hello"), hpp("hi");
    hp = hpp;
    std::cout << *hp.ps << std::endl;

}