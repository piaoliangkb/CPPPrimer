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
        auto res = word_cnt.insert(make_pair(word, 1));
        if (!res.second) {
            ++res.first -> second;
        }
    }
    for (const auto &w : word_cnt)
    {
        cout << w.first << " : " << w.second << endl;
    }

    return 0;
}
