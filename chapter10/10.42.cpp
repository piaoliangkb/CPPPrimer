#include <iostream>
#include <list>
#include <string>

using namespace std;

void elimDups(list<string> &words)
{
    words.sort();
    words.unique();
}

int main()
{
    list<string> lst = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer"};
    elimDups(lst);
    for (auto &s: lst) cout << s << " ";
    cout << endl;

    return 0;
}