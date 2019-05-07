#include <iostream>

using namespace std;

int main()
{
    int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    cout << "now a[3][4] is :" << endl;
    for (auto &i : a)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

    int (*p)[4] = a;

    // p[i]代表p指向的地址偏移多少，因为p是一个指向四个元素数组的指针，p[1]则向下偏移一列
    // *p[1]则表示下一列的第一个数
    cout << "print *p[i] :(there is only three rows, so it will be overflow)" << endl;
    for (int i=0; i<4; ++i)
    {
        cout << *p[i] << " ";
    }
    cout << endl << endl;

    // *p代表指向当前一行数组的指针，[i]代表第几个数
    cout << "print (*p)[i] :" << endl;
    for (int i=0; i<4; ++i)
    {
        cout << (*p)[i] << " ";
    }
    cout << endl;   
    return 0;
}