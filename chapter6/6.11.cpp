#include <iostream>

using namespace std;

void reset(int &i)
{
    i *= 2;
}

int main()
{
    int a = 4, b = 5;
    reset(a);
    reset(b);
    cout << a << " " << b << endl;

    return 0;
}