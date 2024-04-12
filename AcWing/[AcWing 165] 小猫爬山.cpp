#pragma GCC optimize("O2,unroll-loops")
#include <iostream>
#include <algorithm>
#define endl '\n'

using namespace std;

const int N = 20;
const int INF = 0x7FFFFFFF;

int n, m, ans = INF;
int c[N], group[N];

void DFS(int idx, int cnt) {
    if (cnt >= ans) return;  // 最优性剪枝
    if (idx > n)
        return (void)(ans = min(ans, cnt));

    for (int i = 1; i <= cnt; i++)
        if (group[i] + c[idx] <= m)  // 可行性剪枝
            group[i] += c[idx], DFS(idx + 1, cnt), group[i] -= c[idx];

    group[cnt + 1] = c[idx];
    DFS(idx + 1, cnt + 1);
    group[cnt + 1] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> c[i];
    sort(c + 1, c + n + 1, greater<int>());  // 优化搜索顺序

    DFS(1, 1);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
