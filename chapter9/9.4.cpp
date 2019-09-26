#include <iostream>
#include <vector>

using namespace std;

bool find(vector<int>::iterator begin, vector<int>::iterator end, int i)
{
    while (begin!=end)
    {
        ++begin;
        if (*begin == i) return true;
    }
    return false;
}

int main()
{
    vector<int> v = {10, 9, 8, 7, 6, 5, 3, 2, 1};
    if (find(v.begin(), v.end(), 3)){
        cout << "found it" << endl;
    }
    else {
        cout << "not found it" << endl;
    }

    return 0;
}