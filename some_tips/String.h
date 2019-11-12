#ifndef STRING_H
#define STRING_H

#include <cassert>
#include <cstring>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

namespace string1 {

class String {
public:
    String() : data(new char[1]) {
        *data = '\0';
    }

    String(const char* s) : data(new char[strlen(s) + 1]) {
        cout << "[call func] String(const char*)" << endl;

        strcpy(data, s);
    }

    String(const String &rhs) : data(new char[rhs.size() + 1]) {
        cout << "[call func] String(const String&)" << endl;

        strcpy(data, rhs.c_str());
    }

    String(String &&rhs) noexcept {
        cout << "[call func] String(String &&) noexcept" << endl;

        data = std::move(rhs.data);
        rhs.data = nullptr;
    }

    ~String() {
        cout << "[call func] ~String()" << endl;

        delete[] data;
    }

    String& operator=(String rhs) noexcept {
        cout << "[call func] String& operator=(String)" << endl;

        swap(rhs);
        return *this;
    }

    size_t size() const { return strlen(data); }

    const char* c_str() const { return data; }

    void swap(String &rhs) { std::swap(data, rhs.data); }

private:
    char* data;
};

}

namespace string2 
{

class String {
public:
    String() : data(nullptr), len(0) {
        cout << "[call func] String()" << endl;
    }

    String(const char* s, size_t length) {
        cout << "[call func] String(const char*, size_t)" << endl;

        if (length > 0) {
            data = new char[length + 1];
            memcpy(data, s, length);
            data[length] = '\0';
            len = length;
        } 
        else {
            assert(data == nullptr);
        }
    }

    String(const char* s) : String(s, strlen(s)) {
        cout << "[call func] String(const char*)" << endl;
    }

    String(const String& rhs) : String(rhs.data, rhs.len) {
        cout << "[call func] String(const String&)" << endl;
    }

    String(String&& rhs) noexcept : data(rhs.data), len(rhs.len) {
        cout << "[call func] String(String&&)" << endl;

        rhs.data = nullptr;
        rhs.len = 0;
    }

    ~String() {
        delete[] data;
    }

    String& operator=(String rhs) {
        cout << "[call func] String& operator=(String rhs)" << endl;
        
        std::swap(data, rhs.data);
        std::swap(len, rhs.len);
        return *this;
    }

    const char* c_str() const { return data ? data : voidStr; }

    size_t size() const { return len; }

private:
    char *data;
    size_t len;
    static const char* voidStr;
};

}

#endif