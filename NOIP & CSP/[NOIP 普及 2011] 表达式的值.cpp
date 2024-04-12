#include <vector>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using vect = vector<int>;

const int N = 1e5 + 10;
const int MOD = 1e4 + 7;

template <class Type>
class Stack {
  private:
    Type data[N];
    int t = 0;

  public:
    void push(Type x) {
        data[++t] = x;
    }
    void pop() {
        t--;
    }
    Type top() {
        return data[t];
    }
    Type extract() {
        return data[t--];
    }
    bool empty() {
        return !t;
    }
};

int n;
Stack<char> opt;
Stack<vect> num;
unordered_map<char, int> pr = {{'(', 0}, {'+', 1}, {'*', 2}};

void evaluate() {
    char c = opt.extract();
    vect b = num.extract();
    vect a = num.extract();
    if (c == '+')
        num.push({(a[0] * b[0]) % MOD,
            (a[0] * b[1] + a[1] * b[0] + a[1] * b[1]) % MOD});
    else if (c == '*')
        num.push({(a[0] * b[0] + a[0] * b[1] + a[1] * b[0]) % MOD,
            (a[1] * b[1]) % MOD});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    num.push({1, 1});

    while (n--) {
        char c;
        cin >> c;
        if (c == '(')
            opt.push(c);

        else if (c == '+' || c == '*') {
            while (!opt.empty() && pr[opt.top()] >= pr[c]) evaluate();
            num.push({1, 1});
            opt.push(c);
        } else if (c == ')') {
            while (!opt.empty() && opt.top() != '(') evaluate();
            opt.pop();
        }
    }

    while (!opt.empty()) evaluate();
    cout << num.top()[0] << endl;
    fflush(stdout);
    return 0;
}
