#include <iostream>

using namespace std;

int main()
{
    int a = 0, e = 0, i = 0, o = 0, u = 0;
    char c;
    while (cin >> c)
    {
        if (c == 'a' || c == 'A') ++a;
        else if (c == 'e' || c == 'E') ++e;
        else if (c == 'i' || c == 'I') ++i;
        else if (c == 'o' || c == 'O') ++o;
        else if (c == 'u' || c == 'U') ++u;
    }
    cout << a << endl;
    cout << e << endl;
    cout << i << endl;
    cout << o << endl;
    cout << u << endl;
    return 0;
}