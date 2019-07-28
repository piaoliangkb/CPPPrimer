#include <iostream>
#include <string>

using namespace std;

bool hasUpper(const string &s)
{
    for (auto c : s)
    {
        if (isupper(c)) return true;
    }
    return false;
}

void toLower(string &s)
{
    for (auto &c : s)
    {
        if (isupper(c)) c = tolower(c);
    }
}
int main()
{
    string s = "ABCDefg";
    toLower(s);
    cout << hasUpper("abcd") << endl;
    cout << s << endl;
    return 0;
}