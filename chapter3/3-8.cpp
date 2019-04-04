#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "this is my world!";
    decltype(s.size()) i = 0;
    while (i<s.size())
    {
        s[i] = 'X';
        ++i;
    }
    cout << s << endl;
}