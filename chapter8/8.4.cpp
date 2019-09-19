#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void read(vector<string> &v, const string& filename)
{
    string temp;
    fstream fs(filename);
    if (fs)
    {
        while (getline(fs, temp))
        {
            v.push_back(temp);
        }
    }
}

int main()
{
    string filename = "data.txt";
    vector<string> v;
    read(v, filename);

    for (auto &s: v) {
        cout << s << endl;
    }
    

}