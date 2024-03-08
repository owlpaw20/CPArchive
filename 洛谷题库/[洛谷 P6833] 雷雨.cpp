#include <queue>
#include <tuple>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;
using i64 = long long;
using TPL = tuple<i64, int, int>;

const int N = 1e3 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const i64 INF = 0x7FFFFFFFFFFFFFFF;

int n, m, a, b, c;
int g[N][N];
i64 d[3][N][N];
bool vis[N][N];

void BFS(int wh, int sx, int sy) {  // 其实也可以看成是堆优化的 Dijkstra
    memset(vis, 0, sizeof vis);

    priority_queue<TPL, vector<TPL>, greater<TPL>> heap;
    heap.emplace(d[wh][sx][sy] = g[sx][sy], sx, sy);

    while (!heap.empty()) {
        auto [dist, x, y] = heap.top();
        heap.pop();

        if (vis[x][y]) continue;
        vis[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
            if (d[wh][tx][ty] > dist + g[tx][ty])
                heap.emplace(d[wh][tx][ty] = dist + g[tx][ty], tx, ty);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(d, 0x3F, sizeof d);

    cin >> n >> m >> a >> b >> c;
    for (int i = n; i > 0; i--)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];

    BFS(0, n, a);
    BFS(1, 1, b);
    BFS(2, 1, c);

    i64 ans = INF;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = min(ans, d[0][i][j] + d[1][i][j] + d[2][i][j] - 2 * g[i][j]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
