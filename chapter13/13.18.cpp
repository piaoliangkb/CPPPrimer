#include <iostream>
#include <string>

class Employee {
public:
    Employee() : number(num++) {}

    Employee(const std::string& s) : name(s), number(num++) {}
    
    static unsigned num;
    std::string name;
    unsigned number;
};

unsigned Employee::num = 1000;

int main()
{
    Employee e1("zhangli"), e2;
    std::cout << e1.name << " " << e1.number << std::endl;
    std::cout << e2.name << " " << e2.number << std::endl;

}