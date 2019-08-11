/*
 * @Description: C++primer exercises 6.47
 * @Author: piaoliangkb
 * @Date: 2019-08-11 10:51:46
 * @LastEditTime: 2019-08-11 11:00:40
 * @LastEditors: Please set LastEditors
 */
#include <iostream>
#include <vector>

using namespace std;

void output(vector<int> &v)
{
    #ifndef NDEBUG
        cerr << __func__ << " print all items in a vector" << endl
             << "vector size is " << v.size() << endl
             << "execute time is " << __TIME__ << endl;
    #endif
    if (!v.empty())
    {
        auto last = v.back();
        v.pop_back();
        output(v);
        cout << last << " ";
    }
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6};
    output(v);

    return 0;
}