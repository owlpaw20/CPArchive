#include <queue>
#include <bitset>
#include <vector>
#include <cstdint>
#include <iostream>

#define endl '\n'

namespace FastIO {
    const int MAX_BUF = 1 << 20;
    char buf[MAX_BUF], *p1, *p2;

#define getchar() \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

    template <typename T>
    T read() {
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
    void write(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
} // namespace FastIO
using namespace FastIO;

using PII = std::pair<int, int>;

const int MAX_N = 5e3 + 5;

int indeg[MAX_N];

std::queue<PII> q;
std::vector<int> graph[MAX_N];
std::bitset<MAX_N> stats;

int main() {
    read<int>(); // 用不到 N

    int K(read<int>()), p(read<int>());

    for (int i = 1, t; i <= p; ++i)
        stats.set(t = read<int>()), q.emplace(t, 0);

    int R = read<int>();

    for (int i = 1, v; i <= R; ++i) {
        v = read<int>(), indeg[v] = read<int>();
        for (int j = 1; j <= indeg[v]; ++j)
            graph[read<int>()].push_back(v);
    }

    auto BFS = [&]() -> int {
        while (!q.empty()) {
            auto [u, t] = q.front();
            q.pop();

            if (!stats.test(u)) continue;
            if (u == K) return t;

            for (int v : graph[u])
                if (--indeg[v] == 0)
                    stats.set(v), q.emplace(v, t + 1);
        }

        return -1;
    };

    write(BFS()), putchar('\n');
    return fflush(stdout), 0;
}
