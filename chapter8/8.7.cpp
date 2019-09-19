#include <iostream>
#include <string>
#include "Sales_data.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    Sales_data total;
    ifstream ifs(argv[1]);
    ofstream ofs(argv[2]);
    if (ifs && ofs)
    {
        if (read(ifs, total)) 
        {
            Sales_data trans;
            while (read(ifs, trans))
            {
                if (total.isbn() == trans.isbn()) total.combine(trans);
                else
                {
                    print(ofs, total) << endl;
                    total = trans;
                }   
            }
            print(ofs, total) << endl;
        }
        else 
        {
            ofs << "read data from file not ok" << endl;
        }
    }
    else 
    {
        ofs << "open data failed" << endl;
    }
    
}