#include <iostream>
#include <memory>

using namespace std;

int main()
{
    auto sp = make_shared<int>(20);
    auto p = sp.get();
    delete p;
    
    // double free or corruption (out)
    // Aborted (core dumped)
    // 程序块结束之后，仍然会释放 sp -> double free

    return 0;
}