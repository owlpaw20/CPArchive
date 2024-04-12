#include <cstdint>
#include <iostream>

using i64 = int64_t;

const int MAX_N = 2e6 + 5;

int N;
char s[MAX_N];

int f[MAX_N];  // f[i] 表示以第 i 位结尾的合法子串数量，f[i] = f[g[i] - 1] + 1
int g[MAX_N];  // g[i] 表示最大能使 s[g[i], i] 成为合法子串的下标
int a[MAX_N][26];
// 用于转移 g 数组，表示 s[a[i][c] + 1] = c 且能使 s[a[i][c] + 1, i] 成为合法子串的最大下标

int main() {
    scanf("%d\n %s", &N, s + 1);

    i64 ans = 0;
    for (int i = 1, t; i <= N; ++i) {
        g[i] = i;
        if ((t = a[g[i - 1]][s[i] - 'a'])) g[i] = g[t - 1], f[i] = f[t - 1] + 1;
        a[g[i]][s[i] - 'a'] = i, ans += f[i];
    }

    printf("%lld\n", ans);
    return fflush(stdout), 0;
}
