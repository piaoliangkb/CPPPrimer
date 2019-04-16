#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int a[10];
    for (size_t i = 0; i < 10; ++i)
    {
        a[i] = i;
    }
    int copya[10];
    for (size_t i = 0; i < 10; ++i)
    {
        copya[i] = a[i];
    }
    for (auto i : copya)
    {
        cout << i << " ";
    }
    cout << endl;

    vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    vector<int> copyv(v);
    for (auto i : copyv)
    {
        cout << i << " ";
    }
    cout << endl;
}