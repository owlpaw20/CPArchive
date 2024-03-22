#include <cstdio>

using i64 = long long;

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

const int MAX_N = 1e6 + 5;

int N, Q;

struct FENWICK {
    i64 data[MAX_N];

    void upd(int i, const int delta) {
        for (; i <= N; i += (i & -i))
            data[i] += delta;
    }

    i64 sum(int i) {
        i64 ret = 0;
        for (; i; i -= (i & -i))
            ret += data[i];
        return ret;
    }
} BIT;

int main() {
    N = read<int>(), Q = read<int>();
    for (int i = 1, p = 0, c = 0; i <= N; ++i)
        BIT.upd(i, (c = read<int>()) - p), p = c;

    int l, r, x;
    do {
        if (read<int>() == 1) {
            l = read<int>(), r = read<int>(), x = read<int>();
            BIT.upd(l, x), BIT.upd(r + 1, -x);
        } else
            write<i64>(BIT.sum(read<int>())), putchar('\n');
    } while (--Q);

    return fflush(stdout), 0;
}
