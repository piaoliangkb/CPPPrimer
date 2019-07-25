#include <iostream>

using namespace std;

int main()
{
    int count = 0;
    char c;
    while (cin >> c)
    {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            count ++;
    }
    cout << "the number of vowels is " << count << endl;
    return 0;
}