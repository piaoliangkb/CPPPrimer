#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    vector<string> svec;
    svec.reserve(1024);
    string word;
    int i = 1048;
    while (i--)
    {
        svec.push_back("word");
    }
    cout << svec.size() << endl;
    svec.resize(svec.size() + svec.size()/2);
    cout << svec.size() << endl;
    cout << svec.capacity() << endl;
}