#ifndef _ANDQUERY_H_
#define _ANDQUERY_H_

#include "BinaryQuery.h"

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);

private:
    AndQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "&") {
        std::cout << "AndQuery::AndQuery(const Query&, const Query&)"
                  << std::endl;
    }

    QueryResult eval(const TextQuery &) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);

    auto ret_lines = std::make_shared<set<int>>();

    // inserter 使用 insert 的迭代器，
    // 第二个参数为指向给定容器的迭代器，插入到给定迭代器之前。
    // set_intersection 将两个输入序列相同的内容写入到目标位置
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                          inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(left.getfile(), ret_lines, rep());
}

#endif