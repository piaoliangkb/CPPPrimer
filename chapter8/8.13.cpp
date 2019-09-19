#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string& s)
{
    return isdigit(s[0]);
}

string format(string s)
{
    // string.substr(begin, len) 从字符 begin 开始，跨越 len 个字符，拷贝
    return s.substr(0, 3) + "-" + s.substr(3, 3) + "-" + s.substr(6);
}

int main()
{
    string line, word;
    vector<PersonInfo> people;
    istringstream record;
    while (getline(cin, line)) {
        PersonInfo info;
        record.clear();
        record.str(line);
        record >> info.name;
        while (record >> word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    cout << people.size() << endl;

    for (const auto &item : people)
    {
        ostringstream rightnums, badnums;
        for (const auto &phone : item.phones)
        {
            if (!valid(phone))
                badnums << " " << phone;
            else
                rightnums << " " << format(phone);
        }

        if (badnums.str().empty())
        {
            cout << item.name << " " << rightnums.str() << endl;
        }
        else
        {
            cerr << "input error: " << item.name
                 << " invalid nums: " << badnums.str() << endl;
        }
    }
    return 0;
}