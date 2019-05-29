#include <iostream>
#include <string>

using namespace std;

int main()
{
    int grade;
    string finalgrade;
    while (cin >> grade)
    {
        if (grade > 90) finalgrade = "high pass";
        else if (grade > 75) finalgrade = "pass";
        else if (grade > 60) finalgrade = "low pass";
        else finalgrade = "fail";
        cout << "finalgrade is " << finalgrade << endl;
    }
    return 0;
}