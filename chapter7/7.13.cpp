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
            if (total.bookNo == trans.bookNo)
            {
                total.combine(trans);
            }
            else
            {
                total.Print();
                total = trans;
            }
        }
        total.Print();
    }
    else
    {
        std::cout << "No data input." << std::endl;
    }

    return 0;
}