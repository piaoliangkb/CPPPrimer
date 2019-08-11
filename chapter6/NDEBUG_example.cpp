#include <iostream>

using namespace std;

void print(const int ia[], size_t size)
{
    #ifndef NDEBUG
        cerr << "In file : " << __FILE__ << endl
             << __func__ << " : array size is " << size << endl 
             << "at line " << __LINE__ << endl
             << "at time " << __TIME__ << endl;
    #endif
    for (size_t i = 0; i < size; ++i)
    {
        cout << ia[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a[4] = {4, 3, 2, 1};
    print(a, 4);

    return 0;
}