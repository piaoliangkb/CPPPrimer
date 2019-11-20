#ifndef _ANDQUERY_H_
#define _ANDQUERY_H_

#include "BinaryQuery.h"

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

private:
    
    AndQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "&") {
            std::cout << "AndQuery::AndQuery(const Query&, const Query&)" << std::endl;
        }
    
    QueryResult eval(const TextQuery&) const override {
        // placeholder
    }

};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

#endif