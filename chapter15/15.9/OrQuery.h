#ifndef _ORQUERY_H_
#define _ORQUERY_H_

#include "BinaryQuery.h"

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

private:
    
    OrQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "|") {
            std::cout << "OrQuery::OrQuery(const Query&, const Query&)" << std::endl;
        }
    
    QueryResult eval(const TextQuery&) const override {
        // placeholder
    }

};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif