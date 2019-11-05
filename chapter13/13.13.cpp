#include <iostream>
#include <vector>

struct X {
    X() { std::cout << "X()" << std::endl; }
    X(const X&) { std::cout << "X(const X&)" << std::endl; }
    ~X() { std::cout << "~X()" << std::endl; }
    X& operator=(const X&) {
        std::cout << "X& operator=(const X&)" << std::endl;
        return *this;
    }
};

int main()
{
    { // passed by non-ref and reference params
        std::cout << "this is passed by reference and non-reference test:" << std::endl;

        X temp; // X()
        auto f_non_ref = [](const X) { std::cout << "in func f_non_ref" << std::endl; };

        f_non_ref(temp); // 拷贝构造函数 X（const X&）-> 析构函数 ~X()

        auto f_ref = [](const X &) { std::cout << "in func f_ref" << std::endl; };

        f_ref(temp);
    } // temp 析构 ~X()

    std::cout << std::endl;

    {
        X *temp = new X(); // X()
        delete temp;       // ~X()
    }

    std::cout << std::endl;

    {
        X x1, x2, x3; // X() X() X()
        std::vector<X> vec{x1, x2}; // X(const X&)*4 两个拷贝到初始化列表中，两个用作拷贝给vector的元素 ~X() ~X() 拷贝到列表结束
        std::cout << "after vector initialization" << ", now the vector capacity is : " << vec.capacity() << std::endl;
        vec.push_back(x3);  // X(const X&)*3 存储空间重新分配，拷贝3次 ~X() ~X() 原来两个位置的元素 x1, x2 调用析构函数
        std::cout << "after push_back x3, now the vector capacity is : " << vec.capacity() << std::endl;
    } // 离开作用域 x1, x2, x3 调用析构函数，vector 调用析构函数，其元素全部销毁，~X()*6
}