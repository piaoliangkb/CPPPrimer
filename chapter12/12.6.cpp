#include <vector>
#include <memory>
#include <iostream>

std::vector<int>* make_vector()
{
    return new std::vector<int>();
}

void read_to_vec(std::vector<int>* v)
{
    int num;
    while (std::cin >> num) {
        v->push_back(num);
    }
}

void print_vec(std::vector<int>* v)
{
    for (const auto &i : *v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    auto vec = make_vector();
    read_to_vec(vec);
    print_vec(vec);

    delete vec;

    return 0;
}