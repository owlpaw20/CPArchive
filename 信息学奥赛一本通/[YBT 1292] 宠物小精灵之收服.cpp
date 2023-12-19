#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int M = 5e2 + 10;

int n, m, K;
int f[N][M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;
    for (int i = 1; i <= K; i++) {
        int ball, dmg;
        cin >> ball >> dmg;
        for (int i = n; i >= ball; i--)
            for (int j = m - 1; j >= dmg; j--)
                f[i][j] = max(f[i][j], f[i - ball][j - dmg] + 1);
    }

    int dmg = m;
    for (int i = 0; i < m; i++)
        if (f[n][i] == f[n][m - 1])
            dmg = min(dmg, i);

    cout << f[n][m - 1] << " " << m - dmg << endl;
    fflush(stdout);
    return 0;
}
