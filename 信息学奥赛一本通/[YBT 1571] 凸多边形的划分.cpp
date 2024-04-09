#include <limits>
#include <iostream>

#define endl '\n'

using i128 = __int128_t;

const int MAX_N = 55;

int N, val[MAX_N];
i128 f[MAX_N][MAX_N];

void write(i128 x) {
    if (x < (i128)0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> val[i];

    for (int len = 3; len <= N; ++len)
        for (int l = 1, r = len; r <= N; ++l, ++r) {
            f[l][r] = std::numeric_limits<i128>::max();
            for (int k = l + 1; k <= r - 1; ++k)
                f[l][r] = std::min(f[l][r], f[l][k] + f[k][r] + (i128)val[l] * val[k] * val[r]);
        }

    write(f[1][N]), putchar('\n');
    return fflush(stdout), 0;
}
