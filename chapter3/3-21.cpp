#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 如果我们在函数中对参数值不修改的话，建议使用const &来作为函数参数值类型
// const保证了不会修改，&保证了传入的是原参数的地址，而不是传递值，传递值在
// 执行函数的时候会在内存中重新构造，效率降低
// 如果需要对参数值进行修改，就不要加const
void checkAndPrint(const vector<int> &v)
{
    cout << "v.size = " << v.size() << endl;
    if (v.cbegin() != v.cend())
    {
        for (auto it = v.cbegin(); it != v.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void checkAndPrint(const vector<string> &v)
{
    cout << "v.size = " << v.size() << endl;
    if (v.cbegin() != v.cend())
    {
        for (auto it = v.cbegin(); it != v.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 42);
    vector<int> v4{10};
    vector<int> v5{10, 42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    checkAndPrint(v1);
    checkAndPrint(v2);
    checkAndPrint(v3);
    checkAndPrint(v4);
    checkAndPrint(v5);
    checkAndPrint(v6);
    checkAndPrint(v7);

    // two different implementations

    cout << "v1.size = " << v1.size() << endl;
    if (v1.cbegin() != v1.cend())
    {
        for (auto it = v1.cbegin(); it != v1.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v2.size = " << v2.size() << endl;
    if (v2.cbegin() != v2.cend())
    {
        for (auto it = v2.cbegin(); it != v2.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v3.size = " << v3.size() << endl;
    if (v3.cbegin() != v3.cend())
    {
        for (auto it = v3.cbegin(); it != v3.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v4.size = " << v4.size() << endl;
    if (v4.cbegin() != v4.cend())
    {
        for (auto it = v4.cbegin(); it != v4.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v5.size = " << v5.size() << endl;
    if (v5.cbegin() != v5.cend())
    {
        for (auto it = v5.cbegin(); it != v5.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v6.size = " << v6.size() << endl;
    if (v6.cbegin() != v6.cend())
    {
        for (auto it = v6.cbegin(); it != v6.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "v7.size = " << v7.size() << endl;
    if (v7.cbegin() != v7.cend())
    {
        for (auto it = v7.cbegin(); it != v7.cend(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;

    
}