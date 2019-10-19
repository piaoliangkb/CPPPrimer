#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main()
{
    std::string s;
    int i;
    std::vector<std::pair<std::string, int>> v;
    while (std::cin >> s >> i)
    {
        // 列表初始化
        v.push_back({s, i});  

        // 显式构造
        v.push_back(std::pair<std::string, int>(s, i));

        // make_pair 生成 pair 对象
        v.push_back(std::make_pair(s, i));

        // emplace_back 直接构造
        v.emplace_back(s, i);
    }
    for (auto &item : v)
    {
        std::cout << item.first << " " << item.second << std::endl;
    }
    std::cout << std::endl;

    return 0;
}