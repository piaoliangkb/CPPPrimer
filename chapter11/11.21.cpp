#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    map<string, int> word_cnt;
    string word;
    while (cin >> word)
    {
        ++word_cnt.insert({word, 0}).first -> second;
    }
    for (const auto &w : word_cnt)
    {
        cout << w.first << " : " << w.second << endl;
    }

    return 0;
}
