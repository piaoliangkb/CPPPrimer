#ifndef _ORQUERY_H_
#define _ORQUERY_H_

#include "BinaryQuery.h"

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

private:
    
    OrQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "|") {
            // std::cout << "OrQuery::OrQuery(const Query&, const Query&)" << std::endl;
        }
    
    QueryResult eval(const TextQuery&) const override;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const {
    // Query.eval 调用 Query_base 中定义的虚函数 eval
    // 返回每个运算对象的 QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    
    // 左侧运算对象的行号拷贝到一个新的 set<int> 内
    auto ret_lines = std::make_shared<set<int>>(left.begin(), left.end());

    // 右侧运算对象的行号插入
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(left.getfile(), ret_lines, rep());
}

#endif