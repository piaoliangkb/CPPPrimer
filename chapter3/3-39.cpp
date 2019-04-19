#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    string s1 = "A string example";
    string s2 = "A different string";
    if (s1 < s2) cout << "s1 < s2" << endl;
    else cout << "s1 !< s2" << endl;

    const char ca1[] = "A string example";
    const char ca2[] = "A different string";
    if (strcmp(ca1, ca2) > 0) cout << "ca1 > ca2" << endl;
    else cout << "ca1 !> ca2" << endl;
}