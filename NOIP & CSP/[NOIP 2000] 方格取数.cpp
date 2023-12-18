#include <iostream>
using namespace std;

const int N = 20;

int n, p[N][N], f[N][N][N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    while (1) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0 && b == 0 && c == 0) break;
        p[a][b] = c;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                for (int w = 1; w <= n; w++) {
                    f[i][j][k][w] = p[i][j] + max(max(f[i - 1][j][k - 1][w], f[i - 1][j][k][w - 1]),
                                                  max(f[i][j - 1][k - 1][w], f[i][j - 1][k][w - 1]));
                    if (i != 1 && j != w) f[i][j][k][w] += p[k][w];
                }

    cout << f[n][n][n][n] << endl;
    return 0;
}
