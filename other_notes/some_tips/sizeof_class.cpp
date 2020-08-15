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
    cout << "Sizeof a empty class = " << sizeof(A) << endl;  // 1 bytes
    A a;
    cout << "Empty class instace sizeof = " << sizeof(a) << endl; // 1 bytes
    A aa;
    // address of two different instances are different
    cout << "Address of instance a: " << &a << endl;
    cout << "Address of instance aa: " << &aa << endl;

    cout << "Sizeof a class with ctor, dtor = " << sizeof(B) << endl;  // 1 bytes
    B b;
    cout << "Class with empty ctor, dtor sizeof = " << sizeof(b) << endl;  // 1 bytes

    cout << "Sizeof a class with virtual function = " << sizeof(C) << endl;  // 8 bytes
    C c;
    cout << "Class with virtual dtor, sizeof = " << sizeof(c) << endl; // 8 bytes
}