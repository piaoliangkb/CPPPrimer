#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> text;
    map<string, set<int>> word2line;

    ifstream infile("12.27_text.txt");
    string line;
    int line_no = 0;
    while (getline(infile, line)) {

        text.push_back(line);
        
        istringstream iss(line);
        string word;

        while (iss >> word) {
            word.erase(remove_if(word.begin(), word.end(),
                                    [](const char c) { return ispunct(c);}),
                        word.end());
            transform(word.begin(), word.end(), word.begin(),
                        [](char c){ return tolower(c);});

            word2line[word].insert(line_no);
        }

        ++line_no;
    }

    string word;
    do {
        cout << "Please enter the word you want to search:";
        cin >> word;

        auto res = word2line.find(word);
        if (res != word2line.end()) {
            auto occurtimes = res->second.size();
            cout << word << " occurs " << occurtimes << " times" << endl;

            for (const auto &item: res->second) {
                cout << "\t(line" << item << ") " << text[item] << endl;
            }
        }
        else {
            cout << word << " occurs 0 times." << endl;
        }
    } while (true);

    return 0;
}