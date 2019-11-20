#ifndef _BINARYQUERY_H_
#define _BINARYQUERY_H_

#include "Query.h"
#include "Query_base.h"

class BinaryQuery : public Query_base {

protected:
    BinaryQuery(const Query &l, const Query &r, std::string s)
        : lhs(l), rhs(r), opSym(s) {
        std::cout << "BinaryQuery::BinaryQuery(const Query&, const Query&, "
                     "std::string)"
                  << std::endl;
    }

    // 该类没有定义 eval，而是从 Query_base 中直接继承该纯虚函数
    // 所以该类也是纯虚基类
    // 不能定义该类的对象

    std::string rep() const override {
        // auto ret = "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";

        std::cout << "BinaryQuery::rep() " << std::endl;

        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};

#endif