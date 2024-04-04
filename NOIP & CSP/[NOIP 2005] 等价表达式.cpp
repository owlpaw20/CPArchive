#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;
using lng = unsigned long long; // 自然溢出
using POLY = unordered_map<lng, lng>;

namespace PolynomialCalculation {
    POLY operator+(POLY x, const POLY y) {
        for (auto [exp, coeff] : y)
            x[exp] += coeff;
        return x;
    }

    POLY operator-(POLY x, const POLY y) {
        for (auto [exp, coeff] : y)
            x[exp] -= coeff;
        return x;
    }

    POLY operator*(const POLY x, const POLY y) {
        POLY ret;
        for (auto [expX, coeffX] : x)
            for (auto [expY, coeffY] : y)
                ret[expX + expY] += coeffX * coeffY;
        return ret;
    }

    bool operator==(POLY x, POLY y) {
        for (auto [exp, coeff] : x)
            if (y[exp] != coeff)
                return false;
        for (auto [exp, coeff] : y)
            if (x[exp] != coeff)
                return false;
        return true;
    }
} // namespace PolynomialCalculation
using namespace PolynomialCalculation;

template <class Type>
struct Stack {
    vector<Type> data;
    void push(Type x) {
        data.push_back(x);
    }
    void pop() {
        data.pop_back();
    }
    Type top() {
        return data.back();
    }
    bool empty() {
        return data.empty();
    }
    Type extract() {
        Type t = data.back();
        data.pop_back();
        return t;
    }
};

int n;
string f;
Stack<char> opt;
Stack<POLY> num;
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}};

void cleanse_string(string &s) {
    string ret;
    for (char ch : s)
        if (!isblank(ch) && ch != '\r')
            ret += ch;
    s = ret;
}

void evaluate() {
    if (opt.empty()) return;

    POLY x = num.extract();
    POLY y = num.extract();
    char o = opt.extract();

    POLY res;
    if (o == '+') res = y + x;
    if (o == '-') res = y - x;
    if (o == '*') res = y * x;

    num.push(res);
}

POLY to_polynomial(string s) {
    while (!num.empty()) num.pop();
    while (!opt.empty()) opt.pop();

    int len = s.size();
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        if (isdigit(ch)) {
            int x = 0;
            while (i < len && isdigit(s[i]))
                x = x * 10 + s[i++] - '0';
            i -= 1;
            POLY tmp = {{0, x}};
            num.push(tmp);
        } else if (ch == '^') {
            int x = 0;
            i += 1;
            while (i < len && isdigit(s[i]))
                x = x * 10 + s[i++] - '0';
            i -= 1;
            POLY base = num.extract(), res = {{0, 1}};
            while (x--) res = base * res;
            num.push(res);
        } else if (ch == '(')
            opt.push(ch);

        else if (ch == ')') {
            for (char o : opt.data)
                if (o == '(') { // 处理右括号不匹配的情况
                    while (!opt.empty() && opt.top() != '(')
                        evaluate();
                    opt.pop();
                    break;
                }
        } else if (ch == 'a') {
            POLY tmp = {{1, 1}};
            num.push(tmp);
        } else {
            while (!opt.empty() && pr[opt.top()] >= pr[s[i]])
                evaluate();
            opt.push(s[i]);
        }
    }

    while (!opt.empty()) {
        while (opt.top() == '(') opt.pop(); // 处理左括号不匹配的情况
        if (!opt.empty()) evaluate();
    }

    return num.extract();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, f);
    cleanse_string(f);
    POLY F = to_polynomial(f);

    cin >> n;

    string s, ans;
    getline(cin, s);

    for (int i = 0; i < n; i++) {
        getline(cin, s);
        cleanse_string(s);
        POLY S = to_polynomial(s);
        if (F == S)
            ans += (i + 'A');
    }

    cout << ans << endl;
    return 0;
}
