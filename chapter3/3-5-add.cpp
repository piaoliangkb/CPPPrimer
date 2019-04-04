#include <iostream>
#include <string>

using namespace std;

int main()
{
    string res, s;
    while (cin >> s)
    {
        res += s;
    }
    cout << res << endl;
    return 0;
}