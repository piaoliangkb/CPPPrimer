#ifndef _WORD_QUERY_H
#define _WORD_QUERY_H

#include "Query_base.h"
#include <string>

class WordQuery : public Query_base {

    friend class Query;

private:
    WordQuery(const std::string &s) : query_word(s) {
        // std::cout << "WordQuery::WordQuery(const std::string&)" << std::endl;
    }

    QueryResult eval(const TextQuery &t) const override {
        return t.query(query_word);
    }

    std::string rep() const override {
        // std::cout << "WordQuery::rep()" << std::endl;

        return query_word;
    }

    std::string query_word;
};

#endif