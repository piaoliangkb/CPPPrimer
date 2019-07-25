#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len1 = v1.size(), len2 = v2.size();
    if (len1 < len2)
    {
        for (auto st1 = v1.begin(), st2 = v2.begin(); st1 != v1.end(); ++st1, ++st2)
        {
            if (*st1 != *st2) {
                cout << "v1 is not the prefix of v2" << endl;
                return 0;
            }
        }
    }
    else
    {
        for (auto st2 = v2.begin(), st1 = v1.begin(); st2 != v2.end(); ++st1, ++st2)
        {
            if (*st1 != *st2) {
                cout << "v2 is not the prefix of v1" << endl;
                return 0;
            }
        }
    }
    cout << "its ok" << endl;
    return 0;
}

// int main()
// {
//     vector<int> v1{0, 1, 1, 2};
//     vector<int> v2{0, 1, 1, 2, 2, 2};

//     auto size = v1.size() > v2.size() ? v2.size() : v1.size();
//     for (decltype(v1.size()) i=0; i < size; ++i)
//     {
//         if (v1[i] != v2[i]) {
//             cout << "false" << endl;
//             return 0;
//         }
//     }
//     cout << "true" << endl;
//     return 0;
// }
