#include <iostream>
#include <string>

class Class {
public:
    Class(const std::string &name) : clsname(name) {}

    virtual void printInfo() const {
        std::cout << "This is a class named [ " << clsname << " ]" << std::endl;
    }

    virtual std::string name() const { return clsname; }

protected:
    std::string clsname;
};

class Func : public Class {
public:
    Func(const std::string &cls, const std::string &func)
        : Class(cls), funcname(func) {}

    void printInfo() const override {
        Class::printInfo();

        std::cout << "This is a function named [ " << funcname << " ]"
                  << std::endl;
    }

    std::string name() const override { return funcname; }

protected:
    std::string funcname;
};

class MemFunc : public Func {
public:
    MemFunc(const std::string &cls, const std::string &func, const std::string &memfunc)
        : Func(cls, func), memfuncname(memfunc) {}

    void printInfo() const override {
        Class::printInfo();

        std::cout << "This is a member function named [ " << memfuncname << " ]"
                  << std::endl;
    }

    std::string name() const override { return memfuncname; }

protected:
    std::string memfuncname;
};

int main()
{
    Func func1("String", "split");
    func1.printInfo();

    MemFunc func2("String", "memfunc_find", "memfunc_find");
    func2.printInfo();

    return 0;
}