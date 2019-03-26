#include <iostream>
#include <string>

std::string global_str; // empty string
int global_int; // zero

int main()
{
    int local_int; // undefined value
    std::string local_str; // empty string

    std::cout << global_int << " " << local_int << std::endl;
    std::cout << global_str << " " << local_str << std::endl;

    return 0; 
}