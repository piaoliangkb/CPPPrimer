#include <iostream>
#include <memory>
#include <string>
#include <utility>

using std::cout;
using std::endl;

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(std::initializer_list<std::string>);

    StrVec(const StrVec &);

    StrVec &operator=(const StrVec &);

    ~StrVec();

    void push_back(const std::string &);

    size_t size() const { return first_free - elements; }

    size_t capacity() const { return cap - elements; }

    std::string *begin() const { return elements; }

    std::string *end() const { return first_free; }

    void reserve(size_t);

    void resize(size_t);

    void printElems();

private:
    std::allocator<std::string> alloc;

    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }

    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                         const std::string *);

    void alloc_n_move(size_t);

    void free();

    void reallocate();

    std::string *elements;   // 指向数组首元素的指针
    std::string *first_free; // 指向数组第一个空闲元素
    std::string *cap;        // 指向数组尾后位置的指针
};

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

/*
返回值：重新分配空间的起始位置和尾后位置
参数：一个给定范围内的元素
*/
std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *begin, const std::string *end) {
    // beg 指向新分配的内存首位置
    auto beg = alloc.allocate(end - begin);
    // std::uninitialized_copy 返回指向最后一个构造元素之后的位置
    return {beg, std::uninitialized_copy(begin, end, beg)};
}

// 带参数版本的 reallocate，allocate and move
void StrVec::alloc_n_move(size_t n) {
    auto newcapacity = n;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::free() {
    // 若首元素不为空才进入循环
    // 先 destroy 存在的元素
    // 再 deallocate 回收所有空间
    if (elements) {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

// 拷贝赋值运算符在释放已有元素之前调用 alloc_n_copy 来处理自赋值情况
StrVec &StrVec::operator=(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate() {
    auto newcapacity = size() ? 2 * size() : 1; // 新空间大小
    auto newdata = alloc.allocate(newcapacity); // newdata 指向分配的第一个位置
    auto dest = newdata; // 开始移动构造的第一个位置为新分配的位置
    auto elem = elements; // elem 指向第一个原始元素
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(
            dest++, std::move(*elem++)); // 将原来所有的元素移动构造到目标地址
    free(); // 原 elements, cao 不变，释放该段地址的内容
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve(size_t n) {
    if (capacity() < n) {
        alloc_n_move(n);
    }
}

void StrVec::resize(size_t n) {
    if (n < capacity()) {
        while (first_free != elements + n)
            alloc.destroy(--first_free);
    } else if (n > capacity()) {
        alloc_n_move(n);
        for (auto i = size(); i < n; ++i)
            alloc.construct(first_free++, std::string());
    }
}

void StrVec::printElems() {
    for (auto beg = begin(); beg != end(); ++beg)
    {
        cout << *beg << " ";
    }
    cout << endl;
}

// 接受 initializer_list 的构造函数
StrVec::StrVec(std::initializer_list<std::string> il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

int main() {
    StrVec sv{"cppprimer", "fluentpython", "redis", "algorithms"};

    cout << sv.size() << endl;
    cout << sv.capacity() << endl;

    sv.printElems();

    sv.push_back("computer network");

    cout << sv.size() << endl;
    cout << sv.capacity() << endl;

    sv.printElems();

    return 0;
}