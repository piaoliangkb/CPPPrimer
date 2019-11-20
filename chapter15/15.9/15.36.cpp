#include "Query.h"
#include "Query_base.h"
#include "BinaryQuery.h"
#include "WordQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

int main()
{
    Query q = Query("fiery") & Query("bird") | Query("wind");

    std::cout << "---------------------" << std::endl;

    cout << q;
}