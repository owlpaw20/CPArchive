#pragma GCC optimize("O2,unroll-loops")
#include <numeric>
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 15;

bool vis[N];
int n, ans = 10;
int a[N], group[N][N];

bool check(int* arr, int x, int start) {
    for (int i = 0; i < start; i++)
        if (gcd(arr[i], x) > 1)
            return false;
    return true;
}

void DFS(int g_num, int idx, int start, int cnt) {
    if (g_num >= ans) return;
    if (cnt == n) ans = g_num;

    bool is_empty = true;
    for (int i = start; i < n; i++)
        if (!vis[i] && check(group[g_num], a[i], idx)) {
            vis[i] = true;
            group[g_num][idx] = a[i];
            DFS(g_num, idx + 1, start + 1, cnt + 1);
            vis[i] = false;
            is_empty = false;
        }

    if (is_empty) DFS(g_num + 1, 0, 0, cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    DFS(1, 0, 0, 0);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
