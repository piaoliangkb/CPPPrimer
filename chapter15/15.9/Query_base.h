#ifndef _QUERY_BASE_H_
#define _QUERY_BASE_H_

#include "QueryResult.h"
#include "TextQuery.h"

#include <string>

class Query_base {
    friend class Query;

protected:

    // in my program, this is type:int in TextQuery.h
    // such like : map<string, shared_ptr<set<int>>> word2line;
    using line_no = TextQuery::line_num;

    virtual ~Query_base() = default;

private:

    // eval 返回与当前 Query 匹配的 QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;

    // rep 表示查询的一个 string
    virtual std::string rep() const = 0;
};

#endif