#include <iostream>

using namespace std;

void f(int num) 
{
    int cnt = 5;
    auto f = [cnt] (const int i) { return i+cnt; };
    cout << "total count is " << f(num) << endl;
}

int main()
{
    f(10);
    f(15);
    return 0;
}