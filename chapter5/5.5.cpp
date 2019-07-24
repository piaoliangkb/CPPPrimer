#include <iostream>
#include <string>

using namespace std;

int main()
{
    double score;
    string lettergrade;
    while (cin >> score)
    {
        if ((score > 100) || (score < 0)) 
        {
            cout << "invalid score" << endl;
            continue;
        }
        else if (score == 100) lettergrade = "A++";
        else if (score>=90) lettergrade = "A";
        else if (score>=80) lettergrade = "B";
        else if (score>=70) lettergrade = "C";
        else if (score>=60) lettergrade = "D";
        else lettergrade = "F";

        cout << "this student's score grade is " << score << ", letter grade is " << lettergrade << ". " << endl;
    }
    return 0;
}