#include <memory>
#include <string>
#include <vector>
#include <iostream>

// 一个管理 string 的类
class StrBlob {
public:
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

private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string &msg) const;
};

// 私有工具函数：检查元素的值是否符合范围
void StrBlob::check(size_type i, const std::string& msg) const
{
    if (i >= data->size()) throw std::out_of_range(msg);
}

std::string& StrBlob::front() const
{
    check(0, "get front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back() const
{
    check(0, "get back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

int main()
{
    StrBlob b1;
    {
        const StrBlob b2({"a", "an", "the"});
        // const StrBlob b2{"a", "an", "the"};
        // const StrBlob b2 = {"hello", "world"}; // will not work on explicit
        b1 = b2;
        std::cout << b2.size() << std::endl;
        std::cout << b2.front() << std::endl;
        std::cout << b2.back() << std::endl;
    }
    std::cout << b1.size() << std::endl;
    std::cout << b1.front() << std::endl;
    std::cout << b1.back() << std::endl;

    return 0;
}