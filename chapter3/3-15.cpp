#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    vector<string> v;
    string s;
    while (cin >> s)
        v.push_back(s);

    for (auto str : v)
        cout << str << " ";
        
    return 0;
}