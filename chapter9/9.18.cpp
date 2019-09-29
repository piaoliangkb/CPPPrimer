#include <string>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
    deque<string> dq;
    string s;
    while (cin >> s)
    dq.push_front(s);
    for (deque<string>::iterator iter = dq.begin(); iter != dq.end(); ++iter)
    cout << *iter << endl;
}