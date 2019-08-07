#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "";
    s += argv[1];
    s += argv[2];
    cout << s << endl;
    return 0;
}
