#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator find(vector<int>::iterator begin, vector<int>::iterator end, int i)
{
    while (begin!=end)
    {
        ++begin;
        if (*begin == i) return begin;
    }
    return end;
}

int main()
{
    vector<int> v = {10, 9, 8, 7, 6, 5, 3, 2, 1};
    if (find(v.begin(), v.end(), 4) != v.end()){
        cout << "found it" << endl;
    }
    else {
        cout << "not found it" << endl;
    }

    return 0;
}