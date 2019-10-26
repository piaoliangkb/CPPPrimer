#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<int> p(new int(20));
    std::unique_ptr<int> q(p);
    std::unique_ptr<int> r = p;
}
/*
tempCodeRunnerFile.cpp:7:26: error: call to deleted constructor of 'std::unique_ptr<int>'
    std::unique_ptr<int> q(p);
*/