#include "AndQuery.h"
#include "BinaryQuery.h"
#include "OrQuery.h"
#include "Query.h"
#include "Query_base.h"
#include "WordQuery.h"
#include "TextQuery.h"
#include "NotQuery.h"

#include <fstream>

int main() {
    std::ifstream ifs("data.txt");
    TextQuery tq(ifs);

    Query q = Query("fiery") & Query("bird") | Query("wind");
    std::cout << q << std::endl;
    print(std::cout, q.eval(tq));

    Query q1 = Query("fiery");
    std::cout << q1 << std::endl;
    print(std::cout, q1.eval(tq));

    Query q2 = ~Query("alice");
    print(std::cout, q2.eval(tq));

    Query q3 = Query("daddy");
    print(std::cout, q3.eval(tq));
}