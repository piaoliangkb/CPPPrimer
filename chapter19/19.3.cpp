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
        pb->print();
    }
    {
        B *pb = new B;
        C *pc = dynamic_cast<C *>(pb);  // B* -> C* downcast
        if (pc == nullptr) std::cout << "cast error" << std::endl;
        else pc->print();
    }
    {
        A *pa = new D;
        B *pb = dynamic_cast<B *>(pa);
        pb->print();
    }
    {
        B *pb = new B;
        A *pa = dynamic_cast<A *>(pb);
        if (pa == nullptr)
            std::cout << "cast error" << std::endl;
        else
            pa->print();
    }
}