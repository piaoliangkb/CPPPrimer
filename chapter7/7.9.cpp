#include "person.h"
#include <iostream>

int main()
{
    Person person1;
    while (read(std::cin, person1))
    {
        print(std::cout, person1) << std::endl;
    }

    return 0;
}