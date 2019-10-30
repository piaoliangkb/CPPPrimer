#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
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
    shared_ptr<map<string, shared_ptr<set<int>>>> word2line;
};

class QueryResult {
public:
    friend ostream &print(ostream &os, const QueryResult &qr);

    QueryResult(shared_ptr<vector<string>> text, shared_ptr<set<int>> lines,
                const string &s)
        : text(text), lines_in_text(lines), word(s) {}

private:
    const string word;
    shared_ptr<vector<string>> text;
    shared_ptr<set<int>> lines_in_text;
};

TextQuery::TextQuery(ifstream &infile) {
    text = make_shared<vector<string>>();
    word2line = make_shared<map<string, shared_ptr<set<int>>>>();

    string line;
    int line_no = 0;
    while (getline(infile, line)) {
        // 将每一行的内容存储到 text
        text->push_back(line);

        // 处理每个单词
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // 对读入的 word 处理符号,使用 erase, remove_if

            word.erase(remove_if(word.begin(), word.end(),
                                 [](const char c) { return ispunct(c); }),
                       word.end());
            transform(word.begin(), word.end(), word.begin(),
                       [](char c) { return tolower(c); });

            // 在 wowd2line map 中进行查找是否有对应的 word-set 映射
            auto res = word2line->find(word);
            // 若找到，则将对应的行号插入到 set 中
            // 若没找到，则新建一个 set 然后插入
            if (res == word2line->end())
                (*word2line)[word] = make_shared<set<int>>();
            // 插入
            (*word2line)[word]->insert(line_no);
        }

        // 进入到下一行，行号递增
        ++line_no;
    }
}

QueryResult TextQuery::query(const string &s) const {
    static shared_ptr<set<int>> voidset = make_shared<set<int>>();
    // 在 word2line 中查询是否有对应的单词
    auto res = word2line->find(s);
    if (res != word2line->end()) {
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
    for (auto &item : *(qr.lines_in_text)) {
        cout << "\t(line " << item << ") " << (*qr.text)[item] << endl;
    }
    return os;
}

int main() {
    ifstream ifs("12.27_text.txt");
    runQueries(ifs);
}