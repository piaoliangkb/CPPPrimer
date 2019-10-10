#include <iostream>
#include <stack>
#include <string>

using namespace std;

char cal(const string& expr)
{
    return '1';
}

int main()
{
    string expr("(1+2)*(3/(3-1))");
    int seen = 0;
    stack<char> stk;
    for (auto c : expr)
    {
        stk.push(c);
        if (c == '(') ++seen;
        if (seen && c == ')') 
        {
            string temp;
            while (stk.top() != '(')
            {
                temp += stk.top();
                stk.pop();
            }
            stk.pop(); // 弹出 (
            stk.push(cal(temp));
            --seen;
        }
    }
    while (!stk.empty())
    {
        cout << stk.top();
        stk.pop();
    }

}