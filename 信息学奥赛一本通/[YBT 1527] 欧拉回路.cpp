#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;
const int M = 4e5 + 5;

int t, n, m;
int in[N], out[N];
int ed[M], nx[M], head[N], idx;
vector<int> ring;
bool vis[M];

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

bool check(int x) {
    if (t == 1) return (in[x] + out[x]) & 1;  // 无向图存在欧拉回路的充要条件是不存在奇点
    return in[x] != out[x];                   // 有向图存在欧拉回路的充要条件是所有点度数为 0
}

void DFS(int u) {
    for (int& i = head[u]; ~i;) {
        if (vis[i]) {   // 如果这条边已经删过
            i = nx[i];  // 则直接跳到下一条边
            continue;
        }

        vis[i] = true;                  // 删除当前边
        if (t == 1) vis[i ^ 1] = true;  // 删除无向图中建立的相反边

        int id;
        if (t == 1) {
            id = i / 2 + 1;       // 转化无向图链表下标与边的编号
            if (i & 1) id = -id;  // 链表下标为奇数表示为无向图中的反向边
        } else
            id = i + 1;

        int v = ed[i];  // 访问边的终点
        i = nx[i];      // 删除用过的边
        DFS(v);         // 从边的终点继续递归删边

        ring.push_back(id);  // 考虑完边的终点后将边加入回路中，这样形成的是逆欧拉回路
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> t >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        connect(u, v), in[v]++, out[u]++;
        if (t == 1) connect(v, u);
    }

    for (int i = 1; i <= n; i++)
        if (check(i))
            return puts("NO"), 0;

    for (int i = 1; i <= n; i++)
        if (head[i] != -1) {  // 找到第一条有边连接的点开始递归
            DFS(i);
            break;
        }

    if ((int)ring.size() < m)  // 如果回路中的边数小于总边数
        return puts("NO"), 0;  // 则不构成合法欧拉回路

    cout << "YES" << endl;

    for (auto it = ring.rbegin(); it != ring.rend(); it++)  // 输出欧拉回路
        cout << *it << ' ';

    cout << endl;
    fflush(stdout);
    return 0;
}
