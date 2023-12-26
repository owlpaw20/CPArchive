#include <vector>
#include <iostream>
#include <algorithm>  // __gcd()

using namespace std;
using lng = __int128_t;
using PII = pair<lng, lng>;

const int N = 1e5 + 10;

int n, m;
PII w[N];
vector<int> g[N];

PII calc(PII x, PII y) {
    lng down = x.second * y.second / __gcd(x.second, y.second);
    lng up = x.first * down / x.second + y.first * down / y.second;
    return {up, down};
}

void run(int u, PII water) {
    if (g[u].empty()) {
        w[u] = calc(w[u], water);
        return;
    }
    lng t = g[u].size();
    for (int i : g[u]) run(i, {1, water.second * t});
}

void print128(lng x) {
    if (x >= 10) print128(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        for (int j = 0; j < d; j++) {
            int t;
            cin >> t;
            g[i].push_back(t);
        }
        w[i] = {0, 1};
    }

    for (int i = 1; i <= m; i++)
        run(i, {1, 1});

    for (int i = 1; i <= n; i++) {
        if (g[i].empty()) {
            int t = __gcd(w[i].first, w[i].second);
            while (t != 1) {
                w[i].first /= t;
                w[i].second /= t;
                t = __gcd(w[i].first, w[i].second);
            }
            print128(w[i].first);
            putchar(' ');
            print128(w[i].second);
            putchar('\n');
        }
    }
    return 0;
}
