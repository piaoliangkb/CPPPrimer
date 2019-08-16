#include "person.h"

using std::cout;
using std::endl;

int main()
{
    Person p1;
    cout << p1.getName() << " " << p1.getAddr() << endl;
    print(cout, p1) << endl;

    Person p2("piaoliangkb", "sichuan univ");
    cout << p2.getName() << " " << p2.getAddr() << endl;
    print(cout, p2) << endl;

    Person p3("piaoliangkb");
    cout << p3.getName() << " " << p3.getAddr() << endl;
    print(cout, p3) << endl;

    Person p4(std::cin);
    cout << p4.getName() << " " << p4.getAddr() << endl;
    print(cout, p4) << endl;

    return 0;
}