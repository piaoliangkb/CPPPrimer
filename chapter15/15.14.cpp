#include <iostream>
#include <string>

using namespace std;

class base {
public:
    string name() { return basename; }

    virtual void print(ostream &os) { os << basename; }

private:
    string basename = "base";
};

class derived : public base {
public:
    void print(ostream &os) override {
        base::print(os);
        os << " " << i;
    }
private:
    int i = 11;
};

int main()
{
    base bobj;
    derived dobj;
    base *bp1 = &bobj;
    base *bp2 = &dobj;
    base &br1 = bobj;
    base &br2 = dobj;

    cout << 1;
    bobj.print(cout);

    cout << 2;
    dobj.print(cout);

    cout << 3;
    bp1->print(cout);

    cout << 4;
    bp2->print(cout);

    cout << 5;
    br1.print(cout);

    cout << 6;
    br2.print(cout);
}