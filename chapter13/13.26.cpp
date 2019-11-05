#include <iostream>
#include "13.26_StrBlob.h"

using namespace std;

int main()
{
    StrBlob sb{"hello", "hi", "flask", "django"};
    cout << sb.size() << endl;
    StrBlob sb1 = sb;
    cout << sb1.front() << endl;
    cout << sb1.back() << endl;

    StrBlob sb2{"using", "namespace", "std"};
    sb2 = sb;
    cout << sb2.front() << endl;
    cout << sb2.back() << endl;

    return 0;
}