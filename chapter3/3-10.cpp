#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s, res;
    cin >> s;
    for (auto c : s)
    {
        if (!ispunct(c)) res += c;
    }

    cout << res << endl;

    return 0;
}