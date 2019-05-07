#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v{5, 4, 3, 2, 1};
    int arr[5];
    for (int i=0; i<5; ++i) arr[i] = v[i];
    for (auto i : arr) cout << arr[i] << " ";
    cout << endl;
}