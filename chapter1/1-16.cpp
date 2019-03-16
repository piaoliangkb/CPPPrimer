#include <iostream>

int main()
{
    int val, sum = 0;
    // while (std::cin >> val)
    // {
    //     sum += val;
    // }
    for (; std::cin >> val ;)
    sum += val;
    std::cout << "the sum of input is "<< sum << std::endl;

    return 0;
}

/*
1 2 3 4 5^Z
the sum of input is 15
*/