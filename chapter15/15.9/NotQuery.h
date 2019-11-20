#ifndef _NOTQUERY_H_
#define _NOTQUERY_H_

#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base {

    friend Query operator~(const Query&); // 将运算符设置为友元以创建 NotQuery 对象

private:

    NotQuery(const Query &q) : query(q) {}

    QueryResult eval(const TextQuery &) const override {
        // placeholder
    }

    std::string rep() const override { return "~(" + query.rep() + ")"; }

    Query query;
};

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

#endif