#include <cstdint>
#include <iostream>
#include <algorithm>

#define endl '\n'

using u32 = uint32_t;
using u64 = uint64_t;
using cu32 = const uint32_t;
using cu64 = const uint64_t;

const u32 MAX_N = 1e3 + 5;
const u32 MAX_X = 5e3 + 5;
const u32 MOD = 998244353;

u32 n, x;
u32 a[MAX_N];
u32 f[MAX_X][MAX_X];  // f[i][j] = 考虑了前 i 个数后，x 被模成了 j 的方案数

inline u32 mod(cu32 x, cu32 y = MOD) { return (x < y) ? (x) : (x - x / y * y); }
inline u32 mod(cu64 x, cu32 y = MOD) { return (x < y) ? (x) : (x - x / y * y); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> x;
    for (u32 i = 1; i <= n; ++i) std::cin >> a[i];

    auto cmp = [](cu32 x, cu32 y) -> bool { return x > y; };
    std::sort(a + 1, a + n + 1, cmp);

    f[0][x] = 1;

    // 考虑是否要模 a[i]
    for (u32 i = 1; i <= n; ++i) {
        // 如果不对 a[i] 取模，就将其放到一个较小的数后面再取模
        // 由于排序，取法有 n - i 种
        for (u32 j = 0; j <= x; ++j)
            f[i][j] = mod(f[i][j] + mod((u64)f[i - 1][j] * (n - i)));

        // 如果对 a[i] 取模，则从上一个位置转移过来
        for (u32 j = 0; j <= x; ++j)
            f[i][mod(j, a[i])] = mod(f[i][mod(j, a[i])] + f[i - 1][j]);
    }

    for (int i = x; ~i; --i)
        if (f[n][i]) {
            std::cout << i << endl
                      << f[n][i] << endl;
            break;
        }

    return fflush(stdout), 0;
}
