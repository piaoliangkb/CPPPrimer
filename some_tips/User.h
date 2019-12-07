#ifndef _USER_H_
#define _USER_H_

#include <memory>
#include <string>

// pimpl (pointer to implementation) examples
class User {
public:
    User(const std::string &);

    ~User();

    User(const User &);
    
    User &operator=(User);

    int getSalary();

    void setSalary(int);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

#endif