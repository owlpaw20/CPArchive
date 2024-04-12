#include <stack>
#include <cstring>
#include <iostream>
#include <unordered_set>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e5 + 5;
const int M = 2e6 + 5;

int n, m, x;

// 链式前向星
int head1[N], head2[N];
int ed[M], nx[M], idx;

// Tarjan 缩点
int dfn[N], low[N], scc[N], sizes[N];
int scc_cnt, timestamp;
bool in_stk[N];
stack<int> stk;

// DAG 上 DP 求最长链
unordered_set<i64> vis;
int f[N], g[N];

void connect(int u, int v, int *head) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;

    stk.push(u);
    in_stk[u] = true;

    for (int i = head1[u]; ~i; i = nx[i]) {
        int v = ed[i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk.top();
            stk.pop();
            scc[v] = scc_cnt;
            in_stk[v] = false;
            sizes[scc_cnt]++;
        } while (v != u);
    }
}

// 对边进行哈希用于判重
i64 H(int x, int y) {
    return (i64)(x - 1) * N + y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head1, -1, sizeof head1);
    memset(head2, -1, sizeof head2);

    cin >> n >> m >> x;
    while (m--) {
        int u, v;
        cin >> u >> v;
        connect(u, v, head1);
    }

    // 将图中所有强连通分量缩成点
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);

    // 建立缩点之后的新图
    for (int i = 1; i <= n; i++)
        for (int j = head1[i]; ~j; j = nx[j]) {
            int u = scc[i], v = scc[ed[j]];
            i64 h = H(u, v);
            if (u != v && vis.insert(h).second)  // 对强连通分量的出边进行判重
                connect(u, v, head2);
        }

    // Tarjan 遍历顺序是先子节点再父节点
    // 所以 Tarjan 缩点之后强连通分量的下标组成逆拓扑序

    // 对所有强连通分量进行 DAG 上拓扑序 DP 求最长链并统计方案数
    for (int i = scc_cnt; i != 0; i--) {
        if (!f[i]) {          // 如果该强连通分量没有被遍历过
            f[i] = sizes[i];  // 则初始化 f[i] 为其大小（强连通分量自身也是半连通的）
            g[i] = 1;         // 并初始化方案数 g[i]
        }
        for (int j = head2[i]; ~j; j = nx[j]) {  // 遍历该强连通分量的所有出边
            int v = ed[j];                       // 获取出边的终点
            if (f[v] < f[i] + sizes[v]) {        // 如果把出边所在强连通分量加入当前的链可以使答案更优
                f[v] = f[i] + sizes[v];          // -- 更新当前链并保存链更新后的长度
                g[v] = g[i];                     // -- 保存链更新之后的可选方案数
            } else if (f[v] == f[i] + sizes[v])  // 否则如果加入该强连通分量后链的长度相等
                g[v] = (g[v] + g[i]) % x;        // -- 则只更新可选方案数
        }
    }

    int maxf = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (f[i] > maxf)
            maxf = f[i], sum = g[i];  // 求最长链并保存最长链的方案数
        else if (f[i] == maxf)
            sum = (sum + g[i]) % x;

    cout << maxf << endl;
    cout << sum << endl;
    fflush(stdout);
    return 0;
}
