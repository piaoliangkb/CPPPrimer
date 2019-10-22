#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool find_and_remove(multimap<string, string>& mp, const string& author_name)
{
    auto it = mp.find(author_name);
    if (it != mp.end())
    {
        mp.erase(it);
        return true;
    }
    return false;
}

void print_map(const multimap<string, string>& mp)
{
    for (const auto &item : mp)
    {
        cout << item.first << " : " << item.second << endl;
    }
}

int main()
{
    multimap<string, string> authors = {
        {"Jason", "book1"},
        {"Jason", "book2"},
        {"Jason", "book3"},
        {"Jason", "announcement"},
        {"Didi", "book4"}
    };

    string delete1("Jason");
    string delete3("Tatum");
    
    find_and_remove(authors, delete1);
    find_and_remove(authors, delete3);
    print_map(authors);

    return 0;
}