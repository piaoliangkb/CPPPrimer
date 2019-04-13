#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    int i;
    while (cin >> i) v.push_back(i);
    if (v.cbegin() == v.cend())
    {
        cout << "nothing in the vector!" << endl;
    }
    else
    {
        cout << "the sum of neighbour is :" << endl;
        for (auto it = v.cbegin(); it+1 != v.cend(); it += 1)
        {
            cout << *it + *(it+1) << " ";
        }
        if (v.size() == 1)
            cout << *(v.begin()) << endl;

        cout << "the sum of first one and last one is :" << endl;
        for (auto bit = v.cbegin(), eit = v.cend()-1; bit < eit; ++bit, --eit)
        {
            cout << *bit + *eit << " ";
        }
        if (v.size()%2 == 1)
        {
            cout << *(v.cbegin() + v.size()/2) << endl;
        }
    }

    return 0;
}