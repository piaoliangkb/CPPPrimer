#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s;
    vector<string> v;
    while (getline(cin, s))
        v.push_back(s);

    for (auto it = v.begin(); it != v.end() && !it->empty(); ++it)
    {
        for (auto &c : *it) c = toupper(c);
        cout << *it << endl;
    }

    return 0;
}

/* input and output:
nihao, woshi xiaozhupeiqi, nihao ,woshi xiaozhupeiqide gege,qiaozhi.
shifou zheci wojiangzhende likaini, shifou yanleiyiganbuzaiku,
shifou yingyanle wocengshuode najuhua, qingdaorenhourengudu

duoshao cide jimo zhengcha zai xintou, zhiwei wanhui wojiangyuanqude jiaobu
duoshao ,ciwo duzhuxiongkou de leishui ,zhishi weile gaosuwo ziji wo buzaihu
^Z
NIHAO, WOSHI XIAOZHUPEIQI, NIHAO ,WOSHI XIAOZHUPEIQIDE GEGE,QIAOZHI.
SHIFOU ZHECI WOJIANGZHENDE LIKAINI, SHIFOU YANLEIYIGANBUZAIKU,
SHIFOU YINGYANLE WOCENGSHUODE NAJUHUA, QINGDAORENHOURENGUDU

*/