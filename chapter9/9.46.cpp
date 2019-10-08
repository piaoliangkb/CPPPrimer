#include <iostream>
#include <string>

using namespace std;

inline string addName(const string &name, const string &pre, const string &suff)
{
    string returnName = name;
    returnName.insert(0, pre);
    returnName.insert(returnName.size(), suff);
    return returnName;
}

int main()
{
    string pre = "Mr.", suff = " Jr.";
    cout << addName("Shaun Emery", pre, suff) << endl;
}