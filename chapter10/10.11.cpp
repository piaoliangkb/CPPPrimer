#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;

void print(const std::vector<std::string> v)
{
    for (auto &s: v) cout << s << " ";
    cout << endl;
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

void elimDups(std::vector<std::string> &v)
{
    cout << "before sort the sequence is:" ;
    print(v);

    std::sort(v.begin(), v.end());
    cout << "after sort the sequence is:";
    print(v);

    auto end_unique = std::unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
    cout << "after eliminate duplicate the sequence is:";
    print(v);
}

int main()
{
    std::vector<std::string> v = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer"};
    elimDups(v);
    std::stable_sort(v.begin(), v.end(), isShorter);
    print(v);

    std::vector<std::string> v1 = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    elimDups(v1);
    std::stable_sort(v1.begin(), v1.end(), isShorter);
    print(v1);

    return 0;
}