#include "User.h"
#include <iostream>
#include <string>

int main() {
    User usr("zl");
    usr.setSalary(1000);
    std::cout << usr.getSalary() << std::endl;
}