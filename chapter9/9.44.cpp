#include <iostream>
#include <string>

using namespace std;

void change(string &s, const string &oldVal, const string &newVal)
{
    string::size_type i = 0;
    while(i != s.size())
    {
        //cout << s.substr(i, oldVal.size()) << endl;
        if (s.substr(i, oldVal.size()) == oldVal)
        {
            s.replace(i, oldVal.size(), newVal);
            i += newVal.size();
            //cout << s[i] << endl;
        }
        else {
            ++i;
        }
    }
}

int main()
{
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
        change(str, "thru", "through");
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