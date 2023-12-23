#include <iostream>
using namespace std;
using lng = long long;

const int N = 5e5 + 10;

int n, q, m;
lng a[N], b[N], c[N], p[N];
lng pre_b[N], f[N], g[N];
// f[i] 表示使 1 ~ p[i] 的元素从全为 1 改变到满足条件所需的最小代价
// g[i] 表示使 1 ~ p[i] 的元素从全为 0 改变到满足条件所需的最小代价

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i], pre_b[i] = pre_b[i - 1] + b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) a[i] = min(a[i], a[i - 1] + b[i]);
    cin >> q;
    while (q--) {
        cin >> m;
        for (int i = 1; i <= m; i++) cin >> p[i];
        for (int i = 1; i <= m; i++) {
            // 全为 0 只需要进行一次 c 操作
            g[i] = g[i - 1] + c[p[i]];
            // 全为 1 则将前面全部清零，然后回到 g 的情况
            // 或者将 p[i-1] ~ p[i] 之间全部清零，然后全部进行 b 操作
            f[i] = a[p[i] - 1] + g[i - 1];
            f[i] = min(f[i], f[i - 1] + pre_b[p[i] - 1] - pre_b[p[i - 1]]);
        }
        // 答案为 min{全部清零然后用 c 操作的代价, 预处理得到的全 1 最小代价 + 用 b 操作改变末尾的 0 的代价}
        cout << min(g[m] + a[n], f[m] + pre_b[n] - pre_b[p[m]]) << endl;
    }
    return 0;
}
