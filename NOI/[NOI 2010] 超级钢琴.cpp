#include <bit>
#include <queue>
#include <cstdint>
#include <cstring>
#include <iostream>

#define endl '\n'
#define get_pos(x, y) ((p[x] >= p[y]) ? (x) : (y))

using i64 = int64_t;

const int MAX_N = 5e5 + 5;

int N, K, L, R;
int p[MAX_N];

struct SPARSETABLE {
    int data[MAX_N][20];

    void init() {
        for (int i = 1; i <= N; ++i) data[i][0] = i;
        for (int j = 1; j <= std::__lg(N); ++j)
            for (int i = 1; i + (1 << j) - 1 <= N; ++i)
                data[i][j] = get_pos(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int t = std::__lg(r - l + 1);
        return get_pos(data[l][t], data[r - (1 << t) + 1][t]);
    }
} ST;

struct CHORD {
    int lb, rb_l, rb_r, rb;

    bool operator<(const CHORD &t) const {
        return p[rb] - p[lb - 1] < p[t.rb] - p[t.lb - 1];
    }

    CHORD() {}
    CHORD(int _i, int _l, int _r) :
        lb(_i), rb_l(_l), rb_r(_r), rb(ST.query(_l, _r)) {}
};

std::priority_queue<CHORD> heap;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> K >> L >> R;
    for (int i = 1; i <= N; ++i)
        std::cin >> p[i], p[i] += p[i - 1];

    ST.init();

    for (int lb = 1; lb <= N; ++lb)
        if (lb + L - 1 <= N)
            heap.emplace(lb, lb + L - 1, std::min(lb + R - 1, N));

    i64 ans = 0;

    while (K--) {
        auto [lb, rb_l, rb_r, rb] = heap.top();
        heap.pop();

        ans += p[rb] - p[lb - 1];

        if (rb != rb_l) heap.emplace(lb, rb_l, rb - 1);
        if (rb != rb_r) heap.emplace(lb, rb + 1, rb_r);
    }

    std::cout << ans << endl;
    return fflush(stdout), 0;
}
