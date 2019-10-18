#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    string filename = "10.29_text.txt";
    if (argc > 1)
    {
        filename = argv[1];
    }

    ifstream ifs(filename);
    istream_iterator<string> str_it(ifs), eof;
    vector<string> v(str_it, eof);
    
    ostream_iterator<string> os(cout , " ");
    copy(v.cbegin(), v.cend(), os);

    return 0;
}