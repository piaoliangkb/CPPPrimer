#include <iostream>
#include <string>

class ss : public std::string {
public:
    ss(const std::string &s, int *n) : std::string(s), num(n) {}

private:
    int *num;
};

class AWOV {
public:
    virtual ~AWOV() = 0;
};

AWOV::~AWOV() {}

class BWOV : public AWOV {
public:
    ~BWOV() { std::cout << "~BWOV()" << std::endl; }
};

int main() {
    {
        int num = 66;
        ss str("hello", &num);
        std::cout << str.c_str() << std::endl;

        ss *pss = new ss("hahah", &num);
        std::string *ps;

        ps = pss;

        delete ps;
    }

    { BWOV BW; }
}