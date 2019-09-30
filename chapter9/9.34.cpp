#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    auto iter = v.begin();
    while (iter != v.end())
    {
        if (*iter % 2) 
        {   
            iter = v.insert(iter, *iter);
            advance(iter, 2);
        } else {
            ++iter;
        }
    }
    for (auto &i : v) cout << i << " ";
    cout << endl;
}