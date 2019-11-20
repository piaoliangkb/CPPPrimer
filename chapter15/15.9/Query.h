#ifndef _QUERY_H_
#define _QUERY_H_

#include "QueryResult.h"
#include "Query_base.h"
#include "TextQuery.h"
#include "WordQuery.h"

#include <memory>
#include <string>

class Query {

    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

public:
    // 创建一个新的 WordQuery 的构造函数
    Query(const std::string &s) : q(new WordQuery(s)) {
        // std::cout << "Query::Query(const std::string&)" << std::endl;
    }

    QueryResult eval(const TextQuery &t) const { return q->eval(t); }

    std::string rep() const {
        // std::cout << "Query::rep()" << std::endl;

        return q->rep();
    }

private:
    // 构造函数
    Query(std::shared_ptr<Query_base> query) : q(query) {
        // std::cout << "Query::Query(std::shared_ptr<Query_base>)" << std::endl;
    }

    std::shared_ptr<Query_base> q;
};

// Query 类的输出运算符
std::ostream &operator<<(std::ostream &os, const Query &query) {
    return os << query.rep();
}

#endif