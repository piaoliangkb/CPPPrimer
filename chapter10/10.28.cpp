#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

void print(const list<int>& v)
{
    for (auto &i : v) cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> v1, v2, v3;

    // use inserter 
    // v1.begin() and v1.end() have the same effect
    copy(v.cbegin(), v.cend(), inserter(v1, v1.begin()));
    print(v1); // 1 2 3 4 5 6 7 8 9

    // use back_inserter
    copy(v.cbegin(), v.cend(), back_inserter(v2));
    print(v2); // 1 2 3 4 5 6 7 8 9

    // use front_inserter
    copy(v.cbegin(), v.cend(), front_inserter(v3));
    print(v3); // 9 8 7 6 5 4 3 2 1

    return 0;
}