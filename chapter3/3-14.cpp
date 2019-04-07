#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    int val;
    while (cin >> val)
        v.push_back(val);

    for (auto i : v)
        cout << i << " ";

    return 0;
}