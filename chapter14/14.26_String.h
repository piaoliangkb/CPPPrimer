#ifndef _14_26_STRING_H
#define _14_26_STRING_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// now this is the same as which in ex13.50

class String {
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend bool operator==(const String &lhs, const String &rhs);
    friend bool operator!=(const String &lhs, const String &rhs);
    friend bool operator<(const String &lhs, const String &rhs);
    friend bool operator<=(const String *lhs, const String &rhs);
    friend bool operator>(const String *lhs, const String &rhs);
    friend bool operator>=(const String *lhs, const String &rhs);

public:
    String();

    String(const char *c);

    String(const std::string &);

    String(const String &);

    String &operator=(const String &);

    String(String &&) noexcept;

    String &operator=(String &&) noexcept;

    char &operator[](std::size_t n);

    const char &operator[](std::size_t n) const;

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

    auto first = alloc.allocate(1);
    content = first;
    alloc.construct(first++, '\0');
    last = first;
}

String::String(const char *c) {

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

    auto len = s.length();
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, s[i]);
    }
    alloc.construct(first++, '\0');
    last = first;
}

String::String(const String &rhs) {

    auto len = strlen(rhs.content);
    auto first = alloc.allocate(len + 1);
    content = first;
    for (int i = 0; i < len; ++i) {
        alloc.construct(first++, rhs.at(i));
    }
    alloc.construct(first++, '\0');
    last = first;
}

String &String::operator=(const String &rhs) {

    // backup rhs and free lhs
    char *fst = rhs.content;
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

    content = std::move(s.content);
    last = std::move(s.last);

    s.content = s.last = nullptr;
}

String &String::operator=(String &&s) noexcept {
    if (this != &s) {
        free();
        content = std::move(s.content);
        last = std::move(s.last);

        s.content = s.last = nullptr;
    }
    return *this;
}

void String::free() {

    if (content) {
        std::for_each(content, last, [this](char &c) { alloc.destroy(&c); });
    }
    alloc.deallocate(content, last - content);
}

String::~String() {

    free();
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.content;
    return os;
}

bool operator==(const String &lhs, const String &rhs) {
    return (lhs.size() == rhs.size()) &&
           (std::equal(lhs.content, lhs.last, rhs.content));
}

bool operator!=(const String &lhs, const String &rhs) { return !(lhs == rhs); }

bool operator<(const String &lhs, const String &rhs) {

    auto lbeg = lhs.content;
    auto rbeg = rhs.content;

    for (; (lbeg != lhs.last) && (rbeg != rhs.last); ++lbeg, ++rbeg) {
        if (*lbeg < *rbeg) return true;
        else if (*lbeg > *rbeg) return false;
    }
    
    return (lbeg == lhs.last) && (rbeg != rhs.last);
}

bool operator<=(const String &lhs, const String &rhs) {
    return !(rhs < lhs);  // !(rhs < lhs) equals to rhs >= lhs
}

bool operator>(const String &lhs, const String &rhs) {
    return rhs < lhs;
}

bool operator>=(const String &lhs, const String &rhs) {
    return !(lhs < rhs);
}

char &String::operator[](std::size_t n) {
    return content[n];
}

const char &String::operator[](std::size_t n) const {
    return content[n];
}
#endif