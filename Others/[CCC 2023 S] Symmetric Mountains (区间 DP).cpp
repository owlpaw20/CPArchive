#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 5e3 + 5;
const int INF = 0x7FFFFFFF;

int n;
int h[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];

    for (int i = 1; i <= n; i++) {
        int ans = INF;
        for (int j = 1; j + i - 1 <= n; j++) {
            f[j][j + i - 1] = f[j + 1][j + i - 2] + abs(h[j] - h[j + i - 1]);
            ans = min(ans, f[j][j + i - 1]);
        }
        cout << ans << ' ';
    }

    cout.put('\n');
    fflush(stdout);
    return 0;
}
