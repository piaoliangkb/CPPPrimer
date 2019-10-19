#include <iostream>
#include <set>
#include <string>

class Sales_data {
public:
    Sales_data(const std::string s = ""): bookNo(s) {}
    std::string isbn() const { return bookNo; }

private:
    std::string bookNo = "isbn9999";
};

bool compareISBN(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() < rhs.isbn();
}

int main()
{
    using comparetype = bool(*) (const Sales_data&, const Sales_data&);

    std::multiset<Sales_data, comparetype> bookstore(compareISBN);

    typedef bool (*fn)(const Sales_data&, const Sales_data&);

    std::multiset<Sales_data, fn> bookstore1(compareISBN);
    
}