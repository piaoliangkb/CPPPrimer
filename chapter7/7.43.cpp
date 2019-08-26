#include <iostream>
#include <vector>

using namespace std;

class NoDefault {
public:
    NoDefault(int i): num(i) {}
    int num;
};

class C {
public:
    C(): item(4) {}
    NoDefault item;
};

int main()
{
    C c;
    cout << c.item.num << endl;

    vector<C> v(10);
    cout << v[1].item.num << endl;
    return 0;
}