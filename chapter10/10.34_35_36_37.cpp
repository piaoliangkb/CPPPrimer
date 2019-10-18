#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};

    // 10.34
    for (auto it = v.crbegin(); it != v.crend(); ++it)
        cout << *it << " ";
    cout << endl;

    // 10.35
    for (auto it = v.cend(); it != v.cbegin();)
    {
        cout << *--it << " ";
    }
    cout << endl;

    // 10.36
    list<int> lst = {1, 0, 2, 0, 3, 0, 4, 5, 6};
    auto pos = find(lst.crbegin(), lst.crend(), 0);
    cout << *pos << "in front of " << *pos.base() << endl;

    // 10.37
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> lst1(vec.crbegin()+2, vec.crbegin()+7);
    for (auto &i: lst1) cout << i << " ";
    cout << endl;

    // 或者用 reverse_copy
    list<int> lst2;
    reverse_copy(vec.cbegin()+3, vec.cbegin()+8, back_inserter(lst2));
    for (auto &i: lst2) cout << i << " ";
    cout << endl;


}