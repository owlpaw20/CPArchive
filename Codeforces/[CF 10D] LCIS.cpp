#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e2 + 10;

int n, m;
int a[N], b[N];
int f[N][N], pre[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i - 1][j];
            pre[i][j] = pre[i - 1][j];
            if (a[i] == b[j]) {
                int maxval = 1, maxk = 0;
                for (int k = 1; k < j; k++)
                    if (a[i] > b[k] && maxval < f[i - 1][k] + 1)
                        maxval = f[i - 1][k] + 1,
                        maxk = k;
                f[i][j] = max(f[i][j], maxval);
                pre[i][j] = maxk;
            }
        }

    int ans = 0, seq_end = 0;
    for (int i = 1; i <= m; i++)
        if (ans < f[n][i])
            ans = f[n][i], seq_end = i;

    cout << ans << endl;
    if (ans == 0) return 0;

    vector<int> seq;
    do {
        seq.push_back(b[seq_end]);
        seq_end = pre[n][seq_end];
    } while (seq_end != 0);

    for (auto it = seq.rbegin(); it != seq.rend(); it++)
        cout << *it << ' ';
    cout << endl;

    return 0;
}
