#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    list<int> lst = {1, 2, 3, 4, 5};
    vector<int> v = {1, 2, 3, 4, 5, 6};
    cout << "vector == list ? "<<boolalpha << (vector<int>(lst.begin(), lst.end()) == v) << endl;
    cout << "vector < list ? "<<boolalpha << (vector<int>(lst.begin(), lst.end()) > v) << endl;
    cout << "vector > list ? "<<boolalpha << (vector<int>(lst.begin(), lst.end()) < v) << endl;
}