#include <iostream>

using namespace std;

int main()
{
    int a;
    a = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2;
    cout << a << endl;

    a = ((12 / 3) * 4) + (5 * 15) + ((24 % 4) / 2);
    cout << a << endl;

    return 0;
}