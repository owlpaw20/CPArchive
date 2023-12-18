#include <iostream>

using namespace std;

const int N = 20;
const int INF = 0x3f3f3f3f;

int n, m, r, c;
int mat[N][N], q[N], cc[N], rr[N][N];
int f[N][N];

int count(int x) {
    int ret = 0;
    for (int i = 0; i < n; i++)
        ret += x >> i & 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> r >> c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];

    int ans = INF;
    for (int st = 0; st < (1 << n); st++)
        if (count(st) == r) {
            for (int i = 0, j = 0; i < n; i++)
                if (st >> i & 1)
                    q[j++] = i;
            for (int i = 0; i < m; i++) {
                cc[i] = 0;
                for (int j = 1; j < r; j++)
                    cc[i] += abs(mat[q[j]][i] - mat[q[j - 1]][i]);
            }
            for (int i = 0; i < m; i++)
                for (int j = i + 1; j < m; j++) {
                    rr[i][j] = 0;
                    for (int k = 0; k < r; k++)
                        rr[i][j] += abs(mat[q[k]][i] - mat[q[k]][j]);
                }
            for (int i = 0; i < m; i++) {
                f[i][1] = cc[i];
                for (int j = 2; j <= c; j++) {
                    f[i][j] = INF;
                    for (int k = 0; k < i; k++)
                        f[i][j] = min(f[i][j], f[k][j - 1] + cc[i] + rr[k][i]);
                }
                ans = min(ans, f[i][c]);
            }
        }

    cout << ans << endl;
    return 0;
}
