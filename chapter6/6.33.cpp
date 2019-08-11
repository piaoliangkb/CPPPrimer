/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-07 13:27:36
 * @LastEditTime: 2019-08-11 11:01:02
 * @LastEditors: Please set LastEditors
 */
#include <iostream>
#include <vector>

using namespace std;

void output(vector<int> &v, vector<int>::iterator it)
{
    if (it != v.end())
    {
    cout << *it << endl;
    output(v, ++it);  // or output(v, next(it));
    }
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6};
    output(v, v.begin());

    return 0;
}