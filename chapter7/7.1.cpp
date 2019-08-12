#include "Sales_data.h"

int main()
{
    Sales_data total;
    if (std::cin >> total.bookNo >> total.units_sold >> total.revenue)
    {
        Sales_data trans;
        while (std::cin >> trans.bookNo >> trans.units_sold >> trans.revenue)
        {
            if (total.bookNo == trans.bookNo)
            {
                total.Adddata(trans);
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