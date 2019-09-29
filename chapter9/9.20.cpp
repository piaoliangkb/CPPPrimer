#include <list>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
    list<int> lst = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    deque<int> odd;   // 奇数
    deque<int> even;  // 偶数
    for (auto iter = lst.begin(); iter!=lst.end(); ++iter)
    {
        if (*iter % 2) odd.push_back(*iter);
        else even.push_back(*iter);
    }
    cout << "The odd number in list is : " ;
    for (auto &i: odd) cout << i << " ";
    cout << endl;
    cout << "The even number in list is : ";
    for (auto &i: even) cout << i << " ";
    cout << endl;
}