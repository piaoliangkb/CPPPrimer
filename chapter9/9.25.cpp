#include <vector>
#include <iostream>

using namespace std;

void print(const vector<int>& v)
{
    for (auto &i: v) cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    auto iter1 = v.begin(), iter2 = v.begin();
    iter1 = v.erase(iter1, iter2);
    cout << *iter1 << endl;
    print(v);

    auto iter3 = v.end(), iter4 = v.end();
    iter3 = v.erase(iter3, iter4);
    cout << *iter3 << endl;
    print(v);
}