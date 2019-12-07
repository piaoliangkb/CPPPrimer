#include "User.h"
#include <iostream>

// pimpl (pointer to implementation) examples

class User::Impl {
public:
    Impl(const std::string &name) : name(name){}

    ~Impl() = default;

    Impl(const Impl &rhs) {
        name = rhs.name;
        salary = rhs.salary;
    }

    void welcomeMsg() { std::cout << "Welcome " << name << std::endl; }

    std::string name;
    int salary = -1;
};

User::User(const std::string &name) : pimpl(new Impl(name)) {
    pimpl->welcomeMsg();
}

User::~User() {}

User::User(const User &others) : pimpl(new Impl(*others.pimpl)) {}

User &User::operator=(User rhs) {
    using std::swap;
    swap(pimpl, rhs.pimpl);
    return *this;
}

int User::getSalary() { return pimpl->salary; }

void User::setSalary(int num) {
    pimpl->salary = num;
    std::cout << "Salary set to " << pimpl->salary << std::endl;
}