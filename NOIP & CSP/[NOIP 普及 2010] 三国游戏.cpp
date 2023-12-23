#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e2 + 10;

int n, w[N][N];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> w[i][j];
            w[j][i] = w[i][j];
        }
        sort(w[i] + 1, w[i] + n + 1);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, w[i][n - 1]);
    cout << 1 << endl
         << ans << endl;
    return 0;
}
