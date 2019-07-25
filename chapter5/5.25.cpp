#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    int a, b;

    while (cin >> a >> b) {

        try {
            if (b == 0) throw runtime_error("divisor cannot be 0");
            cout << static_cast<double>(a)/b << endl;
        } catch (runtime_error err) {
            cout << err.what() << endl;
            cout << "try this again ? y or n :";
            char c;
            cin >> c;
            if (c == 'n') break; 
        }
    }

    return 0;
}