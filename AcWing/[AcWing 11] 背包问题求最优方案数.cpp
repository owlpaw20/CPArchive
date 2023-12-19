#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int MOD = 1e9 + 7;

int n, m;
int f[N], g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    fill(g, g + m + 1, 1);

    while (n--) {
        int v, w;
        cin >> v >> w;
        for (int i = m; i >= v; i--) {
            int val = f[i - v] + w;
            if (val > f[i]) {
                f[i] = val;
                g[i] = g[i - v];
            } else if (val == f[i])
                g[i] = (g[i] + g[i - v]) % MOD;
        }
    }

    cout << g[m] << endl;
    fflush(stdout);
    return 0;
}
