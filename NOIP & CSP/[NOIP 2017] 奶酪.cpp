#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

int t, n;
double h, r;
bool flag, book[1005];

struct sphere {
    double x, y, z;
} a[1005];

bool cmp(sphere x, sphere y) {
    return x.z < y.z;
}

double dis(double x1, double x2, double y1, double y2, double z1, double z2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
} // 求距离

void dfs(sphere now, int num) {
    if (now.z + r >= h) {
        flag = 1;
        return;
    }

    book[num] = 1;

    for (int j = 1; j <= n; j++) {
        if (flag) return; // 剪枝
        if (!book[j] && dis(now.x, a[j].x, now.y, a[j].y, now.z, a[j].z) <= 2 * r) // 如果可以到达下一个空洞
            dfs(a[j], j); // 搜索
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        memset(a, 0, sizeof a);
        memset(book, 0, sizeof book);
        flag = 0;
        cin >> n >> h >> r;
        for (int i = 1; i <= n; i++)
            cin >> a[i].x >> a[i].y >> a[i].z;
        sort(a + 1, a + n + 1, cmp); // 对所有空洞进行排序
        for (int i = 1; i <= n; i++)
            if (a[i].z <= r) // 与下表面相通的空洞
                dfs(a[i], i); // 可以开始搜索
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    fflush(stdout);
    return 0;
}
