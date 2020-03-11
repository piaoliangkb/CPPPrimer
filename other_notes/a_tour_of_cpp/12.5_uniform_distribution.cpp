#include <random>
#include <iostream>
#include <vector>

using namespace std;

class Randint {
private:
    std::default_random_engine re;
    std::uniform_int_distribution<> dist;
public:
    Randint(int low, int high) : dist{low, high} {}
    int operator()() { return dist(re); }
};

int main()
{
    constexpr int max = 20;
    Randint rnd{0, max};

    vector<int> vec(max+1);

    for (int i=0; i!=2000; ++i) {
        ++vec[rnd()];
    }

    for (int i=0; i!=vec.size(); ++i) {
        cout << i << ": ";
        for(int j=0; j!=vec[i]; ++j) {
            cout << "*";
        }
        cout << endl;
    }

}