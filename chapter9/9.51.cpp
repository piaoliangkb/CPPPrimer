#include <iostream>
#include <string>
#include <array>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::isalpha;
using std::array;
using std::vector;

class Date {
public:
    unsigned year = 1970;
    unsigned month = 1;
    unsigned day = 1;
    Date() = default;
    Date(const string& str);
    void print();

private:
    array<string, 12> month_shortname = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", 
                                    "Aug", "Sep", "Oct", "Nov", "Dec"};
    unsigned mon_to_num(const string& mon);
};

unsigned Date::mon_to_num(const string& mon)
{
    // search string's first 3 letters from month_shortname
    for (array<string, 12>::size_type i=0; i<month_shortname.size(); ++i)
    {
        if ((mon == month_shortname[i]) || (mon.substr(0, 3) == month_shortname[i]))
        {
            return i+1;
        }
    }
    // if cannot find the month from array,
    // indicates that string incalid, 
    // return -1
    return -1;
}

Date::Date(const string& str)
{
    string delimiters(" /,");
    auto pos_month_day = str.find_first_of(delimiters);
    if (pos_month_day == string::npos) throw std::invalid_argument("invalid arguments, cant parse the date.");
    if (isalpha(str[0])) {
        month = mon_to_num(str.substr(0, pos_month_day));
        if (month == -1) throw std::invalid_argument("invalid arguments, cant parse the date.");
    }
    else {
        month = std::stoi(str.substr(0, pos_month_day));
    }

    auto pos_day_year = str.find_first_of(delimiters, pos_month_day+1);
    day = std::stoi(str.substr(pos_month_day+1, pos_day_year));

    year = std::stoi(str.substr(pos_day_year+1, str.size()));
}

void Date::print()
{
    cout << year << ", " << month << ", " << day << endl;
}

int main()
{
    {
        Date date("February 12, 1998");
        date.print();
    }

    {
        Date date;
        date.print();
    }

    {
        auto date = Date("January, 1, 1900");
        date.print();
    }

    {
        auto date = Date("1/1/1900");
        date.print();
    }

    {
        Date date("Jan 1/1977");
        date.print();
    }

    {
        auto date = Date("JJJAANN 12/1988");
        date.print();
    }
}