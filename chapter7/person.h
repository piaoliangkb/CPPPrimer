#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

struct Person {
    // declaration friend function of class Person
    friend std::istream &read(std::istream &is, Person &person);

    private:
    std::string name = "ali";
    std::string addr{"california"};

    public:
    // exercises 7.15 add constructor of Person
    Person() = default;
    Person(std::string name, std::string addr): name(name), addr(addr) {}
    Person(std::string name): name(name), addr("no addr") {}
    explicit Person(std::istream& is) { read(is, *this); };
    // end of exercises 7.15

    // 此处函数返回值为 const std::string& 类型
    const std::string& getName() const { return name; }
    const std::string& getAddr() const { return addr; }
};

// exercises 7.9
// exercises 7.19 set name, addr access level: private
// outside cant change the variable of private member, 
// with this segment, compile error
// unless it is friend of class:Person
std::istream &read(std::istream &is, Person &person)
{
    is >> person.name >> person.addr;
    return is;
}
// end of exercises 7.19

std::ostream &print(std::ostream &os, const Person &person)
{
    os << "Person name is " << person.getName() << std::endl
       << "Person addr is " << person.getAddr();
    return os; 
}
// end of exercises 7.9


#endif