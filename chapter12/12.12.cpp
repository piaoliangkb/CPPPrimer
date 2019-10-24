#include <memory>
#include <iostream>

using namespace std;

void process(shared_ptr<int> ptr)
{
    cout << "In func [process] the shared_pointer's reference is " << ptr.use_count() << endl;
}

int main()
{
    auto p = new int(20);
    auto sp = make_shared<int>();

    process(sp);

    // no known conversion from 'int *' to 'shared_ptr<int>' for 1st argument
    // process(new int());
    // process(p);

    // 合法，但是 process 函数执行结束后
    // 传进去的临时变量 p 指向的内存会被释放
    // p 是一个悬空指针
    process(shared_ptr<int>(p));
    cout << *p << endl;

    return 0;
}