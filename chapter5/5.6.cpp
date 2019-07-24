#include <iostream>
#include <string>

using namespace std;

int main()
{
    double score;
    string lettergrade;

    while (cin >> score)
    {
        lettergrade = (score > 100 ? "" : score == 100 ? "A++" : 
                        score >= 90 ? "A" : score >= 80 ? "B" : 
                        score >= 70 ? "C" : score >= 60 ? "D" : 
                        score > 0 ? "F" : "");
         cout << "this student's score grade is " << score << ", letter grade is " << lettergrade << ". " << endl;
    }
    return 0;
}