#include <iostream>
#include <string>

using namespace std;

int main()
{
    const string s = "keep out!";
    for (auto &c : s)
    c = 'X';

    cout << s << endl;

    return 0;
}

```
tempCodeRunnerFile.cpp:11:7: error: assignment of read-only reference 'c'
     c = 'X';
```