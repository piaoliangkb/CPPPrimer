#include <vector>
#include <iostream>

using namespace std;

bool compare(const vector<int> &v1, const vector<int> &v2)
{
    if (v1.size() == v2.size())
    {
        for (decltype(v1.size()) i = 0; i<v1.size(); ++i)
        {
            if (v1.at(i) != v2.at(i)) 
            {
                cout << "v1 and v2 are not equal at " << i << endl;
                return false;
            }
        }
        return true;
    }
    return false;
}

int main()
{
    vector<int> v1 {100, 99, 98};
    vector<int> v2 {100, 99, 98};
    if (compare(v1, v2)) {
        cout << "two vector<int> equal." << endl;
    }
    else {
        cout << "two vector<int> not equal." << endl;
    }

    cout << boolalpha << 
    return 0; 
}