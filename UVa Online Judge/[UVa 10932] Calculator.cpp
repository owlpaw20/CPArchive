#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;
using flt = double;

template <class Type>
struct Stack {
    vector<Type> data;
    Stack() {}
    Stack(int n) { data.reserve(n); }
    void push(const Type expr) { data.push_back(expr); }
    void pop() { data.pop_back(); }
    bool empty() { return data.empty(); }
    void clear() {
        while (!empty()) pop();
    }
    const Type top() { return data.back(); }
    const Type extract() {
        Type t = data.back();
        data.pop_back();
        return t;
    }
};

string s;
flt map[35];
Stack<flt> num;
Stack<char> opt;
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void evaluate() {
    if (opt.empty()) return;
    flt t1 = num.extract();
    flt t2 = num.extract();
    char op = opt.extract();
    if (op == '+') num.push(t1 + t2);
    if (op == '-') num.push(t2 - t1);
    if (op == '*') num.push(t1 * t2);
    if (op == '/') num.push(t2 / t1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(2);

    while (cin >> s) {
        num.clear();
        opt.clear();

        bool num_queued = false;
        bool assign = false;
        flt tmp = 0;
        string expr;

        if (s.size() != 1 && s[1] == '=') {
            assign = true;
            for (int i = 2; i < (int)s.size(); i++)
                expr += s[i];
        } else
            expr = s;

        for (char ch : expr) {
            if (isalpha(ch))
                num.push(map[ch - 'a' + 1]);
            else if (isdigit(ch))
                num_queued = true,
                tmp = tmp * 10 + (ch - '0');
            else {
                if (num_queued)
                    num_queued = false,
                    num.push(tmp),
                    tmp = 0;
                if (ch == '(')
                    opt.push(ch);
                else if (ch == ')') {
                    while (opt.top() != '(')
                        evaluate();
                    opt.pop();
                } else if (pr[ch] == 1) {
                    while (!opt.empty() && opt.top() != '(')
                        evaluate();
                    opt.push(ch);
                } else if (pr[ch] == 2) {
                    while (!opt.empty() && pr[opt.top()] == 2)
                        evaluate();
                    opt.push(ch);
                }
            }
        }

        if (num_queued)
            num_queued = false,
            num.push(tmp),
            tmp = 0;

        while (!opt.empty())
            evaluate();

        if (assign)
            map[s[0] - 'a' + 1] = num.top(), assign = false;
        else
            cout << fixed << num.top() << endl;
    }
    return 0;
}
