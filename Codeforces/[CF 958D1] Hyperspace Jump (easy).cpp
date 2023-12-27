#include <map>
#include <cctype>
#include <string>
#include <numeric>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 2e5 + 5;

int m;
PII fracs[N];
map<PII, int> vis;

void reduce(PII& frac) {
    int div = gcd(frac.first, frac.second);
    frac.first /= div, frac.second /= div;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m;

    for (int j = 1; j <= m; j++) {
        string expr;
        cin >> expr;

        int a = 0, b = 0, c = 0;
        for (int i = 0; i < (int)expr.length(); i++) {
            if (expr[i] == '(') {
                while (isdigit(expr[++i]))
                    a = a * 10 + expr[i] - '0';
                i--;
            } else if (expr[i] == '+') {
                while (isdigit(expr[++i]))
                    b = b * 10 + expr[i] - '0';
                i--;
            } else if (expr[i] == '/') {
                while (isdigit(expr[++i]))
                    c = c * 10 + expr[i] - '0';
                i--;
            }
        }

        fracs[j] = PII(a + b, c);
        reduce(fracs[j]);

        vis[fracs[j]]++;
    }

    for (int i = 1; i <= m; i++)
        cout << vis[fracs[i]] << ' ';

    cout << endl;
    fflush(stdout);
    return 0;
}
