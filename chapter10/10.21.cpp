#include <iostream>

using namespace std;

int main()
{
    int a = 10;
    auto f = [a]() mutable -> bool {
        if (a) {
            --a;
            return false;
        }
        else return true;
    };

    for (int i=0; i<20; ++i) {
        cout << boolalpha << "call of func " << i << " time. value is 0? " << f() << endl; 
    }

    return 0;
}