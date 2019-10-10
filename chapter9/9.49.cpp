#include <iostream>
#include <string>
#include <fstream>

using namespace std;

inline bool has_upanddown(const string &s, const string &search)
{
    if (s.find_first_of(search) != string::npos) return true;
    else return false;
}

int main(int argc, char** argv)
{
    char* filename;
    string up_and_down("bdfghijklpqty");
    string longest_word = "";
    if (argc <= 1) {
        cout << "filename is empty" << endl << "exit" << endl;;
        return -1;
    }
    else {
        filename = argv[1];
    }

    fstream fs(filename);
    if (!fs.is_open()) {
        cout << "failed to open file [" << filename << "]" << endl;
        return -1;
    }
    else {
        string content;
        while (fs >> content) {
            if (!has_upanddown(content, up_and_down)) {
                if (content.size() > longest_word.size()) longest_word = content;
            }
        }
        cout << "the longest word without up_and_down letter is [" << longest_word << "]\n";
    }
}