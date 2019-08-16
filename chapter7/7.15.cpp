#include "person.h"

using std::cout;
using std::endl;

int main()
{
    Person p1;
    cout << p1.name << " " << p1.addr << endl;

    Person p2("piaoliangkb", "sichuan univ");
    cout << p2.name << " " << p2.addr << endl;

    Person p3("piaoliangkb");
    cout << p3.name << " " << p3.addr << endl;

    Person p4(std::cin);
    cout << p4.name << " " << p4.addr << endl;

    return 0;
}