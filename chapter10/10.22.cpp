#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

bool check_size(const string &s, string::size_type sz)
{
    return s.size() <= sz;
}

int main()
{
    vector<string> words = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer", "consistent", "helloworld"};
    
    auto cnt = count_if(words.cbegin(), words.cend(), bind(check_size, _1, 6));
    cout << cnt << endl;
    return 0;  
}