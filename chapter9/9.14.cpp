#include <list>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    list<const char*> lst{"this", "is", "a", "new", "life"};
    vector<string> v(lst.begin(), lst.end());
    for (auto &s: v) cout << s << " " ;
    cout << endl;

    vector<string> v1;
    v1.assign(lst.begin(), lst.end());
    for (auto &s: v1) cout << s << " " ;
    cout << endl;
}