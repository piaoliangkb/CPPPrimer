#include <iostream>

using std::cout;
using std::endl;

class numbered {
public:
    numbered() {
        static unsigned unique = 100;
        mysn = unique++;
    }

    numbered(const numbered& rhs) {
        mysn = rhs.mysn+1;
    }
    unsigned mysn;
};

void f(const numbered& s) {
    cout << s.mysn << endl;
}

int main()
{
    numbered a, b = a, c = b;
    cout << a.mysn << " " << b.mysn << " " << c.mysn << endl; 
    f(a); f(b); f(c);
}