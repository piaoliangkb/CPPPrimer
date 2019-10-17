#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool check_size(const string& s, string::size_type sz)
{
    return s.size() < sz;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    string s = "django";
    auto it = find_if(v.cbegin(), v.cend(), bind(check_size, s, _1));
    cout << *it << endl;
}