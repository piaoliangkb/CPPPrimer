#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    constexpr size_t sz = 8;
    int arr[sz] = {8, 7, 6, 5, 4, 3, 2, 1};

    int *b = arr;
    int *e = end(arr);
    while (b != e)
    {
        *b = 0;
        ++b;
    }
    for (int *begin = arr; begin != end(arr); ++begin)
    {
        cout << *begin << " ";
    }
    cout << endl;

    return 0;
}