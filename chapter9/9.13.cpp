#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::vector;
using std::cout;
using std::endl;

int main()
{
    list<int> lst = {4, 5, 6, 7, 8, 9};
    vector<double> v(lst.begin(), lst.end());

    for (const auto &item: v) cout << item << " ";
    cout << endl;

    vector<double> v1 = {3.14, 4.13, 5.22, 6.66};
    list<int> lst1(v1.begin(), v1.end());
    for (auto iter = lst1.begin(); iter != lst1.end(); ++iter)
    {
        cout << *iter << " ";
    }
}