#include <cstring>
#include <iostream>
using namespace std;

const int SIZE = 1e2 + 10;
const int INF = 0x3F3F3F3F;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

int n, m, minn = INF;
int g[SIZE][SIZE]; // 0 = 无色, 1 = 红色, 2 = 黄色
int cost[SIZE][SIZE];
bool vis[SIZE][SIZE];

void DFS(int x, int y, int curr, int color) {
    if (x == n && y == n) {
        minn = min(minn, curr);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int tx = x + DX[i], ty = y + DY[i];
        if (tx <= n && tx > 0 && ty <= n && ty > 0 && !vis[tx][ty]) {
            if (g[x][y] == 0 && g[tx][ty] == 0) continue; // 魔法不能连续使用
            if (g[tx][ty] == 0) { // 如果目标点无色
                if (curr + 2 < cost[tx][ty]) {
                    vis[tx][ty] = true;
                    cost[tx][ty] = curr + 2;
                    DFS(tx, ty, curr + 2, color);
                    vis[tx][ty] = false;
                }
            } else { // 如果目标点有色
                if (color == g[tx][ty] && curr < cost[tx][ty]) {
                    vis[tx][ty] = true;
                    cost[tx][ty] = curr;
                    DFS(tx, ty, curr, color);
                    vis[tx][ty] = false;
                } else if (curr + 1 < cost[tx][ty]) {
                    vis[tx][ty] = true;
                    cost[tx][ty] = curr + 1;
                    DFS(tx, ty, curr + 1, g[tx][ty]);
                    vis[tx][ty] = false;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    memset(cost, 0x3F, sizeof cost);
    cin >> n >> m;
    while (m--) {
        int x, y, c;
        cin >> x >> y >> c;
        g[x][y] = c + 1;
    }
    vis[1][1] = true;
    DFS(1, 1, 0, g[1][1]);
    if (minn == INF)
        cout << -1 << endl;
    else
        cout << minn << endl;
    return 0;
}
