#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int arr1[] = {0, 2, 1, 5, 3};
    int arr2[] = {0, 2, 1, 4, 3};

    auto len1 = end(arr1) - begin(arr1);
    auto len2 = end(arr2) - begin(arr2);
    int equal = 1;

    if (len1 != len2) cout << "two arrays doesnot equal" << endl;
    else
    {
        int *a1begin = begin(arr1), *a2begin = begin(arr2), *a1end = end(arr1);
        for (; a1begin != a1end; ++a1begin, ++a2begin)
        {
            if (*a1begin != *a2begin)
            {
                cout << "two array has the same length, but doesnot equal" << endl;
                equal = 0;
                break;
            }
        }
        if(equal) cout << "two arrays equal" << endl;
    }

    vector<int> v1 = {0, 1, 2, 3, 4, 5};
    vector<int> v2 = {0, 1, 2, 3, 4, 5};
    if (v1 == v2)
    {
        cout << "two vector equal" << endl;
    }
    else{
        cout << "two vector doesnot equal" << endl;
    }

    return 0;
}