#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "StrBlob.h"

using namespace std;

class QueryResult;

class TextQuery {
public:
    TextQuery() = default;
    TextQuery(ifstream &infile);

    QueryResult query(const string &) const;

private:
    // 使用 StrBlob 替换 vector<string>
    StrBlob text;
    map<string, shared_ptr<set<int>>> word2line;
};

class QueryResult {
public:
    friend ostream &print(ostream &os, const QueryResult &qr);

    QueryResult(StrBlob text, shared_ptr<set<int>> lines,
                const string &s)
        : text(text), lines_in_text(lines), word(s) {}

private:
    const string word;
    StrBlob text;
    shared_ptr<set<int>> lines_in_text;
};

TextQuery::TextQuery(ifstream &infile) {

    string line;
    while (getline(infile, line)) {
        // 将每一行的内容存储到 text
        text.push_back(line);

        // 处理每个单词
        istringstream iss(line);
        string word;
        while (iss >> word) {

            auto line_no = text.size() - 1;

            word.erase(remove_if(word.begin(), word.end(),
                                 [](const char c) { return ispunct(c); }),
                       word.end());
            transform(word.begin(), word.end(), word.begin(),
                       [](char c) { return tolower(c); });

            auto res = word2line.find(word);
            if (res == word2line.end())
                word2line[word] = make_shared<set<int>>();

            word2line[word]->insert(line_no);
        }

    }
}

QueryResult TextQuery::query(const string &s) const {
    static shared_ptr<set<int>> voidset = make_shared<set<int>>();
    // 在 word2line 中查询是否有对应的单词
    auto res = word2line.find(s);
    if (res != word2line.end()) {
        // 将读入的text, 检索到的set，检索项s传给QueryResult
        return QueryResult(text, res->second, s);
    } else {
        // 若没有对应项，则传递给QueryResult的智能指针指向空set
        return QueryResult(text, voidset, s);
    }
}

void runQueries(ifstream &infile) {
    TextQuery tq(infile);

    while (true) {
        cout << "Please enter word you want to search: ";
        string s;
        cin >> s;
        print(cout, tq.query(s)) << endl;
    }
}

ostream &print(ostream &os, const QueryResult &qr) {
    auto occurtimes = qr.lines_in_text->size();
    cout << qr.word << " occurs " << occurtimes << " times" << endl;

    if (occurtimes != 0) {
        StrBlobPtr sbp(qr.text);
        for (auto &item : *(qr.lines_in_text)) {
            sbp.setCurr(item);
            cout << "\t(line " << item << ") " << sbp.deref() << endl;
        }
    }

    return os;
}

int main() {
    ifstream ifs("12.27_text.txt");
    runQueries(ifs);
}