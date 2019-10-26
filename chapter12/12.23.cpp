#include <iostream>
#include <memory>
#include <string>
#include <cstring>

using namespace std;

size_t get_size(const char *arr)
{
    size_t size = 0;
    while (*arr != '\0')
    {
        ++size; ++arr;
    }
    return size;
}

int main()
{
    const char *a = "hello ", *b = "world";
    size_t lenb = get_size(b), lena = get_size(a);
    char *res = new char[lena + lenb + 1];
    for (size_t i = 0; i < lena; ++i)
    {
        *(res+i) = *a;
        ++a;
    }
    for (size_t i = lena; i < lena + lenb; ++i)
    {
        *(res+i) = *b;
        ++b;
    }
    *(res + lena + lenb) = '\0';
    cout << res << endl;

    delete[] res;

    string s1 = "hello ", s2 = "world";
    auto s3 = s1 + s2;
    cout << s3 << endl;

    return 0;
}

/*
int main() {
        const char *c1 = "Hello ";
        const char *c2 = "World";
        unsigned len = strlen(c1) + strlen(c2) + 1;
        char *r = new char[len]();
        strcat_s(r, len, c1);
        strcat_s(r, len, c2);
        std::cout << r << std::endl;

        std::string s1 = "Hello ";
        std::string s2 = "World";
        strcpy_s(r, len, (s1 + s2).c_str());
        std::cout << r << std::endl;

        delete[] r;

        return 0;
}
*/