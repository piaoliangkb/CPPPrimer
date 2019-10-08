#include <iostream>
#include <string>

using namespace std;

void change(string &s, const string &oldVal, const string &newVal)
{
    auto begin = s.begin();
    while(distance(begin, s.end()) >= oldVal.size())
    {
        
        if (string{begin, begin+oldVal.size()} == oldVal) {
            begin = s.erase(begin, begin+oldVal.size());
            begin = s.insert(begin, newVal.begin(), newVal.end());
            begin += newVal.size();
        }
        else {
            ++begin;
        }
    }
}

int main()
{
    {
        string s1 = "tho, he is fine with it";
        string s2 = "just walk across thru the road, tho its so hard";

        change(s1, "tho", "though");
        change(s2, "thru", "through");
        change(s2, "tho", "though");
        cout << s1 << endl;
        cout << s2 << endl;
    }
    {
        string str{"To drive straight thru is a foolish, tho courageous act."};
        change(str, "thru", "through");
        change(str, "tho", "though");
        std::cout << str << std::endl;
    }
    {
        string str{
            "To drive straight thruthru is a foolish, thotho courageous act."};
        change(str, "thru", "through");
        change(str, "tho", "though");
        std::cout << str << std::endl;
    }
    {
        string str{"To drive straight thru is a foolish, tho courageous act."};
        change(str, "thru", "thruthru");
        change(str, "tho", "though");
        std::cout << str << std::endl;
    }
    {
        string str{"my world is a big world"};
        change(str, "world",
                "worldddddddddddddddddddddddddddddddddddddddddddddddd");
        std::cout << str << std::endl;
    }
}