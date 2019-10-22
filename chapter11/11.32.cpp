#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print_map(const map<string, set<string>>& mp)
{
    for (const auto &item : mp)
    {
        cout << item.first << " :";
        for (const auto &book : item.second)
        {
            cout << book << " ";
        }
        cout << endl;
    }
}

int main()
{
    multimap<string, string> authors = {
        {"Jason", "book1"},
        {"Jason", "book2"},
        {"Jason", "book3"},
        {"Jason", "announcement"},
        {"Didi", "book4"},
        {"Didi", "account"}
    };

    map<string, set<string>> ordered_au_and_book;

    for (const auto& item : authors)
    {
        ordered_au_and_book[item.first].insert(item.second);
    }

    print_map(ordered_au_and_book);
    

    return 0;
}