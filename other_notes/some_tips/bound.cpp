#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator test_std_lower_bound(vector<int> &v, int target) {
    vector<int>::iterator it = lower_bound(v.begin(), v.end(), target);
    return it;
}

vector<int>::iterator test_std_upper_bound(vector<int> &v, int target) {
    auto it = upper_bound(v.begin(), v.end(), target); 
    return it;
}

int lower_bd(vector<int> &v, int target) {
    int low = 0, high = v.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (target > v[mid]) {
            low = mid + 1;
        }
        // 如果 target 还小于 mid，就让 high 一直向左逼近
        // 一直到最后，high 会到 target 的左侧，
        // 退出循环时，low = high + 1 所在的位置就是最小的等于 target 的
        if (target <= v[mid]) {
            high = mid - 1;
        }
    }
    return low;
}

int upper_bd(vector<int> &v, int target) {
    int low = 0, high = v.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // 如果 target 比 mid 大，就让 low 一直向右逼近
        // 一直到最后，low 会到 target 的右侧
        // 恰好是第一个大于 target 的位置
        if (target >= v[mid]) {
            low = mid + 1;
        }
        if (target < v[mid]) {
            high = mid - 1;
        }
    }
    return low;
}

int main() {
    vector<int> v1 {0, 1, 2, 3, 4, 5};
    vector<int> v2 {3, 3, 4, 4, 5, 6};

    auto first4 = test_std_lower_bound(v2, 4);

    cout << *(first4 + 1) << endl;

    cout << *(first4 + 2) << endl;

    auto after4 = test_std_upper_bound(v2, 4);

    cout << *after4 << endl;

    cout << *(after4 - 1) << endl;

    cout << lower_bd(v1, 4) << endl;

    cout << lower_bd(v2, 4) << endl;

    cout << v2[upper_bd(v2, 4)] << endl;

    cout << v1[upper_bd(v1, 3)] << endl;

    return 0;
}