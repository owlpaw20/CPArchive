#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 15;
const int M = 1 << 15;
const int INF = 0x3F3F3F3F;

int n, m;
int d[N][N];
int f[M][N], g[M];

/*  状态转移方程：
    f[i][j] = min_{valid(k, j)} {f[k][i - 1] + (i - 1) * cost(k, j)}
    这是一个按层 DP 的方程，每次考虑当前层相对于上一层新增了哪些节点。
    其中 valid(k, j) 表示状态 k 是否能通过增加若干条道路变为状态 j，且只扩展了一层；
    cost(k, j) 表示增加的道路长度综合的最小值。

    valid(k, j) == true 当且仅当：
     1. k 为 j 的子集，即 j & k == k
     2. j 为 expand(k) 的子集，即 j & expand(k) == j，
        其中 expand(k) 表示从 k 中所有节点出发向下开凿一层以内的所有道路之后，
        处于被打通状态的所有节点构成的集合。expand(k) 可以通过预处理得到。*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(d, 0x3f, sizeof d);
    memset(f, 0x3f, sizeof f);

    cin >> n >> m;
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int i = 0; i < n; i++) f[1 << i][0] = 0;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        d[u][v] = d[v][u] = min(d[u][v], w);
    }

    // 预处理所有状态扩展一层之后可获得的最大下一层状态
    for (int i = 1; i < 1 << n; i++)
        for (int j = 0; j < n; j++)          // 对于每一个节点 U
            if (i >> j & 1) {                // 如果当前状态的这个点是打通的
                for (int k = 0; k < n; k++)  // 则从 U 开始
                    if (d[j][k] != INF)      // 把所有与之连边的节点
                        g[i] |= 1 << k;      // 都添加到最大状态里
            }

    for (int i = 1; i < 1 << n; i++)
        for (int j = (i - 1) & i; j; j = (j - 1) & i)
            // 计算扩展的费用
            if ((g[j] & i) == i) {
                int remain = i ^ j;  // 待更新的方案
                int cost = 0;        // 记录边权之和
                for (int k = 0; k < n; k++)
                    if (remain >> k & 1) {
                        int t = INF;
                        for (int u = 0; u < n; u++)
                            if (j >> u & 1)  // 找出当前连通块内能把该点加入所用的最小边的边长
                                t = min(t, d[k][u]);
                        cost += t;
                    }

                // 根据计算出的费用进行转移
                for (int k = 1; k < n; k++)
                    f[i][k] = min(f[i][k], f[j][k - 1] + cost * k);
            }

    int ans = INF;
    for (int i = 0; i < n; i++)
        ans = min(ans, f[(1 << n) - 1][i]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
