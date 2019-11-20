#ifndef _NOTQUERY_H_
#define _NOTQUERY_H_

#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base {

    friend Query operator~(const Query&); // 将运算符设置为友元以创建 NotQuery 对象

private:

    NotQuery(const Query &q) : query(q) {}

    QueryResult eval(const TextQuery &) const override;

    std::string rep() const override { return "~(" + query.rep() + ")"; }

    Query query;
};

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const {
    auto ret = query.eval(text);

    auto ret_lines = std::make_shared<set<int>>();

    auto beg = ret.begin(), end = ret.end(); // 遍历 set 的行号按照升序排列
    auto sz = ret.getfile()->size();

    // 例如 ret{2, 3}
    // 总行数  {0, 1, 2, 3, 4, 5}
    for (size_t n = 0; n < sz; ++n) {
        // 如果 ret 已经结束，则上边的 if 条件永远为真，将所有剩余行添加
        // 若 ret 未结束，看当前行号和 *beg 是否相等
        // 如果不等，就添加进结果集合
        // 若相等，则递增 beg ，检查集合中的下一个元素和下一个行号
        if (beg == end || n != *beg)
            ret_lines->insert(n);
        else
            ++beg;
    }

    return QueryResult(ret.getfile(), ret_lines, rep());
}

#endif