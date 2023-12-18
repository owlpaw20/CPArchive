#include <iostream>

#define endl '\n'

using namespace std;

const int M = 5;
const int N = 50;
const int P = 500;

int n, m;
int a[P], b[M];
int f[N][N][N];

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

    for (int i = 0; i <= b[1]; i++)
        for (int j = 0; j <= b[2]; j++)
            for (int k = 0; k <= b[3]; k++)
                for (int o = 0; o <= b[4]; o++) {
                    int score = 1 + i + j * 2 + k * 3 + o * 4;
                    if (j) f[j][k][o] = max(f[j][k][o], f[j - 1][k][o]);
                    if (k) f[j][k][o] = max(f[j][k][o], f[j][k - 1][o]);
                    if (o) f[j][k][o] = max(f[j][k][o], f[j][k][o - 1]);
                    f[j][k][o] += a[score];
                }

    cout << f[b[2]][b[3]][b[4]] << endl;
    fflush(stdout);
    return 0;
}
