#include <queue>
#include <tuple>
#include <iostream>

using namespace std;
using TPL = tuple<int, int, int>;

const int N = 2e2 + 5;
const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};

int n, m;
int mp[N][N];

int BFS(int sx, int sy, int ex, int ey) {
    queue<TPL> q;
    q.emplace(sx, sy, 0);

    while (!q.empty()) {
        auto [x, y, step] = q.front();
        q.pop();

        if (x == ex && y == ey)
            return step;

        for (int i = 0; i < 8; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];

            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            if (mp[tx][ty]) continue;

            mp[tx][ty] = 1;
            q.emplace(tx, ty, step + 1);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    char c;
    int sx, sy, ex, ey;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> c;
            if (c == '*') mp[i][j] = 1;
            else if (c == 'K') sx = i, sy = j;
            else if (c == 'H') ex = i, ey = j;
        }

    cout << BFS(sx, sy, ex, ey) << '\n';

    fflush(stdout);
    return 0;
}
