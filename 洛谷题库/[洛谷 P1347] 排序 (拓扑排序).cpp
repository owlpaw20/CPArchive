#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 600 + 10;

queue<int> q;
int n, m, res;
char u, op, v;
vector<int> topo;
int ed[N], nx[N], h[N], to[N], idx;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = h[u];
    h[u] = idx;
    idx++;
}

int topological_sort() {
    int tmpto[N];
    bool flag = 0;
    memcpy(tmpto, to, sizeof to);

    for (int i = 0; i < n; i++)
        if (!tmpto[i])
            q.push(i);

    while (!q.empty()) {
        if (q.size() > 1) flag = 1;
        int t = q.front();
        q.pop();
        topo.push_back(t);
        for (int i = h[t]; ~i; i = nx[i]) {
            int j = ed[i];
            tmpto[j]--;
            if (!tmpto[j]) q.push(j);
        }
    }

    if ((int)topo.size() < n)  // 如果拓扑没有遍历完全
        return 0;              // 说明图中存在环

    if (flag)      // 如果队列中同时出现有多个元素
        return 1;  // 说明拓扑序完全但不稳定

    return 2;  // 如果所有节点的入度都为 0，说明拓扑序完全且稳定
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(h, -1, sizeof h);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> u >> op >> v;
        int uu = u - 'A';
        int vv = v - 'A';
        connect(uu, vv);

        to[vv]++;
        topo.clear();
        res = topological_sort();

        if (res == 2) {
            printf("Sorted sequence determined after %d relations: ", i);
            for (auto i : topo)
                printf("%c", (char)(i + 'A'));
            printf(".\n");
            return 0;
        } else if (res == 0) {
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        }
    }
    puts("Sorted sequence cannot be determined.");
    return 0;
}
