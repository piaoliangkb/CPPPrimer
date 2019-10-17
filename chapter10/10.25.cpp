#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

void elimDups(vector<string> &v)
{
    sort(v.begin(), v.end());
    auto end_unique = unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
}

bool check_size(const string& s, string::size_type sz)
{
    return s.size() < sz;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words); // 按照字典序进行排序，删除重复元素

    stable_sort(words.begin(), words.end(), 
                [](const string &s1, const string &s2) {
                    return s1.size() < s2.size(); 
                }); // 按照长度排序，长度相同保持原元素相对顺序
    
    // 获取一个迭代器，返回指向第一个长度大于 sz 的元素
    // 注意这里使用 const_iterator 则 for_each 打印的时候尾元素迭代器也需要使用 const_iterator
    auto it = partition(words.begin(), words.end(), 
                        bind(check_size, _1, sz));

    // 计算满足 string.size() > sz 的所有元素数目
    auto count = words.end() - it;

    auto f = [count] (const string &word, const string &ending) { return (count>1)? word+ending : word;};
    cout << "there are " << count << f(" word", "s") 
        << " of length " << sz << " or longer" << endl;

    for_each(it, words.end(), [](const string &s) { cout << s << " "; });
    cout << endl;
}

int main()
{
    vector<string> v = { "hello", "this", "my", "computer", "would", "u", "want", 
                        "to", "buy", "my", "computer"};
    biggies(v, 4);

    return 0;
}