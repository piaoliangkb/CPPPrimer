#include "14.16_String.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    String s1("helloworld"), s2("helloworld"), s3("cppprimer");
    
    if (s1 == s2) {
        cout << "s1 equals to s2." << endl;
    }
    else {
        cout << "s1 not equals to s2." << endl;
    }

    if (s1 == s3) {
        cout << "s1 equals to s3." << endl;
    }
    else {
        cout << "s1 not equals to s3." << endl;
    }

    String s4, s5;
    if (s4 == s5) {
        cout << "s4 equals to s5." << endl;
    }
    else {
        cout << "s4 not equals to s5." << endl;
    }

    return 0;
}