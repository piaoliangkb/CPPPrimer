#include <iostream>

using namespace std;

// 函数形参使用引用而非范围for循环使用引用
int get_sum(initializer_list<int> &lst)
{
    int sum = 0;
    for (auto item : lst)
        sum += item;
    return sum;
}

int main()
{
    cout << get_sum({1, 2, 3, 4, 5}) << endl;
    cout << get_sum({10, 20, 30}) << endl;

    return 0;
}