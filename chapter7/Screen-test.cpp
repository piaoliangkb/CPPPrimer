#include "Screen.h"

using std::cout;

int main()
{
    const class Screen a(2, 3, 'm');
    a.display(cout);

    struct Screen b(2, 2, 'n');
    b.set('q').display(cout);

    return 0;
}