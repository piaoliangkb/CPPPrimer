#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool longer_than_five(const string &s)
{
    return s.size() > 5;
}

int main()
{
    vector<string> words = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer", "consistent", "helloworld"};
    auto split_point = partition(words.begin(), words.end(), longer_than_five);
    auto beg = words.begin();
    while (beg != split_point)
    {
        cout << *beg++ << endl;
    }

    return 0;
}