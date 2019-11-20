#include "TextQuery.h"
#include <fstream>

int main()
{
    std::ifstream ifs("data.txt");
    runQueries(ifs);
}