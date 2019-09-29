#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
    list<string> lst;
    string s;
    while (cin >> s)
    lst.push_back(s);
    for (list<string>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
    cout << *iter << endl;
}