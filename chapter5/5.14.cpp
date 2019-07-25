#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, prev_string, max_string;
    int repeat_times, max_repeat_times = 0;
    while (cin >> s)
    {
        if (s == prev_string)
        {
            ++repeat_times;
        }
        else
        {
            repeat_times = 1;
            prev_string = s;
        }

        if (repeat_times > max_repeat_times)
        {
            max_string = s;
            max_repeat_times = repeat_times;
        }
    }
    if (max_repeat_times == 1)
    {
        cout << "no words repeated" << endl;
    }
    else
    {
        cout << max_string << " repeats " << max_repeat_times << " times." << endl;
    }

    return 0;
}
