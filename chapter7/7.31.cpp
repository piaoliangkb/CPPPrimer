#include <iostream>

using namespace std;

class Y;

class X {
    public:
    int val = 0;
    Y* y = nullptr;
};

class Y {
    public:
    int val = 1;
    X x;
};

int main()
{
    Y item;
    cout << item.val << endl;
    cout << item.x.val << endl;

    X item1;
    item1.y = &item;
    cout << item1.val << endl;
    cout << item1.y->val << endl;

    return 0;
}