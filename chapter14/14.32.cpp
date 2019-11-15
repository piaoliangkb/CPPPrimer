#include "14.27_28_30_StrBlob_StrBlobPtr.h"
#include <iostream>

class StrBlobPtr_pointer {
public:
    StrBlobPtr_pointer() : pointer(nullptr) {}

    StrBlobPtr_pointer(StrBlobPtr *p) : pointer(p) {}

    StrBlobPtr &operator*() const {
        return *(this->pointer);
    }

    StrBlobPtr *operator->() const {
        return &this->operator*();
    }

private:
    StrBlobPtr *pointer;
};

int main()
{
    StrBlob sb{"hello", "didi"};
    StrBlobPtr iter = sb.begin();

    StrBlobPtr_pointer p(&iter);
    std::cout << p->deref() << std::endl;
}