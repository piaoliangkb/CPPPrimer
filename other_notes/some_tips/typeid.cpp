#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

class Book {
public:
    Book() {
    }
    virtual void func() {
        std::cout << "Book::func()" << std::endl;
    }
};

class Cppprimer : public Book {
public:
    Cppprimer() {
    }
    void func() override {
        std::cout << "Cppprimer::func()" << std::endl;
    }
};

int main()
{
    int a = 40;
    std::pair<std::vector<std::string>, std::string> pir;
    double *b = nullptr;

    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(pir).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;

    Cppprimer cpp;
    Book& bk = cpp;

    bk.func();
    std::cout << typeid(bk).name() << std::endl;

    Book* bk1 = &cpp;

    bk1->func();
    std::cout << typeid(*bk1).name() << std::endl;

    return 0;
}