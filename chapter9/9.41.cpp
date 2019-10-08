#include<iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<char> v{'H', 'E', 'R', 'O', 'N', 'E', 'V', 'E', 'R', 'D', 'I', E};
    string s(v.begin(), v.end());
    cout << s << endl;
}