#include <iostream>
using namespace std;

const int N = 105;

int n, m, p;
int a[N][N], pre[N][3];
int f1[N][N], f2[N][N][N];

void solve1() {
    for (int k = 1; k <= p; k++)
        for (int i = 1; i <= n; i++) {
            f1[i][k] = f1[i - 1][k];
            for (int j = 0; j < i; j++)
                f1[i][k] = max(f1[i][k], f1[j][k - 1] + pre[i][1] - pre[j][1]);
        }

    cout << f1[n][p] << endl;
}

void solve2() {
    for (int k = 1; k <= p; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                f2[i][j][k] = max(f2[i - 1][j][k], f2[i][j - 1][k]);
                for (int w = 0; w < i; w++)
                    f2[i][j][k] = max(f2[i][j][k], f2[w][j][k - 1] + pre[i][1] - pre[w][1]);
                for (int w = 0; w < j; w++)
                    f2[i][j][k] = max(f2[i][j][k], f2[i][w][k - 1] + pre[j][2] - pre[w][2]);
                if (i == j)
                    for (int w = 0; w < i; w++)
                        f2[i][j][k] = max(f2[i][j][k], f2[w][w][k - 1] + pre[i][1] + pre[j][2] - pre[w][1] - pre[w][2]);
            }

    cout << f2[n][n][p] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++) {
        pre[i][1] = pre[i - 1][1] + a[i][1];
        pre[i][2] = pre[i - 1][2] + a[i][2];
    }

    if (m == 1) solve1();
    else solve2();

    return 0;
}
