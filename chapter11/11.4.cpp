#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
    map<string, int> word_cnt;
    string word;
    while (cin >> word)
    {
        word.erase(remove_if(word.begin(), word.end(), 
                            [](const char c){return ispunct(c);}), word.end());
        for (auto &c: word) c = tolower(c);
        ++word_cnt[word];
    }
    for (const auto &w : word_cnt)
    {
        cout << w.first << " : " << w.second << endl;
    }

    return 0;
}
