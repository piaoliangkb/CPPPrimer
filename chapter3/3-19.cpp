#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v(10, 42);
    vector<int> v{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
    vector v;
    for(int i=0;i<10;i++)
        v.push_back(42);
    cout << "the first approach is better!" << endl;

    return 0;
}