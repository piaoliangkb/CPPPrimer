#include <iostream>
#include <string>
#include "Sales_data.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    Sales_data total;
    ifstream ifs(argv[1]);
    if (ifs)
    {
        if (read(ifs, total)) 
        {
            Sales_data trans;
            while (read(ifs, trans))
            {
                if (total.isbn() == trans.isbn()) total.combine(trans);
                else
                {
                    print(cout, total) << endl;
                    total = trans;
                }   
            }
            print(cout, total) << endl;
        }
        else 
        {
            cerr << "read data from file not ok" << endl;
        }
    }
    else 
    {
        cout << "open data failed" << endl;
    }
    
}