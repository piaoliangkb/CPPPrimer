#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StrLessThan {
public:
    bool operator()(const string &s1, const string &s2) {
        return s1.size() < s2.size();
    }
};

class StrLongerThan {
public:
    StrLongerThan(size_t n) : sz(n) {}

    bool operator()(const string &s) { return s.size() > sz; }

private:
    size_t sz;
};

class Print {
public:
    void operator()(const string &s) {
        cout << s << " ";
    }
};

void elimDups(vector<string> &v) {
    sort(v.begin(), v.end());
    auto end_unique = unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);

    stable_sort(words.begin(), words.end(), StrLessThan());

    auto it = find_if(words.cbegin(), words.cend(), StrLongerThan(sz));

    auto count = words.end() - it;

    auto f = [count](const string &word, const string &ending) {
        return (count > 1) ? word + ending : word;
    };
    cout << "there are " << count << f(" word", "s") << " of length " << sz
         << " or longer" << endl;

    for_each(it, words.cend(), Print());
    cout << endl;
}

int main() {
    vector<string> v = {"hello", "this", "my",  "computer", "would",   "u",
                        "want",  "to",   "buy", "my",       "computer"};
    biggies(v, 4);

    return 0;
}