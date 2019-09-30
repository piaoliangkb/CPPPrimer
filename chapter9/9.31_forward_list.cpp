#include <vector>
#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

int main()
{
    forward_list<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto prev = v.before_begin();
    auto iter = v.begin();
    while (iter != v.end())
    {
        if (*iter & 0x1) {
            iter = v.insert_after(iter, *iter);
            prev = iter;
            ++iter;
        }
        else {
            iter = v.erase_after(prev);
        }
    }
    for (auto &i: v) cout << i << " ";
    cout << endl;
}