#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string(), const std::string& s1 = std::string("noname-object"))
        : ps(new std::string(s)), i(0), use(new std::size_t(1)), name(s1) {}
    
    HasPtr(const HasPtr& rhs)
        : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++(*use); }
    
    HasPtr& operator=(const HasPtr& rhs) {
        if (--*use == 0) {
            std::cout << "left hand string is : " << *ps << std::endl;
            delete ps;
            delete use;
            std::cout << "delete left hand side object" << std::endl;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        ++(*use);

        return *this;
    }

    ~HasPtr() {
        std::cout << name << " call func ~HasPtr()" << std::endl;
        if (--*use == 0) { // 递减本对象的引用计数，若递减之后等于0，则调用 delete
            std::cout << "destroy this object" << std::endl;
            delete ps;
            delete use;
        }
    }

    std::string *ps;
    int i;
    std::size_t *use;
    std::string name; // add for debug
};

int main()
{
    HasPtr hp("hello", "hp");
    HasPtr hpp("hi", "hpp");

    std::cout << *hp.use << std::endl;  // 1
    hp = hpp; // delete hp.use, hp.ps
    std::cout << *hp.ps << std::endl;   // hi
    std::cout << *hp.use << std::endl;  // 2
    std::cout << *hpp.use << std::endl; // 2
}
// when out of scope hpp first call destructor, then hp