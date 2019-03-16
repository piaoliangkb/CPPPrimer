#include <iostream>

int main()
{
    std::cout << "/*" << std::endl;
    std::cout << "*/" << std::endl;
    std::cout << /* "*/" */ << std::endl; // this line has an error
    std::cout << /* "*/" /* "*/" */ << std::endl; 
    
    return 0;
}

/*
zl@LAPTOP-ZL:~/cppprimer/chapter1$ sudo g++ -o 1-8output 1-8.cpp
1-8.cpp:5:24: warning: missing terminating " character
     std::cout << /* "*/" */ << std::endl;
                        ^
1-8.cpp:5:24: error: missing terminating " character
     std::cout << /* "*/" */ << std::endl;
                        ^~~~~~~~~~~~~~~~~~~
1-8.cpp: In function ‘int main()’:
1-8.cpp:7:5: error: expected primary-expression before ‘return’
     return 0;
/*