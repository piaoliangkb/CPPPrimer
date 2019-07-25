#include <iostream>
#include <string>

using namespace std;

int main()
{
    string prev="", s;
    int flag = 0;
    while (cin >> s)
    {
        if (s == prev) {
            cout << s << endl;
            flag = 1;
            break;
        }
        else {
            prev = s;
        }
    }
    if (flag == 0) cout << "no repeated words" << endl;
    return 0;
}