#include "Disc_quote.h"

int main()
{
    Disc_quote dq;
}

/*
15.17.cpp:5:16: error: variable type 'Disc_quote' is an abstract class
    Disc_quote dq;
               ^
./Disc_quote.h:13:12: note: unimplemented pure virtual method 'net_price' in
'Disc_quote' double net_price(std::size_t n) const = 0;
           ^
1 error generated.
*/
