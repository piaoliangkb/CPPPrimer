#include <iostream>

class A {
public:
    A() {}
    virtual ~A() = default;
    virtual void print() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    B() {}
    virtual ~B() = default;
    void print() override {
        std::cout << "B" << std::endl;
    }
};

class C : public B {
public:
    C() {}
    virtual ~C() = default;
    void print() override {
        std::cout << "C" << std::endl;
    }
};

class D : public B {
public:
    D() {}
    virtual ~D() = default;
    void print() override {
        std::cout << "D" << std::endl;
    }
};

int main() {
    {
        A *pa = new C;
        B *pb = dynamic_cast<B *>(pa);  // C* -> B* upcast 总是成功
        if (C *pc = dynamic_cast<C *>(pa)) {
            std::cout << "cast success" << std::endl;
            pc->print();
        } else {
            std::cout << "cast error" << std::endl;
            pa->print();
        }
    }

}