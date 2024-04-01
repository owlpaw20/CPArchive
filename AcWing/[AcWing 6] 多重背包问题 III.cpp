#include <iostream>

#define endl '\n'

using namespace std;

const int M = 2e4 + 5;

int n, m, q[M];
int f[2][M];

/*  f[j] = max(f[j - v] + w, f[j - 2v] + 2w, ..., f[j - kv] + kw)
    f[j + v] = max(f[j] + w, f[j - v] + 2w, ..., f[j - (k - 1)v] + kw)
    f[j + pv] = max(f[j - v + pv] + w, f[j - 2v + pv] + 2w, ..., f[j - kv + pv] + kw)
             = max(f[j + (p-1)v] + w, f[j + (p-2) v] + 2w, ..., f[j + (p-k) v] + kw) */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1, c, v, s; i <= n; i++) {
        cin >> c >> v >> s;
        for (int r = 0; r < c; r++) {
            int H = 0, R = -1;
            for (int j = r; j <= m; j += c) {
                while (H <= R && j - q[H] > s * c) H++;
                while (H <= R && f[(i - 1) & 1][q[R]] + (j - q[R]) / c * v <= f[(i - 1) & 1][j]) R--;
                q[++R] = j;
                f[i & 1][j] = f[(i - 1) & 1][q[H]] + (j - q[H]) / c * v;
            }
        }
    }

    cout << f[n & 1][m] << endl;
    fflush(stdout);
    return 0;
}
