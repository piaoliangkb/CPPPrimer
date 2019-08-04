#include <iostream>

using namespace std;

int compare(const int &i, const int *const p)
{
    return (i > *p ? i : *p);
}

int main()
{
    int a = 20, b = 30, *p = &b;
    cout << compare(a, p) << endl;
    cout << compare(a, &b) << endl;

    return 0;
}