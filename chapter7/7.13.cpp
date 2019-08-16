#include "Sales_data.h"

int main()
{
    Sales_data total(std::cin); // 使用 Sales_data(std::istream &is) 构造函数
    if (!total.isbn().empty())
    {
        std::istream &is = std::cin;  // 使用 is 保存std::cin的内容
        while (is)
        {
            Sales_data trans(is);
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total) << std::endl;
                total = trans;
            }
        }
        print(std::cout, total) << std::endl;
    }
    else
    {
        std::cout << "No data input." << std::endl;
    }

    return 0;
}