#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1, s2;
    do {
        cout << "Please enter 2 strings:" << endl;
        cin >> s1 >> s2;
        cout << (s1.size() < s2.size() ? s1 : s2) << endl;
    } while (true);
    return 0;
}