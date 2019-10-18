#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    string in_filename = "10.33_input.txt";
    string odd_file = "10.33_odd.txt", even_file = "10.33_even.txt";
    if (argc == 4)
    {
        in_filename = argv[1];
        odd_file = argv[2];
        even_file = argv[3];
    }

    ifstream ifs(in_filename);
    istream_iterator<int> int_it(ifs), eof;
    // vector<int> v(int_it, eof);

    ofstream odd_ofs(odd_file), even_ofs(even_file);
    ostream_iterator<int> odd_iter(odd_ofs, " "), even_iter(even_ofs, "\n");

    // copy_if(v.cbegin(), v.cend(), odd_iter, [](const int i) { return i&1; });
    // copy_if(v.cbegin(), v.cend(), even_iter, [](const int i) { return !(i&1); });

    for_each(int_it, eof, [&odd_iter, &even_iter](const int i) {
        (i & 0x1 ? odd_iter : even_iter) = i;
    });

    return 0;
}