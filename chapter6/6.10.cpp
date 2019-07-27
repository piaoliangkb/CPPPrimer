#include <iostream>

using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp; 
}

int main()
{
    int a = 100, b = 200;
    int c = 300, d = 400;
    swap(&a, &b);
    swap(&c, &d);
    cout << a << " " << b << " " << c << " " << d << endl;

    return 0; 
}