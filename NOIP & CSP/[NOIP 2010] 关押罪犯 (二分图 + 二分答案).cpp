#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e4 + 10;
const int M = 2e5 + 10;

int n, m, idx;
int head[N], color[N];
int ed[M], nx[M], wt[M];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

bool DFS(int u, int c, int limit) {
    color[u] = c;
    for (int i = head[u]; ~i; i = nx[i]) {
        if (wt[i] <= limit) continue; // 只考虑较大的怨气值
        int j = ed[i];
        if (color[j]) {
            if (color[j] == c) // 如果出现颜色冲突
                return false; // 则不是二分图
        } else if (!DFS(j, 3 - c, limit)) // 则不是二分图
            return false;
    }
    return true;
}

// 判断所有怨气值大于 x 的关系是否能形成合法二分图
bool check(int x) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++)
        if (color[i] == 0)
            if (!DFS(i, 1, x))
                return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }

    // 对最大边权进行二分答案
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    fflush(stdout);
    return 0;
}
