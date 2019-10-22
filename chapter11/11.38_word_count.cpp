#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    unordered_map<string, int> umap;
    string word;
    while (cin >> word) {
        ++umap[word];
    }
    for (const auto& item : umap) {
        cout << item.first << " " << item.second << endl;
    }

    return 0;
}