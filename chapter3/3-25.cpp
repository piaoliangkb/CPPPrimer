#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> scores(11, 0);
    int i;
    while (cin >> i)
    {
        if (i <= 100)
        {
            ++*(scores.begin() + i/10);
        }
    }
    for (auto i : scores)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}