#include <cmath>
#include <cstdint>
#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_N = 1e6 + 5;
const int MAX_M = 1e6 + 5;
const int MAX_V = 1e6 + 5;

int a[MAX_N], bel[MAX_N], cnt[MAX_V];

struct QUERY {
    int l, r, id;
    bool operator<(const QUERY &t) const {
        if (bel[l] != bel[t.l]) return bel[l] < bel[t.l];
        if (bel[l] & 1) return r > t.r;
        return r < t.r;
    }
} q[MAX_M];

int ans[MAX_M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, block;
    std::cin >> N, block = sqrt(N);
    for (int i = 1; i <= N; ++i)
        std::cin >> a[i], bel[i] = (i - 1) / block + 1;

    int M;
    std::cin >> M;
    for (int i = 0; i < M; ++i)
        std::cin >> q[i].l >> q[i].r, q[i].id = i;

    std::sort(q, q + M);

    int sum = 0;
    auto expand = [&](const int x) -> void { sum = (cnt[a[x]]++ == 0) ? sum + 1 : sum; };
    auto shrink = [&](const int x) -> void { sum = (--cnt[a[x]] == 0) ? sum - 1 : sum; };

    for (int i = 0, l = 1, r = 0; i < M; ++i) {
        while (l > q[i].l) expand(--l);
        while (r < q[i].r) expand(++r);
        while (l < q[i].l) shrink(l++);
        while (r > q[i].r) shrink(r--);
        ans[q[i].id] = sum;
    }

    for (int i = 0; i < M; ++i) std::cout << ans[i] << endl;
    return fflush(stdout), 0;
}
