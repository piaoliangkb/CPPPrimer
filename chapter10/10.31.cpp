#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    istream_iterator<int> int_it(cin), eof;
    vector<int> v(int_it, eof);
    sort(v.begin(), v.end(), [](const int i1, const int i2) { return i1 > i2; });
    unique_copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));

    return 0;
}