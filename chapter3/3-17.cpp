#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    vector<string> v;
    string str;
    while (cin >> str)
        v.push_back(str);
    
    for (auto &s : v)
    {
        for (auto &c : s)
            c = toupper(c);
    }
    for (auto s : v)
    {
        cout << s << endl;
    }

    return 0;
}