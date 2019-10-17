#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> words = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer", "consistent", "helloworld"};
    auto cnt = count_if(words.cbegin(), words.cend(), 
                        [](const string& s) { return s.size() > 6; });
    cout << cnt << endl;
    
    return 0;
}