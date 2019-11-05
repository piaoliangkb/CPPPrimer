#include <iostream>

using std::cout;
using std::endl;

class numbered {
public:
    numbered() {
        static int unique = 100;
        mysn = unique++;
    }
    unsigned mysn;
};

void f(numbered s) {
    cout << s.mysn << endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a); f(b); f(c);
}