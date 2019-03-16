#include <iostream>

int main()
{
    int cur, val;
    if (std::cin >> cur)
    {
        int count = 1;
        while (std::cin >> val)
        {
            if (val == cur) count++;
            else
            {
                std::cout << cur << " occurs " << count << "times" << std::endl;
                cur = val;
                count = 1;
            }
        }
        std::cout << cur << "occurs " << count << "times" << std::endl;
    }
    return 0;
}