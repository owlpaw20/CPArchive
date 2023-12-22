#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;

const int N = 1e2 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

// 提前写好的状态顺序
const vector<int> seq = {1, 2, 4, 8, 3, 5, 9, 6, 10, 12, 7, 11, 13, 14, 15};

// 为每一个颜色分配数字编号
unordered_map<char, int> mp = {{'P', 0}, {'C', 1}, {'Z', 2}, {'N', 3}};

int n, m;
int g[N][N][4];  // 存储每一个方格在四个方向的门的颜色
bool vis[N][N];

bool BFS(int sx, int sy, int ex, int ey, int state) {
    using PII = pair<int, int>;
    memset(vis, 0, sizeof vis);

    queue<PII> q;
    vis[sx][sy] = true;
    q.emplace(sx, sy);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == ex && y == ey)
            return true;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];

            if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
            if (vis[tx][ty]) continue;

            if ((1 << g[x][y][i]) & state)
                q.emplace(tx, ty), vis[tx][ty] = true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    char ch;

    // 输入横向相邻两个方格之间门的颜色
    // 注意要与偏移数组中各下标对应的的方向相同
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
            cin >> ch, g[i][j][0] = g[i][j + 1][2] = mp[ch];

    // 输入纵向相邻两个方格之间门的颜色
    // 注意要与偏移数组中各下标对应的的方向相同
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
            cin >> ch, g[i][j][1] = g[i + 1][j][3] = mp[ch];

    int q;
    cin >> q;
    while (q--) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;

        for (int state : seq) {
            if (BFS(sx, sy, ex, ey, state)) {               // 如果找到合法解
                cout << __builtin_popcount(state) << endl;  // 则输出所选颜色个数
                break;
            }
        }
    }

    fflush(stdout);
    return 0;
}
