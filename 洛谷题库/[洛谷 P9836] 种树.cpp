#include <cmath>
#include <queue>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using HEAP = priority_queue<int, vector<int>, greater<int>>;
using HASH = unordered_map<int, HEAP>;

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

const int N = 1e4 + 10;
const int MOD = 998244353;

int n, w;
HASH pf;

void factorize_prime(int x) {
    int sqrtx = sqrt(x);
    for (int i = 2, exp = 0; i <= sqrtx; i++, exp = 0) {
        if (x % i != 0) continue;
        while (x % i == 0)
            x /= i, exp += 1;
        pf[i].push(exp);
    }
    if (x > 1) pf[x].push(1);
}

int main() {
    n = read(), w = read();
    for (int i = 1; i <= n; i++)
        factorize_prime(read());

    int sqrtw = sqrt(w);
    for (int i = 2; i <= sqrtw; i++)
        while (w % i == 0) {
            w /= i;
            if ((int)pf[i].size() < n)
                pf[i].push(1);
            else
                pf[i].push(pf[i].top() + 1), pf[i].pop();
        }

    if (w > 1) {
        if ((int)pf[w].size() < n)
            pf[w].push(1);
        else
            pf[w].push(pf[w].top() + 1), pf[w].pop();
    }

    int ans = 1;
    for (auto [num, heap] : pf)
        while (!heap.empty())
            ans = (long long)ans * (heap.top() + 1) % MOD,
            heap.pop();

    write(ans), putchar('\n');
    fflush(stdout);
    return 0;
}
