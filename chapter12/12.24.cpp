#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    string s;
    int size;

    cin >> size;
    cin >> s;

    char *arr = new char[size + 1];
    for (int i = 0; i < size; ++i)
    {
        *(arr+i) = s[i];
    }
    *(arr+size) = '\0';

    cout << arr << endl;

    delete[] arr;

    return 0;
}