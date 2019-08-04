#include <iostream>

using namespace std;

void swap(const int* &p1, const int* &p2)
{
    auto temp = p1;
    p1 = p2;
    p2 = temp;
}

int main()
{
    const int a = 40, b = 50;
    const int *p1 = &a, *p2 = &b;  // auto p1 = &a, p2 = &b;
    cout << "before swap:" << endl;
    cout << "p1 = " << *p1 << " p2 = " << *p2 << endl;
    swap(p1, p2);
    cout << "after swap" << endl;
    cout << "p1 = " << *p1 << " p2 = " << *p2 << endl;

    return 0;
}