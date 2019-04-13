#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;

    for (int i=10; i>0 ; --i)
        v.push_back(i);
    
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        *it *= 2;
    }
    
    for (auto i : v)
        cout << i << " ";
    cout << endl;

    return 0;

}