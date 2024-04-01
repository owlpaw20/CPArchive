#include <stack>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 1e4 + 10;
const int M = 1e5 + 10;
const int INF = 0x7FFFFFFF;

int n, m;

int ord;
int dfn[N];
int low[N];
bool vis[N];
bool out[N];
int belong[N];
stack<int> st;
vector<vector<int>> scc;

int ed[M], nx[M], head[N], idx;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++ord; // 标记当前节点的初始 DFS 序和追溯值

    st.push(u); // 将遍历到的节点放入栈中
    vis[u] = true; // 标记为已入栈

    for (int i = head[u]; ~i; i = nx[i]) { // 遍历以当前点 U 为起点的所有边
        int v = ed[i]; // 取得边的终点 V
        if (dfn[v] == 0) { // 如果该终点 V 还没有 DFS 序（没有搜索过）
            Tarjan(v); // -- 则递归地对该终点 V 进行搜索
            low[u] = min(low[u], low[v]); // -- 并更新起点 U 的追溯值
        } else if (vis[v] == true) // 如果该终点 V 被搜索过但仍在栈中
            low[u] = min(low[u], low[v]); // -- 利用它来更新起点 U 的追溯值
    }

    if (low[u] == dfn[u]) { // 如果找到了整个强联通分量的头部节点
        scc.emplace_back(); // 在存储中新增一个强联通分量

        int idx = scc.size() - 1;
        scc[idx].push_back(u); // 在存储中加入该头部节点

        while (!st.empty() && st.top() != u) { // 将栈中属于当前强联通分量的所有点取出
            belong[st.top()] = idx; // 标记所从属于的强联通分量
            vis[st.top()] = false; // 标记为已出栈
            scc[idx].push_back(st.top()); // 在存储中加入该节点
            st.pop(); // 出栈
        }

        // 处理头部节点的标记和出栈
        vis[u] = false;
        belong[u] = idx;
        st.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        connect(u, v);
    }

    // 从 1 号点开始 DFS
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            Tarjan(i);

    // 输出强联通分量的数量
    cout << scc.size() << endl;

    // 对所有强联通分量内部进行排序
    for (vector<int>& s : scc)
        sort(s.begin(), s.end());

    // 输出所有强联通分量
    for (int i = 1; i <= n; i++) {
        if (out[belong[i]] == true) continue;
        out[belong[i]] = true;
        for (int node : scc[belong[i]])
            cout << node << ' ';
        cout.put('\n');
    }

    fflush(stdout);
    return 0;
}
