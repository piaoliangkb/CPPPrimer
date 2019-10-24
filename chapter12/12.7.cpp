#include <memory>
#include <vector>
#include <iostream>

std::shared_ptr<std::vector<int>> make_vec()
{
    auto p = std::make_shared<std::vector<int>>();
    return p;
}

void read_to_vec(const std::shared_ptr<std::vector<int>> p)
{
    int num;
    while (std::cin >> num) {
        p->push_back(num);
    }
}

void print_vec(const std::shared_ptr<std::vector<int>> p)
{
    for (const auto &i : *p)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    auto p = make_vec();
    read_to_vec(p);
    print_vec(p);

    return 0;
}