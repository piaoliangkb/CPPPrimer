#include <iostream>
#include <vector>

using namespace std;

void output(vector<int> &v, vector<int>::iterator it)
{
    if (it != v.end())
    {
    cout << *it << endl;
    output(v, ++it);  // or output(v, next(it));
    }
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6};
    output(v, v.begin());

    return 0;
}