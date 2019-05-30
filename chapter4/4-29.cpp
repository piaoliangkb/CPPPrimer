#include <iostream>

using namespace std;

int main()
{
    int x[10] , *p=x;
    cout << sizeof(x) << endl; // 40
    cout << sizeof(p) << endl; // 8 —— 表示指针所占空间大小。64位处理器上指针占8个字节64位，因为64位才能指向所有地址。
    cout << sizeof(*x) << endl;// 4
    cout << sizeof(*p) << endl;// 4
}