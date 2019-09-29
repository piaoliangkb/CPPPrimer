#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> v(ia, end(ia));
    list<int> lst(v.begin(), v.end());
    // for (auto &i: ia)
    // {
    //     v.push_back(i);
    //     lst.push_back(i);
    // }
    auto iter1 = v.begin();
    while (iter1 != v.end())
    {
        if (!(*iter1 & 0x1)) iter1 = v.erase(iter1);
        else ++iter1;
    }
    auto iter2 = lst.begin();
    while (iter2 != lst.end())
    {
        if (*iter2 & 0x1) iter2 = lst.erase(iter2);
        else ++iter2;
    }
    for (auto &i: v)
    {
        cout << i << " ";
    }
    cout << endl;
    for (auto &i: lst)
    {
        cout << i << " ";
    }
    cout << endl;
}