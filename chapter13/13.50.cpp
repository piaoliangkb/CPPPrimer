#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

class String {
public:
    String() : content(nullptr), last(nullptr) {
        std::cout << "[call func] : String()" << std::endl;
    }

    String(const char *c);

    String(const std::string &);

    String(const String&);

    String& operator=(const String&);

    String(String &&) noexcept;

    String &operator=(String &&) noexcept;

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
    std::cout << "[call func] : copy-assignment-operator operator=(const String&)" << std::endl;

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

String::String(String &&s) noexcept {
    std::cout << "[call func] : move-constructor String(String &&)" << std::endl;

    content = std::move(s.content);
    last = std::move(s.last);

    s.content = s.last = nullptr;
}

String &String::operator=(String &&s) noexcept {
    std::cout << "[call func] : move-assignment-operator operator=(String&&)" << std::endl;
    if (this != &s) {
        free();
        content = std::move(s.content);
        last = std::move(s.last);

        s.content = s.last = nullptr;
    }
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
    std::vector<String> v;

    std::cout << "begin push_back : hello" << std::endl;
    v.push_back("hello");
    std::cout << "after push_back : hello" << std::endl;

    std::cout << "begin push_back : hi" << std::endl;
    v.push_back("hi");
    std::cout << "after push_back : hello" << std::endl;

    std::cout << "begin emplace_back : cppprimer" << std::endl;
    v.emplace_back("cppprimer");
    std::cout << "after emplace_back : cppprimer" << std::endl;

    std::cout << "v.size is : " << v.size() << std::endl;
    for (const auto &item : v) {
        item.printString();
    }
}