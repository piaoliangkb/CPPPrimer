#include <iostream>

using namespace std;

int main()
{
    auto f = [] (const int i1, const int i2) -> int {return i1+i2;};
    cout << f(3, 4) << endl;
    cout << f(100, 199) << endl;

    return 0;
}