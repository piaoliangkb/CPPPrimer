#include <memory>
#include <iostream>

using namespace std;

void process(shared_ptr<int> ptr)
{
    cout << "In func [process] the shared_pointer's reference is " << ptr.use_count() << endl;
}

int main()
{
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p.get()));

    cout << p.use_count() << endl;
    cout << *p << endl;

    return 0;
}