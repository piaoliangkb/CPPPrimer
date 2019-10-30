#ifndef HEADER_12_19_H
#define HEADER_12_19_H

#include <memory>
#include <string>
#include <vector>

class StrBlobPtr;
class StrBlob;

// 一个管理 string 的类
class StrBlob {
public:
    friend class StrBlobPtr;

    using size_type = std::vector<std::string>::size_type;

    // 默认构造函数
    StrBlob() : data(std::make_shared<std::vector<std::string>>()){};
    // 接受一个初始值列表的构造函数
    StrBlob(std::initializer_list<std::string> il)
        : data(std::make_shared<std::vector<std::string>>(il)){};

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string &front() const;
    std::string &back() const;

    StrBlobPtr begin();
    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

//------------------------------------------------------------------------------/
//---------------------------split StrBlob and
// StrBlobPtr-----------------------/
//------------------------------------------------------------------------------/

class StrBlobPtr {
public:
    using size_type = std::vector<std::string>::size_type;
    bool operator!=(const StrBlobPtr &p) { return p.curr != curr; }

    // curr 显式初始化为 0
    // wptr 隐式初始化为一个空 weak_ptr
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(const StrBlob &a, size_type sz = 0) : wptr(a.data), curr(sz) {}

    // 解引用
    std::string &deref() const;

    // 前缀递增
    StrBlobPtr &incr();

    // 设置当前位置
    void setCurr(size_type i) { curr = i; }

private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<std::string>> check(size_type,
                                                    const std::string &) const;
};

//------------------------------------------------------------------------------------/
//--------------------implementation of
// StrBlob---------------------------------------/
//------------------------------------------------------------------------------------/

// 私有工具函数：检查元素的值是否符合范围
void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string &StrBlob::front() const {
    check(0, "get front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() const {
    check(0, "get back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

//------------------------------------------------------------------------------------/
//--------------------implementation of
// StrBlobPtr------------------------------------/
//------------------------------------------------------------------------------------/

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(size_type i, const std::string &msg) const {
    auto res = wptr.lock();
    if (!res)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= res->size())
        throw std::out_of_range(msg);
    return res;
}

std::string &StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

// 返回递增后对象的引用
StrBlobPtr &StrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

#endif