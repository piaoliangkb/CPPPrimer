#ifndef _STATIC_AND_EXTERN_H_
#define _STATIC_AND_EXTERN_H_

#include <string>

class Str {
public:
    Str() = default;
    Str(const std::string &s) : str(s) {}

    std::string getStr() const { return str; }
private:
    std::string str;
};

static Str static_s;
extern Str extern_s;

static int x;

#endif