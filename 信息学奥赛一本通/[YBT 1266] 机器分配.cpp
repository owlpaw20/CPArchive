#include <iostream>

#define endl '\n'

using namespace std;

const int N = 20;

int n, m;
int v[N][N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> v[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= j; k++)
                f[i][j] = max(f[i][j], f[i - 1][j - k] + v[i][k]);

    cout << f[n][m] << endl;

    for (int i = n, j = m; i > 0; i--)
        for (int k = 0; k <= j; k++)
            if (f[i][j] == f[i - 1][j - k] + v[i][k]) {
                cout << i << ' ' << k << endl;
                j -= k;
                break;
            }

    fflush(stdout);
    return 0;
}
