#include <queue>
#include <vector>
#include <iostream>

using namespace std;
using PII = pair<int, int>;

const int N = 110;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, x, y, a, b, cnt;
bool on[N][N], vis[N][N], if_laid_off[N][N];
vector<PII> swi[N][N];
queue<PII> q, togo, delayed;

void BFS() {
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int i = 0; i < swi[x][y].size(); i++)
            on[swi[x][y][i].first][swi[x][y][i].second] = 1;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (!on[tx][ty]) {
                if (!if_laid_off[tx][ty]) {
                    if_laid_off[tx][ty] = 1;
                    togo.push({tx, ty});
                }
            } else if (!vis[tx][ty] && tx > 0 && ty > 0 && tx <= n && ty <= n) {
                vis[tx][ty] = 1;
                q.push({tx, ty});
            }
        }

        while (!togo.empty()) {
            int x = togo.front().first, y = togo.front().second;
            togo.pop();
            if (!vis[x][y] && on[x][y])
                q.push({x, y});
            else
                delayed.push({x, y});
        }

        while (!delayed.empty()) {
            int x = delayed.front().first, y = delayed.front().second;
            delayed.pop();
            togo.push({x, y});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> a >> b;
        swi[x][y].push_back({a, b});
    }

    on[1][1] = vis[1][1] = 1;
    q.push({1, 1});
    BFS();

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cnt += on[i][j];
    cout << cnt << endl;
    return 0;
}
