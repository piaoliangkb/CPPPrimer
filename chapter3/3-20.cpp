#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    int i;
    while (cin >> i)
        v.push_back(i);
    
    if (v.empty()) return -1;

    for (decltype(v.size()) i = 0; i+1 < v.size(); ++i)
    {
        cout << v[i] + v[i+1] << endl;
    }

    cout << endl << endl;
    // split by two lines

    for (decltype(v.size()) i = 0; i < v.size() / 2; i++)
    {
        cout << v[i] + v[v.size()-1-i] << endl;
    }

    if (v.size() % 2 != 0)
        cout << v[v.size()/2] << endl;

    return 0;
}