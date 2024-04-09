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

    template <typename T>
    void write(T x, char y) { write(x), putchar(y); }
} // namespace FastIO
using namespace FastIO;

using u32 = uint32_t;

const int MAX_N = 1e5 + 5;

int N;
u32 f[MAX_N];
char mark[MAX_N];

int main() {
    N = read<int>();
    for (int i = 1; i <= N; ++i) mark[i] = getchar();

    if (N & 1) {
        puts("0");
        return fflush(stdout), 0;
    }

    f[0] = 1;
    for (int i = 1; i <= N; ++i)
        if (mark[i] == '?') {
            for (int j = (i >> 1); j; --j)
                f[j] = f[j] * 25 + f[j - 1];
            f[0] *= 25;
        }

    write(f[N >> 1], '\n');
    return fflush(stdout), 0;
}
