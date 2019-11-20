#ifndef _BASKET_H_
#define _BASKET_H_

#include "Quote.h"
#include <memory>
#include <set>
#include <iostream>

class Basket {
public:
    void add_item(const Quote &sale) {
        std::cout << "[call func] Basket::add_item(const Quote&)" << std::endl;
        
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale) {
        std::cout << "[call func] Basket::add_item(Quote&&)" << std::endl;

        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    // 打印每本书的总价和 Basket 中所有书的总价
    double total_receipt(std::ostream&) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
                            return lhs->isbn() < rhs->isbn();
                        }
    
    // 传递 compare 参数的时候不可使用花括号，
    // 否则 items 会被当成函数
    // std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items(compare); error
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Basket::total_receipt(std::ostream &os) const {
    double sum = 0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "total sale : " << sum << std::endl;

    return sum;
}

#endif