#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main()
{
    allocator<string> alloc;
    string s;
    int n;

    cout << "allocate size : ";
    cin >> n;
    
    auto const p = alloc.allocate(n);
    auto q = p; 
    
    while (cin >> s && q != p + n)
    {
        alloc.construct(q++, s);
    }

    cout << "initial pointer points to : " << *p << endl;

    while (q != p)
    {
        cout << *(--q) << endl;
        alloc.destroy(q);
    }

    alloc.deallocate(p, n);

    return 0;
}