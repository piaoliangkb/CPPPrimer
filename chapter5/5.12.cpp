#include <iostream>

using namespace std;

int main()
{
    int a = 0, e = 0, i = 0, o = 0, u = 0, space = 0, tab = 0, newline = 0, ff = 0, fl = 0, fi = 0;
    char c, prec = '\0';
    while (cin >> std::noskipws >> c) // 让std::cin 读取空白字符
    {
        if (c == 'a' || c == 'A') ++a;
        else if (c == 'e' || c == 'E') ++e;
        else if (c == 'i' || c == 'I') {
            ++i;
            if (c == 'i' && prec == 'f') ++fi;
        }
        else if (c == 'o' || c == 'O') ++o;
        else if (c == 'u' || c == 'U') ++u;
        else if (c == ' ') ++space;
        else if (c == '\t') ++tab;
        else if (c == '\n') ++newline;
        else if (c == 'f') {
            if (prec == 'f') ++ff;
        }
        else if (c == 'l') {
            if (prec == 'f') ++fl;
        }
        prec = c;
    }
    cout << a << endl;
    cout << e << endl;
    cout << i << endl;
    cout << o << endl;
    cout << u << endl;
    cout << space << endl;
    cout << tab << endl;
    cout << newline << endl;
    cout << ff << endl;
    cout << fl << endl;
    cout << fi << endl;
    return 0;
}