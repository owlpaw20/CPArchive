#include <limits>
#include <iostream>

#define endl '\n'

using i64 = long long int;

const int MAX_N = 5e3 + 5;

int n, s;
int t[MAX_N], c[MAX_N];
int sum_t[MAX_N], sum_c[MAX_N];

i64 f[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> s;

    for (int i = 1; i <= n; ++i) {
        std::cin >> t[i] >> c[i];
        sum_t[i] = sum_t[i - 1] + t[i];
        sum_c[i] = sum_c[i - 1] + c[i];
    }

    std::fill(f + 1, f + n + 1, std::numeric_limits<i64>::max());

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            f[i] = std::min(f[i], f[j] + (i64)(sum_c[i] - sum_c[j]) * sum_t[i] + (i64)s * (sum_c[n] - sum_c[j]));

    std::cout << f[n] << endl;
    return fflush(stdout), 0;
}
