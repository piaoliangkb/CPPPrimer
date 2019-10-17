#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print(const vector<string> &v)
{
    for (auto &s: v) cout << s << " ";
    cout << endl;
}

void elimDups(vector<string> &v)
{
    cout << "before sort the sequence is :";
    print(v);


    sort(v.begin(), v.end());
    cout << "after sort the sequence is :";
    print(v);

    auto end_unique = unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
    cout << "after eliminate duplicate the sequence is :";
    print(v);

}

int main()
{
    vector<string> v = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer"};
    elimDups(v);

    return 0;

}