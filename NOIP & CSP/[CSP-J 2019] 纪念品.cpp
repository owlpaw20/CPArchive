#include <vector>
#include <iostream>
using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

int t, n, m;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> t >> n >> m;
    VVI w(t + 5, VI(n + 5));
    for (int i = 1; i <= t; i++)
        for (int j = 1; j <= n; j++)
            cin >> w[i][j];
    for (int i = 1; i <= t; i++) {
        VI f(m + 5);
        for (int j = 1; j <= n; j++)
            if (w[i + 1][j] > w[i][j]) // 只有收入为正时才更新
                for (int k = w[i][j]; k <= m; k++)
                    f[k] = max(f[k], f[k - w[i][j]] + w[i + 1][j] - w[i][j]);
        m += f[m];
    }
    cout << m << endl;
    return 0;
}
