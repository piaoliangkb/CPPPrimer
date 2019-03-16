#include <iostream>

int main()
{
    int m, n;
    std::cout << "Please input two numbers :";
    std::cin >> m >> n;
    while (m <= n)
    {
        std::cout << m << " ";
        ++m;
    }
    std::cout << std::endl;
    return 0;
}