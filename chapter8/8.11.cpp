#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

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

    for (const auto &item: people) {
        cout << item.name << " ";
        for (const auto &phone: item.phones) {
            cout << phone << " ";
        }
        cout << endl;
    }
    return 0;
}