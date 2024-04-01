#include <queue>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;

using PII = std::pair<int, int>;

const int MAX_N = 2e3 + 5;
const int MAX_P = 2e5 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int N, M, P, Q;
char map[MAX_N][MAX_N];

std::queue<PII> q;
int gov[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

std::vector<PII> graph[MAX_P];
std::vector<PII> graph2[MAX_N * MAX_N];

struct UnionFind {
    int fa[MAX_P];

    void init(int x) {
        std::iota(fa, fa + x + 1, 0);
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }
} sets;

namespace LCA {
    int fa[MAX_P][20];
    int mx[MAX_P][20];
    int depth[MAX_P];

    void prep(int st) {
        std::queue<int> q;
        q.push(st);
        depth[st] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto [v, w] : graph[u]) {
                if (depth[v]) continue;

                depth[v] = depth[u] + 1;
                fa[v][0] = u, mx[v][0] = w;

                for (int i = 1; i < 20; i++) {
                    fa[v][i] = fa[fa[v][i - 1]][i - 1];
                    mx[v][i] = std::max(mx[v][i - 1], mx[fa[v][i - 1]][i - 1]);
                }

                q.push(v);
            }
        }
    }

    int query(int u, int v) {
        if (depth[u] > depth[v]) std::swap(u, v);

        int mxw = 0;

        for (int i = 19; ~i; i--)
            if (depth[fa[v][i]] >= depth[u]) {
                mxw = std::max(mxw, mx[v][i]);
                v = fa[v][i];
            }

        if (u == v) return mxw;

        for (int i = 19; ~i; i--)
            if (fa[u][i] != fa[v][i]) {
                mxw = std::max({mxw, mx[u][i], mx[v][i]});
                u = fa[u][i], v = fa[v][i];
            }

        mxw = std::max({mxw, mx[u][0], mx[v][0]});
        return mxw;
    }
} // namespace LCA

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> P >> Q;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> map[i][j];

    for (int i = 1, x, y; i <= P; i++) {
        cin >> x >> y;
        gov[x][y] = i;
        q.emplace(x, y);
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];

            if (tx < 1 || ty < 1 || tx > N || ty > M) continue;
            if (map[tx][ty] == '#') continue;

            if (!gov[tx][ty]) {
                gov[tx][ty] = gov[x][y];
                dist[tx][ty] = dist[x][y] + 1;
                q.emplace(tx, ty);
            } else if (gov[tx][ty] != gov[x][y])
                graph2[dist[tx][ty] + dist[x][y]].emplace_back(gov[x][y], gov[tx][ty]);
        }
    }

    sets.init(P);

    for (int w = 0; w < N * N; w++)
        for (auto [u, v] : graph2[w])
            if (sets.merge(u, v)) {
                graph[u].emplace_back(v, w);
                graph[v].emplace_back(u, w);
            }

    for (int i = 1; i <= P; i++)
        if (!LCA::depth[i])
            LCA::prep(i);

    while (Q--) {
        int S, T;
        cin >> S >> T;

        if (sets.find(S) != sets.find(T)) cout << -1 << endl;
        else cout << LCA::query(S, T) << endl;
    }

    return fflush(stdout), 0;
}
