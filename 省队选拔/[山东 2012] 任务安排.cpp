#include <cmath>
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

using i64 = long long int;
using i128 = __int128_t;

const int MAX_N = 3e5 + 5;

int n, s;
int sum_t[MAX_N], sum_c[MAX_N];

i64 f[MAX_N];
int q[MAX_N];

int main() {
    n = read<int>(), s = read<int>();

    for (int i = 1; i <= n; ++i) {
        sum_t[i] = sum_t[i - 1] + read<int>();
        sum_c[i] = sum_c[i - 1] + read<int>();
    }

    int qh = 0, qr = 0;

    auto get_insertion_pos = [&](const int i) -> int {
        int l = qh, r = qr;
        while (l < r) {
            const int mid = (l + r) >> 1, m = q[mid], mx = q[mid + 1];
            (f[mx] - f[m] >= i64(sum_t[i] + s) * (sum_c[mx] - sum_c[m])) ? (r = mid) : (l = mid + 1);
        }
        return r;
    };

    auto eliminate_back = [&](const int i) -> bool {
        const int r = q[qr], rp = q[qr - 1];
        return i128(f[r] - f[rp]) * (sum_c[i] - sum_c[rp]) >= i128(f[i] - f[rp]) * (sum_c[r] - sum_c[rp]);
    };

    for (int i = 1; i <= n; ++i) {
        int j = q[get_insertion_pos(i)];
        f[i] = f[j] - i64(sum_t[i] + s) * sum_c[j] + (i64)sum_c[i] * sum_t[i] + (i64)sum_c[n] * s;
        while (qh < qr && eliminate_back(i)) --qr;
        q[++qr] = i;
    }

    write(f[n]), putchar('\n');
    return fflush(stdout), 0;
}
