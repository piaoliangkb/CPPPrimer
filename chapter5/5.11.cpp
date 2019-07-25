#include <iostream>

using namespace std;

int main()
{
    int a = 0, e = 0, i = 0, o = 0, u = 0, space = 0, tab = 0, newline = 0;
    char c;
    while (cin >> std::noskipws >> c) // 让std::cin 读取空白字符
    {
        if (c == 'a' || c == 'A') ++a;
        else if (c == 'e' || c == 'E') ++e;
        else if (c == 'i' || c == 'I') ++i;
        else if (c == 'o' || c == 'O') ++o;
        else if (c == 'u' || c == 'U') ++u;
        else if (c == ' ') ++space;
        else if (c == '\t') ++ tab;
        else if (c == '\n') ++ newline;
    }
    cout << a << endl;
    cout << e << endl;
    cout << i << endl;
    cout << o << endl;
    cout << u << endl;
    cout << space << endl;
    cout << tab << endl;
    cout << newline << endl;
    return 0;
}