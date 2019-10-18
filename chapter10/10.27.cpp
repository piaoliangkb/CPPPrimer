#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 2, 3, 3, 5, 5, 6};
    list<int> lst1, lst2;
    unique_copy(v.cbegin(), v.cend(), inserter(lst1, lst1.begin()));
    for (auto &i : lst1) cout << i << " ";
    cout << endl;

    unique_copy(v.cbegin(), v.cend(), front_inserter(lst2));
    for (auto &i : lst2) cout << i << " ";
    cout << endl;

    return 0;
}