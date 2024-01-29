#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 30;

struct UnionFind {
    int fa[N], sz[N];

    void reset(int n) {
        for (int i = 1; i <= n; i++)
            sz[i] = 0, fa[i] = i;
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[x] = y, sz[y] += sz[x], true;
    }
};

bool vis[N];
int deg[N];
UnionFind dsu;

void solve() {
    memset(deg, 0, sizeof deg);
    memset(vis, 0, sizeof vis);

    int n;
    cin >> n;

    dsu.reset(26);

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        int u = s.front() - 'a';
        int v = s.back() - 'a';

        vis[u] = vis[v] = true;  // 标记字母已出现
        deg[v]--, deg[u]++;      // 统计每个字母的度数

        dsu.merge(u, v);  // 标记两点连通
    }

    int s = 0, t = 0;

    for (int i = 0; i < 26; i++)
        if (deg[i] != 0) {               // 如果有向图有存在奇点
            if (deg[i] == 1) s++;        // 判断是否为起点
            else if (deg[i] == -1) t++;  // 判断是否为终点
            else goto unsuccessful;      // 如果有其他度数则不存在欧拉路
        }

    if (!(s == 0 && t == 0) && !(s == 1 && t == 1))  // 如果不是全部为偶点或只有两个奇点
        goto unsuccessful;                           // 则不存在欧拉路

    for (int i = 0, t = -1; i < 26; i++)
        if (vis[i]) {
            if (t == -1)                // 如果找到了第一个出现过的字母
                t = dsu.find(i);        // 以该字母作为起点
            else if (t != dsu.find(i))  // 如果它与其他某个出现过的字母不联通
                goto unsuccessful;      // 则不存在欧拉路，因为所有出现过的字母都应该互相连通
        }

    // 存在欧拉路
    puts("Ordering is possible.");
    return;

unsuccessful:
    puts("The door cannot be opened.");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
