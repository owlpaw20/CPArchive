#include <iostream>
using namespace std;

const int N = 1e3 + 10;
const char cand[] = {'J', 'O', 'I'};

int n, m, ans, o;
char g[N][N], e[3][3];

bool check(int x, int y) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (g[x + i][y + j] != e[i + 1][j + 1])
                return false;
    return true;
}

void solve(int x, int y, char c) {
    if (c == g[x][y]) return;
    char tmp = g[x][y];
    int cnt = o;

    for (int i = x - 1; i <= x; i++)
        for (int j = y - 1; j <= y; j++)
            if (check(i, j))
                cnt--;

    g[x][y] = c;

    for (int i = x - 1; i <= x; i++)
        for (int j = y - 1; j <= y; j++)
            if (check(i, j))
                cnt++;

    ans = max(ans, cnt);
    g[x][y] = tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
            cin >> e[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (check(i, j))
                ans++;

    o = ans;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < 3; k++)
                solve(i, j, cand[k]);

    cout << ans << endl;
    return 0;
}
