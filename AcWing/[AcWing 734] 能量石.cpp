#include <tuple>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define s(a) get<0>(a)
#define l(a) get<2>(a)

using namespace std;
using TPL = tuple<int, int, int>;

const int N = 1e2 + 5;
const int M = 1e4 + 5;

TPL a[N];
int f[M];

/* 在最优解中，可能有某些宝石的能量已经消耗殆尽，这些宝石可以不考虑。假设去
 * 除了贡献为 0 的宝石后的最优解的能量石排列长度为 K (1 <= K <= N)，则对于
 * a[1] ~ a[K] 中的任意两个位置 i 和 j = i + 1，交换之后，这两个宝石的贡
 * 献之和不会更大。设总时间为 t，则
 * E[i] - t * L[i] + E[j] - (t + S[i]) * L[j] >= E[j] - t * L[j] + E[i] - (t + S[j]) * L[i]
 * 整理得，
 * S[i] * L[j] <= S[j] * L[i] */

auto cmp = [](TPL x, TPL y) { return s(x) * l(y) < s(y) * l(x); };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1, n; t <= T; t++) {
        memset(f, 0xCF, sizeof f);
        f[0] = 0;

        cin >> n;

        int maxt = 0;

        for (int i = 1; i <= n; i++) {
            auto& [s, e, l] = a[i];
            cin >> s >> e >> l;
            maxt += s;
        }

        sort(a + 1, a + n + 1, cmp);

        for (int i = 1; i <= n; i++) {
            auto [s, e, l] = a[i];
            for (int j = maxt; j >= s; j--)
                f[j] = max(f[j], f[j - s] + max(0, e) - (j - s) * l);
        }

        int ans = 0;
        for (int i = 1; i <= maxt; i++)
            ans = max(ans, f[i]);

        printf("Case #%d: %d\n", t, ans);
    }

    fflush(stdout);
    return 0;
}
