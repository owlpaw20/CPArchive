#pragma GCC optimize("O2,unroll-loops")

#include <chrono>
#include <limits>
#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_map>

#define endl '\n'

namespace FastIO {
    const int MAX_BUF = 1 << 20;
    char buf[MAX_BUF], *p1, *p2;

#define getchar() \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

    template <typename T>
    inline T read() {
        T x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }

    template <typename T>
    inline void write(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

using i64 = int64_t;
using c32 = const int32_t;
using c64 = const int64_t;
using cu32 = const uint32_t;
using PII = std::pair<int, int>;

const int MAX_N = 2e5 + 5;

struct MyHash {
    inline static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    inline size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int N, M, cost[MAX_N];
i64 f[MAX_N];  // f[i] 表示前 i 条路中修复若干条路可以获得的最大收益
std::unordered_map<int, std::vector<PII>, MyHash> val;

struct SegT {
    struct Node {
        i64 max_v;  // max_v = f[j] + val(j + 1, i) - cost(j + 1, i)
        i64 add_tag;

        Node() :
            max_v(0), add_tag(0) {}

        inline void pull(const Node x, const Node y) { max_v = std::max(x.max_v, y.max_v); }

        inline void push(Node &x, Node &y) {
            if (!add_tag) return;
            x.max_v += add_tag;
            y.max_v += add_tag;
            x.add_tag += add_tag;
            y.add_tag += add_tag;
            add_tag = 0;
        }

    } node[MAX_N << 2];

    inline void range_add(cu32 l, cu32 r, c64 v, cu32 u = 1, cu32 nl = 0, cu32 nr = N) {
        if (nl >= l && nr <= r) {
            node[u].max_v += v;
            node[u].add_tag += v;
            return;
        }

        node[u].push(node[u << 1], node[u << 1 | 1]);

        cu32 mid = (nl + nr) >> 1;

        if (l <= mid) range_add(l, r, v, u << 1, nl, mid);
        if (r > mid) range_add(l, r, v, u << 1 | 1, mid + 1, nr);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    inline void point_set(cu32 x, c64 v, cu32 u = 1, cu32 nl = 0, cu32 nr = N) {
        if (nl == nr) {
            node[u].max_v = v;
            node[u].add_tag = 0;
            return;
        }

        node[u].push(node[u << 1], node[u << 1 | 1]);

        cu32 mid = (nl + nr) >> 1;

        if (x <= mid)
            point_set(x, v, u << 1, nl, mid);
        else
            point_set(x, v, u << 1 | 1, mid + 1, nr);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    i64 query(cu32 l, cu32 r, cu32 u = 1, cu32 nl = 0, cu32 nr = N) {
        if (nl >= l && nr <= r) return node[u].max_v;

        node[u].push(node[u << 1], node[u << 1 | 1]);

        cu32 mid = (nl + nr) >> 1;
        i64 ret = std::numeric_limits<i64>::min();

        if (l <= mid) ret = std::max(ret, query(l, r, u << 1, nl, mid));
        if (r > mid) ret = std::max(ret, query(l, r, u << 1 | 1, mid + 1, nr));

        return ret;
    }

} SEGT;

int main() {
    N = read<int>(), M = read<int>();
    for (int i = 1; i <= N; ++i) cost[i] = read<int>();
    for (int i = 1, l, r, v; i <= M; ++i)
        l = read<int>(), r = read<int>(), v = read<int>(), val[r].emplace_back(l, v);

    for (int i = 1; i <= N; ++i) {                               // 每次枚举到一个新的右端点时
        SEGT.range_add(0, i - 1, -cost[i]);                      // 将此前的 maxv 全部多减去一个 cost[i]，因为要多修一条路
        for (auto [l, v] : val[i]) SEGT.range_add(0, l - 1, v);  // 将这些状态的 maxv 都加上修路带来的价值
        f[i] = std::max(f[i - 1], SEGT.query(0, i - 1));         // 更新当前状态
        SEGT.point_set(i, f[i]);                                 // 更新线段树中的状态
    }

    write(f[N]), putchar('\n');
    return fflush(stdout), 0;
}
