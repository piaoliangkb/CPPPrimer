#include "String.h"
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

const char *string2::String::voidStr = "";

int main()
{

    {
        string1::String s("hello");
        string1::String s1(s);

        cout << s.c_str() << endl;
        cout << s1.c_str() << endl;

        string1::String s2 = std::move(s1);

        cout << s2.c_str() << endl;

        string1::String s3;
        s3 = std::move(s2);

        cout << s3.c_str() << endl;
    }

    {
        cout << "\n\nstarting a new scope\n";

        // String(const char*, size_t) -> String(const char *)
        string2::String s("something"); 
        
        cout << s.c_str() << endl;
        cout << s.size() << endl;

        cout << "s1 & s2 operation" << endl;
        string2::String s1(s);
        string2::String s2(std::move(s));

        cout << "s3 operation" << endl; 
        string2::String s3;
        s3 = std::move(s2);

        string2::String s4;
        cout << s4.c_str() << endl;
    }
    
    return 0;
}
