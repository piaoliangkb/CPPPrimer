#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class QueryResult;

class TextQuery {
public:
    TextQuery() = default;
    TextQuery(ifstream &infile);

    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> text;
    map<string, shared_ptr<set<int>>> word2line;
};

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

TextQuery::TextQuery(ifstream &infile) {
    text = make_shared<vector<string>>();

    string line;
    while (getline(infile, line)) {

        text->push_back(line);
        int line_no = text->size() - 1;

        istringstream iss(line);
        string word;

        while (iss >> word) {

            word.erase(remove_if(word.begin(), word.end(),
                                 [](const char c) { return ispunct(c); }),
                       word.end());
            transform(word.begin(), word.end(), word.begin(),
                       [](char c) { return tolower(c); });

            auto &lines = word2line[word]; 

            // lines 是一个 shared_ptr
            // lines 是一个智能指针的引用，不会直接拷贝这个指针
            if (!lines) {
                lines.reset(new set<int>);
            }
            lines->insert(line_no);
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

    for (auto beg = qr.begin(); beg != qr.end(); ++beg) {
        cout << "\t(line " << *beg << ") " << (*qr.getfile())[*beg] << endl;
    }
    return os;
}

int main() {
    ifstream ifs("12.27_text.txt");
    runQueries(ifs);
}