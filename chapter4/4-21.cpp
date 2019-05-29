#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for (auto &i : v)
    {
        i % 2 == 0 ? : i *=2;
    }
    for (auto x : v) cout << x << " ";
    
    return 0;
}