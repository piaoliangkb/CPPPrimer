#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<string, vector<string>> fam;
    string s;
    while (getline(cin, s))
    {
        auto split_pos = s.find(' ');
        string last_name = s.substr(0, split_pos);  // xing
        string first_name = s.substr(++split_pos, s.size()); // ming

        fam[last_name].push_back(first_name);
    }

    for (const auto &item : fam)
    {
        cout << "last_name is " << item.first << endl;
        cout << "children are : " ;
        for (const auto &name : item.second) cout << name << " ";
        cout << endl;
    }

    return 0;
}