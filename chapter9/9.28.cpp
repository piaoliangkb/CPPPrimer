#include <iostream>
#include <forward_list>

using namespace std;

void findAndInsert(forward_list<string>& flst, const string& s1, const string& s2)
{
    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end())
    {
        if (*curr == s1) {
            flst.insert_after(curr, s2);
            return;
        }
        else {
            prev = curr;
            ++curr;
        }
    }
    flst.insert_after(prev, s2);
}

void print(const forward_list<string>& flst)
{
    for (auto &i: flst) cout << i << " ";
    cout << endl;
}

int main()
{
    forward_list<string> flst = {"this", "is", "my", "string"};
    findAndInsert(flst, "is", "INSERT FIRST TIME");
    print(flst);
    findAndInsert(flst, "cantfind", "INSERT SECOND TIME");
    print(flst);
    findAndInsert(flst, "INSERT", "insert third time");
    print(flst);
    findAndInsert(flst, "cantfind", "INSERT FORTH TIME");
    print(flst);
}