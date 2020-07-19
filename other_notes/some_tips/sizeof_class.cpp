#include <iostream>

using namespace std;

class A{

};

class B {
public:
    B(){}
    ~B(){}
};

class C {
public:
    C(){}
    virtual ~C() {}
};

int main() {
    A a;
    cout << "Empty class instace sizeof = " << sizeof(a) << endl; // 1 bytes##

    B b;
    cout << "Class with empty ctor, dtor sizeof = " << sizeof(b) << endl;  // 1 bytes

    C c;
    cout << "Class with virtual dtor, sizeof = " << sizeof(c) << endl; // 8 bytes
}