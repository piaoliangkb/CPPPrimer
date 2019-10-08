#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    s.reserve(120);
    char c;
    while (cin >> c)
    {
        s += c;
    }
    cout << s.capacity() << endl;
    cout << s << endl;
}