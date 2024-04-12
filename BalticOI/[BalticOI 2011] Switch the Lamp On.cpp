#include <deque>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e2 + 10;
const int INF = 0x3F3F3F3F;
const int dx[] = {1, 1, -1, -1};
const int dy[] = {1, -1, -1, 1};

int n, m;
int dist[N][N];
bool vis[N][N];
char cct[N][N];

bool check(int x, int y, int tx, int ty) {
    if (tx < x && ty < y) return (cct[min(x, tx)][min(y, ty)] == '/');
    if (tx > x && ty > y) return (cct[min(x, tx)][min(y, ty)] == '/');
    return (cct[min(x, tx)][min(y, ty)] == '\\');
}

int BFS(int sx, int sy) {
    memset(dist, 0x3F, sizeof dist);
    memset(vis, false, sizeof vis);
    dist[sx][sy] = 0;
    deque<PII> q;
    q.emplace_back(sx, sy);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        if (vis[x][y]) continue;
        vis[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 0 || ty < 0 || tx > n || ty > m) continue;
            if (vis[tx][ty]) continue;

            bool if_switch = check(x, y, tx, ty);

            if (dist[x][y] + if_switch < dist[tx][ty]) {
                dist[tx][ty] = dist[x][y] + if_switch;
                if (if_switch)
                    q.emplace_back(tx, ty);
                else
                    q.emplace_front(tx, ty);
            }
        }
    }

    return dist[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> cct[i][j];

    int ret = BFS(0, 0);
    cout << (ret == INF ? "NO SOLUTION" : to_string(ret)) << endl;

    fflush(stdout);
    return 0;
}
