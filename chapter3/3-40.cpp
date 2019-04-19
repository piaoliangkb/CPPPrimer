#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    const char ca1[] = "this is my";
    const char ca2[] = " horse";

    size_t size = strlen(ca1) + strlen(ca2) + 1;
    char *ca3 = new char[size];

    strcpy(ca3, ca1);
    strcat(ca3, ca2);
    cout << ca3 << endl;

    return 0;
}