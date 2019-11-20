#ifndef _QUERYRESULT_H_
#define _QUERYRESULT_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>

using std::ostream;
using std::shared_ptr;
using std::string;
using std::vector;
using std::set;
using std::cout;
using std::endl;

class QueryResult {
public:
    friend ostream &print(ostream &os, const QueryResult &qr);

    QueryResult(shared_ptr<vector<string>> text, shared_ptr<set<int>> lines,
                const string &s)
        : text(text), lines_in_text(lines), word(s) {}

    set<int>::iterator begin() const { return lines_in_text->begin(); }
    set<int>::iterator end() const { return lines_in_text->end(); }
    shared_ptr<vector<string>> getfile() const { return text; }

private:
    const string word;
    shared_ptr<vector<string>> text;
    shared_ptr<set<int>> lines_in_text;
};

ostream &print(ostream &os, const QueryResult &qr) {
    auto occurtimes = qr.lines_in_text->size();

    cout << qr.word << " occurs " << occurtimes << " times" << endl;

    for (auto beg = qr.begin(); beg != qr.end(); ++beg) {
        cout << "\t(line " << *beg << ") " << (*qr.getfile())[*beg] << endl;
    }
    return os;
}

#endif