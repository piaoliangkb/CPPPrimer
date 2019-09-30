#include <vector>
#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

int main()
{
    list<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = v.begin();
    while (iter != v.end())
    {
        if (*iter & 0x1) {
            iter = v.insert(iter, *iter);
            ++iter; ++iter; // or advance(iter, 2);
        }
        else {
            iter = v.erase(iter);
        }
    }
    for (auto &i: v) cout << i << " ";
    cout << endl;
}