#include <limits>
#include <cstdint>
#include <iostream>

#define endl '\n'
#define ceil(x, y) ((x) / (y) + bool((x) % (y)))

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

using i64 = int64_t;

const int MAX_N = 1e5 + 5;

int cx[MAX_N], cy[MAX_N];
i64 p[MAX_N], l[MAX_N], r[MAX_N];

void solve() {
    int N(read<int>()), K(read<int>());
    i64 x(read<int>()), y(read<int>());

    for (int i = 1; i <= N; ++i) {
        cx[i] = read<int>(), cy[i] = read<int>();
        l[i] = 0, r[i] = std::numeric_limits<i64>::max();
    }

    if (x == 0 && y == 0) {
        putchar('0'), putchar('\n');
        return;
    }

    auto update_boundaries = [&](const int ox, const int oy) -> void {
        i64 xx = ox * x, yy = oy * y;

        for (int i = 1; i <= N; ++i)
            p[i] = p[i - 1] + cx[i] * ox + cy[i] * oy + K;

        if (!p[N]) {
            for (int i = 1; i <= N; ++i)
                if (p[i] < xx + yy)
                    r[i] = std::numeric_limits<i64>::min();
            return;
        }

        for (int i = 1; i <= N; ++i) {
            if (p[N] > 0) {
                if (p[i] < xx + yy)
                    l[i] = std::max(l[i], ceil(xx + yy - p[i], p[N]));
            } else if (p[i] < xx + yy)
                r[i] = std::numeric_limits<i64>::min();
            else
                r[i] = std::min(r[i], (xx + yy - p[i]) / p[N]);
        }
    };

    update_boundaries(1, 1);
    update_boundaries(-1, 1);
    update_boundaries(1, -1);
    update_boundaries(-1, -1);

    i64 ans = std::numeric_limits<i64>::max();

    for (int i = 1; i <= N; ++i)
        if (l[i] <= r[i])
            ans = std::min(ans, l[i] * N + i);

    write((ans == std::numeric_limits<i64>::max()) ? -1 : ans), putchar('\n');
}

int main() {
    int T(read<int>());
    while (T--) solve();
    return fflush(stdout), 0;
}
