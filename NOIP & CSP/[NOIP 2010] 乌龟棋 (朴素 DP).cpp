#include <iostream>

#define endl '\n'

using namespace std;

const int M = 5;
const int N = 50;
const int P = 500;

int n, m;
int a[P], b[M];
int f[N][N][N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        int t;
        cin >> t;
        b[t]++;
    }

    f[0][0][0][0] = a[1];
    for (int i = 0; i <= b[1]; i++)
        for (int j = 0; j <= b[2]; j++)
            for (int k = 0; k <= b[3]; k++)
                for (int o = 0; o <= b[4]; o++) {
                    int score = 1 + i + j * 2 + k * 3 + o * 4;
                    int& abcd = f[i][j][k][o];
                    if (i) abcd = max(abcd, f[i - 1][j][k][o] + a[score]);
                    if (j) abcd = max(abcd, f[i][j - 1][k][o] + a[score]);
                    if (k) abcd = max(abcd, f[i][j][k - 1][o] + a[score]);
                    if (o) abcd = max(abcd, f[i][j][k][o - 1] + a[score]);
                }

    cout << f[b[1]][b[2]][b[3]][b[4]] << endl;
    fflush(stdout);
    return 0;
}
