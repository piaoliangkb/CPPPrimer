#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    ifstream ifs("data_8_6.txt");
    if (ifs)
    {
        string s;
        vector<string> v;
        while (getline(ifs, s)) {
            v.push_back(s);
        }

        istringstream iss;
        for (const auto &i: v)
        {
            iss.clear();
            iss.str(i);
            string word;
            while (iss >> word) cout << word << endl;
        }
    }
    return 0;
}