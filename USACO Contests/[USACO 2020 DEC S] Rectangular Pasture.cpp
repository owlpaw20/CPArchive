#include <iostream>
#include <algorithm>
#define x first
#define y second
using namespace std;
using lng = long long;
using PII = pair<lng, lng>;

const int N = 2.5e3 + 10;

int n;
PII cow[N];
int pre[N][N];
int vis[2][N];

int sum(int x1, int y1, int x2, int y2) {
    return pre[x2][y2] - pre[x2][y1 - 1] - pre[x1 - 1][y2] + pre[x1 - 1][y1 - 1];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].x >> cow[i].y;
        vis[0][i] = cow[i].x;
        vis[1][i] = cow[i].y;
    }

    // 坐标离散化
    sort(vis[0] + 1, vis[0] + n + 1);
    sort(vis[1] + 1, vis[1] + n + 1);
    for (int i = 1; i <= n; i++) {
        cow[i].x = lower_bound(vis[0] + 1, vis[0] + n + 1, cow[i].x) - vis[0];
        cow[i].y = lower_bound(vis[1] + 1, vis[1] + n + 1, cow[i].y) - vis[1];
        pre[cow[i].x][cow[i].y] = 1;
    }

    // 二维前缀和
    auto cmp = [&](PII a, PII b) { return a.y < b.y; };
    sort(cow + 1, cow + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];

    // 计算答案
    lng ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            int top = min(cow[i].x, cow[j].x);
            int bottom = max(cow[i].x, cow[j].x);
            ans += sum(1, cow[i].y, top, cow[j].y) * sum(bottom, cow[i].y, n, cow[j].y);
        }

    cout << ans + 1 << endl;
    return 0;
}
