#ifndef HEADER_12_19_H
#define HEADER_12_19_H

#include <memory>
#include <vector>
#include <string>

class ConstStrBlobPtr;
class StrBlob;

// 一个管理 string 的类
class StrBlob {
public:
  friend class ConstStrBlobPtr;

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

  ConstStrBlobPtr begin() const;  // add const
  ConstStrBlobPtr end() const;    // add const

private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string &msg) const;
};

//------------------------------------------------------------------------------/
//---------------------------split StrBlob and
// ConstStrBlobPtr-----------------------/
//------------------------------------------------------------------------------/

class ConstStrBlobPtr {
public:
  using size_type = std::vector<std::string>::size_type;
  bool operator!=(const ConstStrBlobPtr& p) {
      return p.curr != curr;
  }

  // curr 显式初始化为 0
  // wptr 隐式初始化为一个空 weak_ptr
  ConstStrBlobPtr() : curr(0) {}
  ConstStrBlobPtr(const StrBlob &a, size_type sz = 0) : wptr(a.data), curr(sz) {} // add const

  std::string &deref() const;

  // 前缀递增
  ConstStrBlobPtr &incr();

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

ConstStrBlobPtr StrBlob::begin() const { return ConstStrBlobPtr(*this); } // add const

ConstStrBlobPtr StrBlob::end() const { return ConstStrBlobPtr(*this, data->size()); }
// add const

//------------------------------------------------------------------------------------/
//--------------------implementation of
// ConstStrBlobPtr------------------------------------/
//------------------------------------------------------------------------------------/

std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(size_type i, const std::string &msg) const {
  auto res = wptr.lock();
  if (!res)
    throw std::runtime_error("unbound ConstStrBlobPtr");
  if (i >= res->size())
    throw std::out_of_range(msg);
  return res;
}

std::string &ConstStrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

// 返回递增后对象的引用
ConstStrBlobPtr &ConstStrBlobPtr::incr() {
  check(curr, "increment past end of ConstStrBlobPtr");
  ++curr;
  return *this;
}

#endif