#include <iostream>
#include <thread>

using namespace std;

void f() {
    cout << "Hello";
}

struct F {
    void operator()() { cout << "Parallel World!\n"; }
};

void user() {
    thread t1 {f};
    thread t2 {F()};

    t1.join();
    t2.join();
}

int main() 
{
    user();
}
