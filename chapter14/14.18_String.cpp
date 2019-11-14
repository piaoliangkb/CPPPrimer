#include "14.18_String.h"
#include <iostream>

using namespace std;

void printCmp(const String &s1, const String &s2) {
    cout << "s1 = " << s1 << " s2 = " << s2 << endl;
    cout << boolalpha
         << "s1 < s2 : " << (s1 < s2) << endl
         << "s1 <= s2 : " << (s1 <= s2) << endl
         << "s1 > s2 : " << (s1 > s2) << endl
         << "s1 >= s2 : " << (s1 >= s2) << endl;
    cout << endl;
}

int main()
{
    String s1("abcc"), s2("abcc"), s3("abc"), s4("abd");
    printCmp(s1, s2);
    printCmp(s1, s3);
    printCmp(s3, s4);
    return 0;
}