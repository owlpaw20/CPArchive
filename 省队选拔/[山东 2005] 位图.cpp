#include <cstdlib>
#include <cstring>
#include <iostream>
#define x first
#define y second
using namespace std;
using PII = pair<int, int>;

const int N = 160;
const int M = 25600;
const int INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

template <class Type>
struct queue {
    Type data[M];
    int head, rear;
    void push(Type x) {
        data[++rear] = x;
    }
    Type extract() {
        return data[head++];
    }
    bool empty() {
        return head > rear;
    }
    queue() : head(0), rear(-1) {}
};

int n, m, bmp[N][N];
bool vis[N][N];

int D(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int BFS(int sx, int sy) {
    if (bmp[sx][sy] == 1) return 0;
    queue<PII> q;
    memset(vis, false, sizeof vis);
    q.push({sx, sy});
    vis[sx][sy] = true;
    int dist = INF;
    while (!q.empty()) {
        PII u = q.extract();
        for (int i = 0; i < 4; i++) {
            int tx = u.x + dx[i], ty = u.y + dy[i], td = D(sx, sy, tx, ty);
            if (tx > 0 && ty > 0 && tx <= n && ty <= m && !vis[tx][ty] && td < dist) {
                vis[tx][ty] = true;
                q.push({tx, ty});
                if (bmp[tx][ty])
                    dist = td;
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> bmp[i][j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cout << BFS(i, j) << " ";
        cout << endl;
    }
    return 0;
}
