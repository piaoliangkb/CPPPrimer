#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

class String {
public:
    String();

    String(const char *c);

    String(const std::string &);

    String(const String&);

    String& operator=(const String&);

    void printString() const { std::cout << content << std::endl; }

    char at(size_t i) const { return *(content + i); }

    size_t size() const { return (last - content) - 1; }

    ~String();

private:
    char *content;

    char *last; // off-the-end

    std::allocator<char> alloc;

    void free();
};

String::String() {
    std::cout << "[call func] : String()" << std::endl;

    auto first = alloc.allocate(1);
    content = first;
    alloc.construct(first++, '\0');
    last = first;
}

String::String(const char *c) {
    std::cout << "[call func] : String(const char*)" << std::endl;

    auto len = strlen(c);
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, *c++);
    }
    alloc.construct(first++, '\0');
    last = first;
}

String::String(const std::string &s) {
    std::cout << "[call func] : String(const std::string&)" << std::endl;

    auto len = s.length();
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, s[i]);
    }
    alloc.construct(first++, '\0');
    last = first;
}

String::String(const String& rhs) {
    std::cout << "[call func] : copy-constructor String(const String&)" << std::endl;

    auto len = strlen(rhs.content);
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, rhs.at(i));
    }
    alloc.construct(first++, '\0');
    last = first;
}

String& String::operator=(const String& rhs) {
    std::cout << "call func : copy-assignment-operator operator=(const String&)" << std::endl;

    // backup rhs and free lhs
    char* fst = rhs.content;
    auto len = rhs.size();
    free();

    // allocate new memory
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, *fst++);
    }
    alloc.construct(first++, '\0');
    last = first;

    return *this;
}

void String::free() {
    std::cout << "[call func] : free()" << std::endl;

    if (content) {
        std::for_each(content, last, [this](char &c) { alloc.destroy(&c); });
    }
    alloc.deallocate(content, last-content);
}

String::~String() {
    std::cout << "[call func] : ~String()" << std::endl;

    free();
}

int main() {
    {
        String s("hello, world");
        s.printString();
        std::cout << "s.size is : " << s.size() << std::endl;
    }

    {
        std::cout << "\n";
        std::string s1("this is a string in c++ standard library");
        String s2(s1);
        s2.printString();
        std::cout << "s.size is : " << s2.size() << std::endl;
    }

    {
        std::cout << "\n";
        String s("hello, world"), s2("PythonPLZ");
        s2.printString();
        std::cout << "s.size is : " << s2.size() << std::endl;
        s2 = s;
        s2.printString();
        std::cout << "s.size is : " << s2.size() << std::endl;
    }
}