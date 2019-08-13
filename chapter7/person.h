#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

struct Person {
    std::string name;
    std::string addr;

    // 此处函数返回值为 const std::string& 类型
    const std::string& getName() const { return name; }
    const std::string& getAddr() const { return addr; }
};

// exercises 7.9
std::istream &read(std::istream &is, Person &person)
{
    is >> person.name >> person.addr;
    return is;
}

std::ostream &print(std::ostream &os, const Person &person)
{
    os << "Person name is " << person.name << std::endl
       << "Person addr is " << person.addr;
    return os; 
}
// end of exercises 7.9

#endif