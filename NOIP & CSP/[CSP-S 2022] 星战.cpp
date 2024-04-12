#include <chrono>
#include <random>
#include <cstdint>
#include <cstring>
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
}  // namespace FastIO
using namespace FastIO;

using u64 = uint64_t;

const int MAX_N = 5e5 + 5;

int N, M, Q;
u64 in[MAX_N], init[MAX_N];
u64 val[MAX_N];

std::mt19937 Rand(std::chrono::steady_clock().now().time_since_epoch().count());

int main() {
    N = read<int>(), M = read<int>();

    u64 sum = 0;
    for (int i = 1; i <= N; ++i)
        val[i] = Rand(), sum += val[i];

    u64 cur = 0;
    while (M--) {
        int u = read<int>(), v = read<int>();
        init[v] = in[v] += val[u];
        cur += val[u];
    }

    Q = read<int>();

    while (Q--) {
        int t = read<int>(), u = read<int>();

        switch (t) {
            case 1:
                in[read<int>()] -= val[u];
                cur -= val[u];
                break;

            case 2:
                cur -= in[u];
                in[u] = 0;
                break;

            case 3:
                in[read<int>()] += val[u];
                cur += val[u];
                break;

            case 4:
                cur = cur - in[u] + init[u];
                in[u] = init[u];
                break;

            default:
                break;
        }

        puts(sum == cur ? "YES" : "NO");
    }

    return fflush(stdout), 0;
}
