#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> v{"1", "2", "3", "4", "5"};
    int count = 0;
    for (auto const& item : v)
    {
        count += stoi(item);
    }
    cout << "the total count of vector<string> for integer is " << count << endl;

    vector<string> v2{"3.14", "3.15", "5.66", "9.99"};
    double total = 0;
    for (auto const& item : v2)
    {
        total += stod(item);
    }
    cout << "the total count of vector<string> for double is " << total << endl;
}